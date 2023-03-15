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
    enum ButtonStatus status;
}Button;


void button_draw(Button *);
int button_event(Button *);

#endif