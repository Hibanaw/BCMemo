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

void textbox_drawDefault(Textbox *tb){
    Text t;
    t.content = tb->content;
    t.posX = tb->posX1;
    t.posY = tb->posY1;
    t.width = tb->posX2-tb->posX1;
    t.hight = tb->posY2-tb->posY1;
    t.font = tb->font;
    t.font.fontColor = _GRAY;
    text_display(t);
}

void textbox_drawText(Textbox *tb){
    Text t;
    t.content = tb->content;
    t.posX = tb->posX1;
    t.posY = tb->posY1;
    t.width = tb->posX2-tb->posX1;
    t.hight = tb->posY2-tb->posY1;
    t.font = tb->font;
    text_display(t);
}

int textbox_event(Textbox *tb){
    char *s = tb->content;
    // if(mouse_isClickedInBox(tb->posX1, tb->posY1, tb->posX2, tb->posY2)){
    //     if(mouse()->style != CURSORTEXT)
    //     mouse()->style = CURSORTEXT;
    // }
    // else{
    //     if(mouse()->style != CURSORPOINTER)
    //     mouse()->style = CURSORPOINTER;
    // }
    if(mouse_isClickedInBox(tb->posX1, tb->posY1, tb->posX2, tb->posY2) == 1){
        hz_input(tb->posX1, tb->posY2, tb->posX1+100, tb->posY2+40, s, 10, _WHITE, _BLACK, 32);
    }
}