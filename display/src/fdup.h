#ifndef FDUP_H
#define FDUP_H

struct dispcombo_t;

/**
 *@brief Translates a binary structure that conforms to the FDUP protocol specification into a structure that contains GPIO output register
 *values that can be used to operate the 7-segment display
 *@details Interprets the FDUP data inside the structure pointed to by the "displays" pointer and modifies the contents of each of its 4 "dispcontent_t" 
 *structs (see dispcont.h) in a way that their "character" field equals the GPIO output register contents that can be used to draw the
 *character to the display. The decimal point bit is also included in the field if the "dp" bitfield is set to 1
 * 
 **/
char translate_fdup_7segm(dispcombo_t *displays);





#endif