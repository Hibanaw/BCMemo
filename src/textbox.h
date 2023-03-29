/**
 * @file textbox.h
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-03-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __TEXTBOX_H__
#define __TEXTBOX_H__

#include <string.h>
#include <time.h>
#include "global.h"
#include "text.h"
#include "ime.h"

enum TextboxStatus{
    TextboxDefault,
    TextboxFocused,
    TextboxSelected
};

typedef struct{
	const char * defaultContent;
    int posX1;
    int posY1;
    int posX2;
    int posY2;
	char content[500];
    int maxLength;
    FontFamily font;
	enum TextboxStatus status;
    int cursorLocation;
    int cursorStatus;
	clock_t cursorLastBlink;
}Textbox;

void textbox_determinState(Textbox *tb);
Textbox textbox_newDefault(char *ds, int x1, int y1, int x2, int y2);

#endif