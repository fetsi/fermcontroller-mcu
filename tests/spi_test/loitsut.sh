#!/bin/bash
avr-gcc -Wall -Os -mmcu=attiny861 -DF_CPU=1000000 -o spi_test.bin spi_test.c spi.c && avr-objcopy -j .text -j .data -O ihex spi_test.bin spi_test.hex && avrdude -p t861 -c usbtiny -U flash:w:spi_test.hex:i

