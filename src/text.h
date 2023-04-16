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


void text_display(Text);
int text_getLength(char *s);
Text text_newDefault(char *s, int x1, int y1, int x2, int y2);
char *text_getNthChar(char *s, int n);
int text_getHeight(Text t);


#include <graphics.h>
#include "svga.h"
#include "hz.h"
#include "debug.h"
#endif