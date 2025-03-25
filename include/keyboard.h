#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "stdint.h"

typedef enum
{
    KEYPRESS_1 = 0x02,
    KEYPRESS_2 = 0x03,
    KEYPRESS_3 = 0x04,
    KEYPRESS_4 = 0x05,
    KEYPRESS_5 = 0x06,
    KEYPRESS_6 = 0x07,
    KEYPRESS_7 = 0x08,
    KEYPRESS_8 = 0x09,
    KEYPRESS_9 = 0x0A,
    KEYPRESS_0 = 0x0B,
    KEYPRESS_BACKSPACE = 0x0E,
    KEYPRESS_TAB = 0x0F,
    KEYPRESS_q = 0x10,
    KEYPRESS_w = 0x11,
    KEYPRESS_e = 0x12,
    KEYPRESS_r = 0x13,
    KEYPRESS_t = 0x14,
    KEYPRESS_y = 0x15,
    KEYPRESS_u = 0x16,
    KEYPRESS_i = 0x17,
    KEYPRESS_o = 0x18,
    KEYPRESS_p = 0x19,
    KEYPRESS_ENTER = 0x1C,
    KEYPRESS_a = 0x1E,
    KEYPRESS_s = 0x1F,
    KEYPRESS_d = 0x20,
    KEYPRESS_f = 0x21,
    KEYPRESS_g = 0x22,
    KEYPRESS_h = 0x23,
    KEYPRESS_j = 0x24,
    KEYPRESS_k = 0x25,
    KEYPRESS_l = 0x26,
    KEYPRESS_z = 0x2C,
    KEYPRESS_x = 0x2D,
    KEYPRESS_c = 0x2E,
    KEYPRESS_v = 0x2F,
    KEYPRESS_b = 0x30,
    KEYPRESS_n = 0x31,
    KEYPRESS_m = 0x32,
    KEYPRESS_SPACE = 0x39,
    
} keyboard_scan;

uint8    read_char(void);

#endif