/**
 * @file textbox.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-03-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "textbox.h"

void textbox_draw(Textbox *t){
    int x1 = t->posX1, y1 = t->posY1,
    x2 = t->posX2, y2 = t->posY2;
    setfillstyle(1,_GRAY);
    bar(x1+3, y1+3, x2+3, y2+3);
    setfillstyle(1, _BLACK);
    bar(x1, y1, x2, y2);
    setfillstyle(1, _WHITE);
    bar(x1+1, y1+1, x2-1, y2-1);
}

int textbox_event(Textbox *t){

}