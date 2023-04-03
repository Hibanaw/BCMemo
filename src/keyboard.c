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

char keybord_bios2ascii(unsigned k){
	return (char)k&0xff;
}

int keybord_isAlphabet(unsigned k){
    char a = keybord_bios2ascii(k);
    return a >= 'a' && a <= 'z' || a >= 'A' && a <= 'Z';
}

int keybord_isCharacter(unsigned k){
    char a = keybord_bios2ascii(k);
    return a >= 32 && a <= 126;
}

int keybord_isESCAPE(unsigned k){
    return k == KEYESCAPE;
}

int keybord_isBACKSPACE(unsigned k){
    return k == KEYBACKSPACE;
}

int keybord_isControlOn(){
    return bioskey(2)&0x04;
}

void keybord_eat(){
    static k;
    int tk = bioskey(1);
    if(tk != 0 && tk == k){
        bioskey(0);
    }
    k = tk;
}