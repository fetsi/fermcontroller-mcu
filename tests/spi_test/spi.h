#ifndef SPI_H
#define SPI_H

struct dispcontent_t {
    unsigned char character;
    unsigned char dp : 1;
};

typedef struct dispcontent_t dispcontent_t;

struct dispcombo_t {
    dispcontent_t disp1;
    dispcontent_t disp2;
    dispcontent_t disp3;
    dispcontent_t disp4;
};
typedef struct dispcombo_t dispcombo_t;


void spi_init_slave(void);
char spi_put(unsigned char val);
char spi_get_disp_cont(dispcombo_t *displays);
void spi_wait(void);



#endif

