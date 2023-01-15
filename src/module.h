#ifndef _MODULE_H_
#define _MODULE_H_

#include<time.h>
#include<graphics.h>
#include"svga.h"
#include"keyboard.h"
#include"hz.h"


typedef struct{
    int posX, posY;
    int width, height;
    int status;//1选中2点下
}Button;

typedef struct{
    int posX, posY;
    int width, height;
    char *text;
    int fontSize;
    int fontColor;
    int isFocused;
    int maxLength;
    int outLine;
    char *discription;
    int flicker;
    long flickerChangeTime;//clock()*10/CLK_TCK
}Textbox;

void drawButton(Button b);
void drawTextbox(Textbox t);
#endif