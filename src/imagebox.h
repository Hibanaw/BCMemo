/**
 * @file imagebox.h
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __IMAGEBOX_H__
#define __IMAGEBOX_H__

#include "button.h"


typedef Button ImageBox;

void imageBox_draw(ImageBox *ib);
int imageBox_event(ImageBox *ib);
ImageBox imageBox_new(char *filePath, int x, int y);
void imageBox_fullScreen(char *filePath);

#include <graphics.h>
#include <svga.h>
#include "image.h"
#include "keyboard.h"
#endif