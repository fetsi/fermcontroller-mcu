#ifndef __AVR_ATtiny861__
#define __AVR_ATtiny861__
#endif


#include "spi.h"
#include "avr/interrupt.h"

void clock_setup(void) {

    cli(); // Disable interrupts
    CLKPR = (1<<CLKPCE); // Prescaler enable
    CLKPR = 0; // Clock division factor 1 (0000)
    sei(); // Enable interrupts
}



int main(void) {

    //unsigned char value = 6;
    clock_setup();
    spi_init_slave();

    do {
        spi_wait();
        unsigned char val = spi_get_disp_cont(); 
        spi_put(val);
         
    }  while(1);



    return 0;
    
}

