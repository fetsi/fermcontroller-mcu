#!/bin/bash
avr-gcc -Wall -Os -mmcu=attiny861 -DF_CPU=8000000 -o blinktest.bin blinktest.c && avr-objcopy -j .text -j .data -O ihex blinktest.bin blinktest.hex && avrdude -p t861 -c usbtiny -U flash:w:blinktest.hex:i

