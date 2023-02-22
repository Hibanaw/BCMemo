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
    ESCAPEKEY = 0x011b,
    BACKSPACEKEY = 0xe08,
    ENTERKEY = 0x1c0d
};

int keybord_getKey();
char keybord_bios2ascii(unsigned);
int keybord_isAlphabet(unsigned);
int keybord_isESCAPE(unsigned);

#endif