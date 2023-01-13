#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include<bios.h>

typedef enum spicalkey{
    ESCAPE = 0x011b
}spicalkey;

char bk2ascii(unsigned);


#endif