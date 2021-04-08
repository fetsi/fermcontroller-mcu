#ifndef DISPCONT_H
#define DISPCONT_H

#include "sevensegment.h"

typedef struct dispcontent_t {
    unsigned char character;
    unsigned char dp : 1;
} dispcontent_t;

typedef struct dispcontent_t dispcontent_t;

typedef struct dispcombo_t {
    dispcontent_t disp_arr[NUM_DISPLAYS];
} dispcombo_t;



#endif