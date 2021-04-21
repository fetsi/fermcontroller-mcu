#include "dispcont.h"
#include "sevensegment.h"


char translate_fdup_7segm(dispcombo_t *displays) {

    for(unsigned char i = 0; i < NUM_DISPLAYS; ++i) {
        switch(displays->disp_arr[i].character) {
            case 0x0:
                //Empty display
                break;
            case 0x10:
                displays->disp_arr[i].character = CHAR_0;
                break;
            case 0x11:
                displays->disp_arr[i].character = CHAR_1;
                break;
            case 0x12:
                displays->disp_arr[i].character = CHAR_2;
                break;
            case 0x13:
                displays->disp_arr[i].character = CHAR_3;
                break;
            case 0x14:
                displays->disp_arr[i].character = CHAR_4;
                break;
            case 0x15:
                displays->disp_arr[i].character = CHAR_5;
                break;
            case 0x16:
                displays->disp_arr[i].character = CHAR_6;
                break;
            case 0x17:
                displays->disp_arr[i].character = CHAR_7;
                break;
            case 0x18:
                displays->disp_arr[i].character = CHAR_8;
                break;
            case 0x19:
                displays->disp_arr[i].character = CHAR_9;
                break;
            case 0x1A:
                displays->disp_arr[i].character = CHAR_A;
                break;
            case 0x1B:
                displays->disp_arr[i].character = CHAR_C;
                break;
            case 0x1C:
                displays->disp_arr[i].character = CHAR_E;
                break; 
            case 0x1D:
                displays->disp_arr[i].character = CHAR_F;
                break;
            case 0x1E:
                displays->disp_arr[i].character = CHAR_H;
                break;
            case 0x1F:
                displays->disp_arr[i].character = CHAR_I;
                break;
            case 0x20:
                displays->disp_arr[i].character = CHAR_J;
                break;
            case 0x21:
                displays->disp_arr[i].character = CHAR_L;
                break;
            case 0x22:
                displays->disp_arr[i].character = CHAR_O;
                break;
            case 0x23:
                displays->disp_arr[i].character = CHAR_P;
                break;
            case 0x24:
                displays->disp_arr[i].character = CHAR_S;
                break;
            case 0x25:
                displays->disp_arr[i].character = CHAR_U;
                break;
            case 0x26:
                displays->disp_arr[i].character = CHAR_MINUS;
                break;
            default:
                displays->disp_arr[i].character = CHAR_DEBUG;
                break;
        }
        if(displays->disp_arr[i].dp) {
            displays->disp_arr[i].character |= DECIMAL_POINT;
        }
    }
    return 0;
}