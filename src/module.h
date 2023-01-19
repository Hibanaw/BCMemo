#ifndef _MODULE_H_
#define _MODULE_H_

#include<time.h>
#include<graphics.h>
#include<stdlib.h>
#include"svga.h"
#include"keyboard.h"
#include"hz.h"
#include"config.h"

#ifndef min
#define min(a,b) (a)<(b)?(a):(b)
#endif


typedef struct Button{
    int posX, posY;
    int width, height;
    int status;//1选中2点下
}Button;

typedef struct Textbox{
	int posX, posY;
	int width, height;
	char *text;
	int fontSize;
	int fontColor;
	int isFocused;
	int isMoveOn;
	int isHovered;
	int maxLength;
	int outLine;
	char *discription;
	int flicker;
	time_t flickerChangeTime;
	void *buffer;
}Textbox;

void *saveBg(int x1, int y1, int x2, int y2);

void drawButton(Button b);
void drawTextbox(Textbox t);
#endif