/**
 * @file text.h
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-03-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __TEXT_H__
#define __TEXT_H__

#include <graphics.h>
#include "svga.h"
#include "hz.h"
#include "log.h"

typedef struct{
    int fontSize;
    int fontColor;
    int spacing;
    int rowSpacing;
}FontFamily;

typedef struct
{
    char *content;
    int posX;
    int posY;
    int width;
    int hight;
    FontFamily font;

}Text;


void text_display(Text *);

#endif