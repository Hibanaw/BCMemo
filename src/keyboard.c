/**
 * @file keyboard.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-02-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include"keyboard.h"

int keybord_getKey(){
    return bioskey(1) ? bioskey(0) : 0;
}

char keybord_bios2ascii(unsigned k){
	return (char)k&0xff;
}

int keybord_isAlphabet(unsigned k){
    char a = keybord_bios2ascii(k);
    return a >= 'a' && a <= 'z' || a >= 'A' && a <= 'Z';
}

int keybord_isESCAPE(unsigned k){
    return k == KEYESCAPE;
}

int keybord_isBACKSPACE(unsigned k){
    return k == KEYBACKSPACE;
}