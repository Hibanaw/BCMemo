#include"keyboard.h"

char bk2ascii(unsigned k){
    return char(k&0xff);
}

int isAlphabet(unsigned k){
    return isAlphabet(bk2ascii(k));
}

int isAlphabet(char c){
    return c >= 'A' && c <='Z' || c >= 'a' && c <= 'z';
}

int isESCAPE(unsigned k){
    return k == ESCAPEKEY;
}
