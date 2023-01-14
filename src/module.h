#ifndef _MODULE_H_
#define _MODULE_H_

#include<graphics.h>
#include"svga.h"
#include"keyboard.h"

typedef struct{
    int posX, posY;
    int width, height;
    int status;//1ѡ��2����
}Button;

typedef struct Textbox{
    char *str;
    int isFocused;
    int maxLength;
}Textbox;


#endif