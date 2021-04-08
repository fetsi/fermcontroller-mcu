#ifndef SPI_H
#define SPI_H

#include "dispcont.h"



void spi_init_slave(void);
char spi_put(unsigned char val);
char spi_get_disp_cont(dispcombo_t *displays);
void spi_wait(void);



#endif