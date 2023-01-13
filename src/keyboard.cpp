#include"keyboard.h"

char bk2ascii(unsigned k){
    char c;
    c = k & 256;
    return c;
}