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

#define NUMBER_DISPBYTES 8            //Max size of FDUP frame not including start, end & address bytes


struct usidriverStatus_t {
	unsigned char transferOfByteComplete : 1; //!< True when transfer of a byte is completed.
	unsigned char writeCollision : 1;         //!< True if put attempted during transfer.
    unsigned char frameStarted : 1;           //!< True if we have received the FDUP frame start byte but have not yet received the whole frame
    unsigned char receivingDispContents : 1;  //!< True if the current frame is meant for us according to the address byte
    unsigned char bytesReceived;              //!< Used to count the number of bytes we have received out of a FDUP frame. (Bytes recvd since start byte) 
    unsigned char dispBytesRecvd;             //!< Used to count the number of display content bytes we have received (bytes after address byte, if the message is for us) 
};

volatile struct usidriverStatus_t spi_status;


unsigned char recvBuffer[NUMBER_DISPBYTES];
unsigned char dispContents[NUMBER_DISPBYTES];


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
    spi_status.frameStarted = 0;
    spi_status.bytesReceived = 0;
    spi_status.receivingDispContents = 0;
    spi_status.dispBytesRecvd = 0;
    memset(recvBuffer, 0, sizeof(recvBuffer));
    memset(dispContents, 0, sizeof(dispContents));
}


ISR(USI_OVF_vect) {
    //Clear counter overflow interrupt flag
    USISR =  (1 << USIOIF);
    spi_status.transferOfByteComplete = 1;
    unsigned char currentByte = USIDR;

    if(!spi_status.frameStarted && currentByte == 0xBA) {
        //We received the frame start byte
        spi_status.frameStarted = 1;
    }

    if(spi_status.frameStarted) {
        ++spi_status.bytesReceived;
        if((spi_status.bytesReceived == 2) && (currentByte == MY_ADDRESS) ) {
            //This frame is for us!
            spi_status.receivingDispContents = 1;
            return;
        } 

        if(spi_status.receivingDispContents && spi_status.dispBytesRecvd < NUMBER_DISPBYTES) {
            recvBuffer[spi_status.dispBytesRecvd] = currentByte;
            ++spi_status.dispBytesRecvd;
        }

        if(currentByte == 0xBE) {    //TODO: Replace hard-coded value with reference to the FDUP header once that exists
            if(spi_status.dispBytesRecvd == NUMBER_DISPBYTES) {
                memcpy(dispContents, recvBuffer, NUMBER_DISPBYTES); //Copy buffer contents into disp contents only if we have received the right amount of display bytes
            }
            memset(recvBuffer, 0, sizeof(recvBuffer));
            spi_status.receivingDispContents = 0;
            spi_status.frameStarted = 0;
            spi_status.bytesReceived = 0;
            spi_status.dispBytesRecvd = 0;
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
