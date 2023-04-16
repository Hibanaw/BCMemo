/**
 * @file scroll.h
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __SCROLL_H__
#define __SCROLL_H__


enum ScrollBarStatus{
    ScrollBarDefault,
    ScrollBarFocused,
    ScrollBarSelected
};

typedef struct
{
    int posX;
    int posY;
    int height;
    int width;
    int length;
    enum ScrollBarStatus status;
    int barPosY1;
    int barPosY2;
    int mouseLastPosY;
    int sumItem;
    int inScreenItem;
    int ithItem;
    int lastDrawBarPosY1;
    int lastDrawBarPosY2;
}ScrollBar;

ScrollBar scrollBar_new(int x, int y, int h);
int scrollBar_event(ScrollBar *sb);
void scrollBar_draw(ScrollBar *sb);


#include <graphics.h>
#include "stdlib.h"
#include "global.h"
#include "mouse.h"
#include "svga.h"
#endif