#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include<bios.h>

typedef enum spicalkey{
    ESCAPEKEY = 0x011b,
    BACKSPACEKEY = 0xe08,
    ENTERKEY = 0x1c0d
}spicalkey;

char bk2ascii(unsigned);
int isAlphabet(unsigned);
int isAlphabet(char);
int isESCAPE(unsigned);

#endif