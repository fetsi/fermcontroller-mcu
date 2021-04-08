#ifndef __AVR_ATtiny861__
#define __AVR_ATtiny861__
#endif
#ifndef __GNUC__
#define __GNUC__
#endif

#include "avr/io.h"
#include "avr/interrupt.h"

struct usidriverStatus_t {
	unsigned char transferOfByteComplete : 1; //!< True when transfer completed.
	unsigned char writeCollision : 1;   //!< True if put attempted during transfer.
};

volatile struct usidriverStatus_t spi_status;
unsigned char storedUSIDR;

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
    storedUSIDR = 0;
}


ISR(USI_OVF_vect) {

    //Updates flags, clears counter
    USISR =  (1 << USIOIF);

    spi_status.transferOfByteComplete = 1;
    storedUSIDR = USIDR;
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

unsigned char spi_get_disp_cont(void) {
    return storedUSIDR;
}

void spi_wait(void) {
    while(spi_status.transferOfByteComplete == 0);
}
