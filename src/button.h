/**
 * @file button.h
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-02-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <graphics.h>
#include "global.h"
#include "svga.h"
#include "mouse.h"
#include "button.h"
#include "text.h"

enum ButtonStatus{
    ButtonDefault,
    ButtonFocused,
    ButtonSelected
};

typedef struct Button{
    int posX1;
    int posY1;
    int posX2;
    int posY2;
    char *content;
    enum ButtonStatus status;
	void (*draw)();
}Button;

void button_draw(Button *);
void button_drawDefault(Button *);
void button_drawWithText(Button *);
int button_event(Button *);

#endif