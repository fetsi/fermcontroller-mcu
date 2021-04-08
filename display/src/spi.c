#ifndef __AVR_ATtiny861__
#define __AVR_ATtiny861__
#endif
#ifndef __GNUC__
#define __GNUC__
#endif

#include "avr/io.h"
#include "avr/interrupt.h"
#include <string.h>
#include "spi.h"
#include "dispcont.h"

#define MAX_FRAMESIZE 8            //Max size of FDUP frame not including start & end bytes


struct usidriverStatus_t {
	unsigned char transferOfByteComplete : 1; //!< True when transfer of a byte is completed.
	unsigned char writeCollision : 1;         //!< True if put attempted during transfer.
    unsigned char receivingDispUpdate : 1;    //!< True if we have received the FDUP frame start byte but have not yet received the whole frame
    unsigned char bytesReceived;              //!< Used to count the number of bytes we have received out of a FDUP frame. (Bytes recvd since start byte) 
};

volatile struct usidriverStatus_t spi_status;


unsigned char recvBuffer[MAX_FRAMESIZE];
unsigned char dispContents[MAX_FRAMESIZE];


void spi_init_slave(void) {
    DDRB &= ~(1 << DDB0);   //Set MOSI pin as input
    DDRB |= (1 << DDB1);    //Set MISO pin as output
    DDRB &= ~(1 << DDB2);   //Set clock pin as input
    PORTB |= (1 << PORTB1) | (1 << PORTB0); //Activate pull-ups for MOSI & clock

    //Enable counter overflow interrupt, set to 3-wire mode and set spi mode to 0 ()
    USICR = (1 << USIOIE) | (1 << USIWM0) | (1 << USICS1);
    USIDR = 0;

    spi_status.transferOfByteComplete = 0;
    spi_status.writeCollision = 0;
    spi_status.receivingDispUpdate = 0;
    spi_status.bytesReceived = 0;
    memset(recvBuffer, 0, sizeof(recvBuffer));
    memset(dispContents, 0, sizeof(dispContents));
}


ISR(USI_OVF_vect) {
    //Updates flags, clears counter
    USISR =  (1 << USIOIF);
    spi_status.transferOfByteComplete = 1;
    unsigned char storedUSIDR = USIDR;

    if(spi_status.receivingDispUpdate) {
        if(storedUSIDR == 0xBE) {    //TODO: Replace hard-coded value with reference to the FDUP header once that exists
            if(spi_status.bytesReceived == MAX_FRAMESIZE) {
                memcpy(dispContents, recvBuffer, MAX_FRAMESIZE); //Copy buffer contents into disp contents only if we have received a complete frame
            }
            memset(recvBuffer, 0, MAX_FRAMESIZE);
            spi_status.receivingDispUpdate = 0;
            spi_status.bytesReceived = 0;
        }
        else {
            if(spi_status.bytesReceived < MAX_FRAMESIZE) {
                recvBuffer[spi_status.bytesReceived] = storedUSIDR;
                ++spi_status.bytesReceived;
            }
            else {
                memset(recvBuffer, 0, MAX_FRAMESIZE);
                spi_status.receivingDispUpdate = 0;
                spi_status.bytesReceived = 0;
            }
        }
    }
    else {
        if(storedUSIDR == 0xBA) { //TODO: Replace hard-coded value with reference to the FDUP header once that exists
            spi_status.receivingDispUpdate = 1;
        }
    }

}


char spi_put(unsigned char val) {

    //If counter (4 lowest bits of USISR) is not zero, there is a transfer in progress. If so, set the writeCollision flag and return -1
    //without modifying data registers
    if(USISR & 0x0F) {
        spi_status.writeCollision = 1;
        return -1;
    }
    

    //Re-initialize status flags
    spi_status.transferOfByteComplete = 0;
    spi_status.writeCollision = 0;
    
    //Put data in the USI data register
    USIDR = val;

    return 0;
}

char spi_get_disp_cont(dispcombo_t *displays) {

    //TODO: This check should probably be optimized into something a lot lighter since it gets executed every couple of milliseconds in the main loop
    if(memcmp(displays, dispContents, sizeof(*displays))) {
        memcpy(displays, dispContents, sizeof(*displays));
        return 0;
    }
    return -1;
}

void spi_wait(void) {
    while(spi_status.transferOfByteComplete == 0);
}
