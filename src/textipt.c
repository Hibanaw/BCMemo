/**
 * @file textinput.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "textipt.h"


void textinput_drawDefault(TextInput *ti)
{
    int x1 = ti->posX1, y1 = ti->posY1,
        x2 = ti->posX2, y2 = ti->posY2;
    setfillstyle(1, _GRAY);
    bar(x1 + 3, y1 + 3, x2 + 3, y2 + 3);
    setfillstyle(1, _BLACK);
    bar(x1, y1, x2, y2);
    setfillstyle(1, _WHITE);
    bar(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
    textbox_draw(&ti->textbox);
}

void textinput_drawTransparent(TextInput *ti){
    int x1 = ti->posX1, y1 = ti->posY1,
        x2 = ti->posX2, y2 = ti->posY2;
    setfillstyle(1, ti->textbox.bgColor);
    bar(x1, y1, x2, y2);
    textbox_draw(&ti->textbox);
}

int textinput_event(TextInput *ti){
    int k;
    int tl, l, ltl;
    if(ti->align == 1){
        ltl = text_getLength(ti->textbox.content);
        ltl = (ltl == 0)?text_getLength(ti->textbox.defaultContent) : ltl;
        l = ltl*(ti->textbox.font.fontSize + ti->textbox.font.spacing);
        if(ti->textbox.posX1 != ti->posX1 + (ti->posX2-ti->posX1 - l)/2){
            ti->textbox.posX1 = ti->posX1 + (ti->posX2-ti->posX1 - l)/2;
            // ti->textbox.posX2 = ti->textbox.posX1 + l + ti->textbox.font.fontSize + ti->textbox.font.spacing;
            mouse_hide();
            ti->draw(ti);
            mouse_show();
        }
        k = textbox_event(&ti->textbox);
        tl = text_getLength(ti->textbox.content);
        tl = (tl == 0)?text_getLength(ti->textbox.defaultContent) : tl;
        if(tl != ltl){
            l = tl*(ti->textbox.font.fontSize + ti->textbox.font.spacing);
            ti->textbox.posX1 = ti->posX1 + (ti->posX2-ti->posX1 - l)/2;
            // ti->textbox.posX2 = ti->textbox.posX1 + l + ti->textbox.font.fontSize + ti->textbox.font.spacing;
            mouse_hide();
            ti->draw(ti);
            mouse_show();
            return k;
        }
        else return k;
    }
    else{
        k = textbox_event(&ti->textbox);
    }
    return k;
}

TextInput textinput_newDefault(char *ds, int x1, int y1, int x2, int y2, char *buffer){
    Textbox tb;
    TextInput ti;
    memset(&tb, 0, sizeof(tb));
    tb = textbox_newDefault(ds, x1, y1, x2, y2, buffer);
    tb.status = TextboxDefault;
    tb.mstatus = TextboxMouseDefault;
    tb.cursorStatus = 0;
    tb.defaultContent = ds;
    tb.content = buffer;
    tb.maxLength = 10;
    tb.font.fontSize = 24;
    tb.font.fontColor = _BLACK,
    tb.font.spacing = 1;
    tb.font.rowSpacing = 0;
    tb.hint = '*';
    tb.type = TextboxText;
    tb.posX1 = x1+5;
    tb.posX2 = x2-5;
    tb.posY1 = y1+10;
    tb.posY2 = y2-10;
    ti.textbox = tb;
    ti.posX1 = x1;
    ti.posX2 = x2;
    ti.posY1 = y1;
    ti.posY2 = y2;
    ti.draw = textinput_drawDefault;
    ti.align = 0;
    return ti;
}

TextInput textinput_newTitle(char *ds, int x1, int y1, int x2, int y2, char *buffer){
    Textbox tb;
    TextInput ti;
    memset(&tb, 0, sizeof(tb));
    tb = textbox_newDefault(ds, x1, y1, x2, y2, buffer);
    tb.status = TextboxDefault;
    tb.mstatus = TextboxMouseDefault;
    tb.cursorStatus = 0;
    tb.defaultContent = ds;
    tb.content = buffer;
    tb.maxLength = 14;
    tb.font.fontSize = 24;
    tb.font.fontColor = _BLACK,
    tb.font.spacing = 2;
    tb.font.rowSpacing = 0;
    tb.hint = '*';
    tb.type = TextboxText;
    ti.textbox = tb;
    ti.posX1 = x1;
    ti.posX2 = x2;
    ti.posY1 = y1;
    ti.posY2 = y2;
    ti.draw = textinput_drawTransparent;
    ti.align = 1;
    return ti;
}