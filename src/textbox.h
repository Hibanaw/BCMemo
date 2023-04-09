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

enum TextboxMouseStatus{
	TextboxMouseDefault,
    TextboxMouseFocused,
    TextboxMouseClicked
};

typedef struct{
	char *defaultContent;
    int posX1;
    int posY1;
    int posX2;
    int posY2;
	char *content;
    int maxLength;
    FontFamily font;
	enum TextboxStatus status;
    enum TextboxMouseStatus mstatus;
    int cursorLocation;
    int cursorStatus;
	clock_t cursorLastBlink;
}Textbox;

void textbox_draw(Textbox *tb);
int textbox_event(Textbox *tb);
void textbox_determinState(Textbox *tb);
Textbox textbox_newDefault(char *ds, int x1, int y1, int x2, int y2, char *buffer);
Text textbox_convert2text(Textbox tb);
int textbox_getCursorPositionX(Textbox t);
int textbox_getCursorPositionY(Textbox t);
#endif