#ifndef SPI_H
#define SPI_H

#include "dispcont.h"

#define MY_ADDRESS 0x88



void spi_init_slave(void);
char spi_put(unsigned char val);
char spi_get_disp_cont(dispcombo_t *displays);
void spi_wait(void);



#endif