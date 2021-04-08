#ifndef __AVR_ATtiny861__
#define __AVR_ATtiny861__
#endif

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>



unsigned char DISPMUX[4] = {
    0b00010000,
    0b00100000,
    0b01000000,
    0b00001000
};



#define SEGM_A  0b00100000
#define SEGM_B  0b10000000
#define SEGM_C  0b00001000
#define SEGM_D  0b00000010
#define SEGM_E  0b00010000
#define SEGM_F  0b01000000
#define SEGM_G  0b00000001

#define DECIMAL_POINT 0b00000100

#define CHAR_0      (SEGM_A | SEGM_B | SEGM_C | SEGM_D | SEGM_E | SEGM_F)
#define CHAR_1      (SEGM_B | SEGM_C)
#define CHAR_2      (SEGM_A | SEGM_B | SEGM_G | SEGM_E | SEGM_D)
#define CHAR_3      (SEGM_A | SEGM_B | SEGM_G | SEGM_C | SEGM_D)
#define CHAR_4      (SEGM_F | SEGM_G | SEGM_B | SEGM_C)
#define CHAR_5      (SEGM_A | SEGM_F | SEGM_G | SEGM_C | SEGM_D)
#define CHAR_6      (SEGM_A | SEGM_F | SEGM_E | SEGM_D | SEGM_C | SEGM_G)
#define CHAR_7      (SEGM_A | SEGM_B | SEGM_C)
#define CHAR_8      (SEGM_A | SEGM_B | SEGM_C | SEGM_D | SEGM_E | SEGM_F | SEGM_G)
#define CHAR_9      (SEGM_A | SEGM_F | SEGM_B | SEGM_G | SEGM_C | SEGM_D)
#define CHAR_MINUS  (SEGM_G)

#define SCREENMUX_PORT PORTB
#define SCREENCONT_PORT PORTA



void clock_setup(void) {

    cli(); // Disable interrupts
    CLKPR = (1<<CLKPCE); // Prescaler enable
    CLKPR = 0; // Clock division factor 1 (0000)
    sei(); // Enable interrupts
}


int main(void) {

    clock_setup();
    DDRA = 0b11111111;
    DDRB = 0b11110000;

    unsigned char SCREENCONTENTS[4] = {
        CHAR_1,
        CHAR_2 | DECIMAL_POINT,
        CHAR_4,
        CHAR_5
    };

    PORTA = CHAR_2;
    PORTB = 0;
    unsigned char counter = 0;

    
    while(1) {
        PORTA = SCREENCONTENTS[counter];
        PORTB = DISPMUX[counter];
        if(counter++ == 3)
            counter = 0;
        _delay_ms(2);
    }
    
    return 0;
    

}