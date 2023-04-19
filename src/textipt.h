/**
 * @file textipt.h
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
    int align;
    void (*draw)(); 
}TextInput;

void textinput_draw(TextInput *tb);
void textinput_drawDefault(TextInput *tb);
int textinput_event(TextInput *ti);
TextInput textinput_newDefault(char *ds, int x1, int y1, int x2, int y2, char *buffer);
TextInput textinput_newTitle(char *ds, int x1, int y1, int x2, int y2, char *buffer);

#endif