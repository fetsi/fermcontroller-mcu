CFLAGS = -Wall -Os -mmcu=attiny861 -DF_CPU=8000000
BUILDDIR = ../build


all: display.hex

display.hex: display.bin
	avr-objcopy -j .text -j .data -O ihex $(BUILDDIR)/display.bin $(BUILDDIR)/display.hex	


display.bin : display.o spi.o fdup.o
	avr-gcc $(CFLAGS) -o $(BUILDDIR)/display.bin display.o spi.o fdup.o


display.o : display.c
	avr-gcc -c $(CFLAGS) display.c

spi.o : spi.c
	avr-gcc -c $(CFLAGS) spi.c

fdup.o : fdup.c
	avr-gcc -c $(CFLAGS) fdup.c


clean:
	rm *.o
	rm $(BUILDDIR)/*.bin
	rm $(BUILDDIR)/*.hex


upload: display.hex
	avrdude -p t861 -c usbtiny -U flash:w:$(BUILDDIR)/display.hex:i