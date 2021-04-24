#ifndef __AVR_ATtiny861__
#define __AVR_ATtiny861__
#endif

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "spi.h"
#include "sevensegment.h"
#include "dispcont.h"
#include "fdup.h"
#include <string.h>


unsigned char DISPMUX[4] = {
    0b00001000,
    0b00010000,
    0b00100000,
    0b01000000
};




void clock_setup(void) {

    cli(); // Disable interrupts
    CLKPR = (1<<CLKPCE); // Prescaler enable
    CLKPR = 0; // Clock division factor 1 (0000)
    sei(); // Enable interrupts
}


int main(void) {

    clock_setup();
    spi_init_slave();
    DDRA = 0b11111111;
    DDRB = 0b01111000;


    PORTA = 0;
    PORTB = 0;
    
    unsigned char counter = 0;

 
    dispcombo_t contents;
    memset(&contents, 0, sizeof(contents));

    while(1) {
        
        spi_get_disp_cont(&contents);
        translate_fdup_7segm(&contents);

        PORTA = 0;
        _delay_ms(1);
        PORTB = DISPMUX[counter];
        _delay_ms(2);
        PORTA = contents.disp_arr[counter].character;
        
        if(counter++  == (NUM_DISPLAYS - 1))
            counter = 0;
        _delay_ms(2);
    }

    return 0;
    

}