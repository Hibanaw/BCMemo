/**
 * @file textinput.h
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __TEXTBOX__
#define __TEXTBOX__

#include "textbox.h"

typedef struct{
    int posX1;
    int posY1;
    int posX2;
    int posY2;
    Textbox textbox;
}TextInput;

void textinput_drawDefault(TextInput *tb);
TextInput textinput_newDefault(char *ds, int x1, int y1, int x2, int y2, char *buffer);

#endif