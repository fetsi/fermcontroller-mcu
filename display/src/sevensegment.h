#ifndef SEVENSEGMENT_H
#define SEVENSEGMENT_H

#define NUM_DISPLAYS 4

/*Macros that bind segments of the display to pins of the output port*/
#define SEGM_A          (1 << 5)
#define SEGM_B          (1 << 7) 
#define SEGM_C          (1 << 3)
#define SEGM_D          (1 << 1)
#define SEGM_E          (1 << 4)
#define SEGM_F          (1 << 6)
#define SEGM_G          (1 << 0)
#define DECIMAL_POINT   (1 << 2)


/*Macros that define combinations of segments as displayable characters*/
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
#define CHAR_E      (SEGM_A | SEGM_F | SEGM_G | SEGM_E | SEGM_D)
#define CHAR_DEBUG  (SEGM_E | SEGM_B)       //A special pattern for debugging purposes. Displayed if no valid translation exists for a byte.



#endif