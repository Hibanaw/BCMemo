/**
 * @file keyboard.h
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-02-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include<bios.h>

enum spicalkey{
    KEYESCAPE = 0x011b,
    KEYBACKSPACE = 0xe08,
    KEYSPACE = 0x3920,
    KEYENTER = 0x1c0d,
    KEYUP = 0x4800,
    KEYLEFT = 0x4b00,
    KEYRIGHT = 0x4d00,
    KEYDOWN = 0x5000,
    KEYONE = 0x0231,
    KEYTWO = 0x0332,
    KEYTHREE = 0x0433,
    KEYFOUR = 0x0534
};

int keybord_getKey();
char keybord_bios2ascii(unsigned);
int keybord_isAlphabet(unsigned);
int keybord_isESCAPE(unsigned);
int keybord_isBACKSPACE(unsigned);

#endif