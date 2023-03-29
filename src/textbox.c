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

void textbox_draw(Textbox *tb)
{
    int x1 = tb->posX1, y1 = tb->posY1,
        x2 = tb->posX2, y2 = tb->posY2;
    setfillstyle(1, _GRAY);
    bar(x1 + 3, y1 + 3, x2 + 3, y2 + 3);
    setfillstyle(1, _BLACK);
    bar(x1, y1, x2, y2);
    setfillstyle(1, _WHITE);
    bar(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
    if(strlen(tb->content)){
        Text t = text_newDefault(tb->content, x1, y1, x2, y2);
        t.font = tb->font;
        text_display(t);
    }
    else{
        Text t = text_newDefault(tb->defaultContent, x1, y1, x2, y2);
        t.font = tb->font;
        t.font.fontColor = _GRAY;
        text_display(t);
    }
}

int textbox_event(Textbox *tb)
{
    char *s = tb->content;
    Mouse *m = mouse();
    int mx = m->posX, my = m->posY;
    textbox_determinState(tb);
    if (tb->status == TextboxSelected)
    {
        //TODO: edit
        char olds[500], inss[20], olds1[500], olds2[500], finals[500];
        int cl = tb->cursorLocation;
        int i;
        int is;
        memset(inss, 0, sizeof(inss));
        memset(olds1, 0, sizeof(olds1));
        memset(olds2, 0, sizeof(olds2));
        memset(finals, 0, sizeof(finals));

        strcpy(olds, tb->content);
        for(i = 0; i < strlen(olds); i++){
            if(i < cl){
                olds1[i] = olds[i];
            }
            else{
                olds2[i-cl] = olds[i];
            }
        }
        is = ime_input(inss);
        if(strlen(olds) + strlen(inss) > tb->maxLength){
            return 0;
        }
        if(is == -1){
            olds1[MAX(0, cl-1)] = 0;
            strcat(finals, olds1);
            strcat(finals, olds2);
        }
        else{
            strcat(finals, olds1);
            strcat(finals, inss);
            strcat(finals, olds2);
        }
        if(strcmp(olds, finals)){
            strcpy(tb->content, finals);
            textbox_draw(tb);
        }
    }
}

void textbox_determinState(Textbox *tb)
{
    Textbox ltb = *tb;
    Mouse *m = mouse();
    int mx = m->posX, my = m->posY, mc = m->click;
    
    if (ltb.status == TextboxDefault && mouse_isClickedInBox(tb->posX1, tb->posY1, tb->posX2, tb->posY2) == 2)
    {
        tb->status = TextboxFocused;
        m->style = CURSORTEXT;
    }
    if (ltb.status == TextboxFocused && mouse_isClickedInBox(tb->posX1, tb->posY1, tb->posX2, tb->posY2) == 1)
    {
        tb->status = TextboxSelected;
        m->style = CURSORTEXT;
    }
    if (ltb.status != TextboxDefault && mouse_isClickedInBox(tb->posX1, tb->posY1, tb->posX2, tb->posY2) == 0)
    {
        tb->status = TextboxDefault;
        m->style = CURSORPOINTER;
    }
    // 在框里点，需要改变编辑器光标位置
    if (mouse_isClickedInBox(tb->posX1, tb->posY1, tb->posX2, tb->posY2) == 1)
    {
        int x = tb->posX1, y = tb -> posY1;
		int w = tb->posX2 - tb->posX1, h = tb->posY2 - tb->posY1;
        int row = CEILING(1.0 * y / (tb->font.fontSize + tb->font.rowSpacing));
        int colum = CEILING(1.0 * (mx - x) / (tb->font.fontSize + tb->font.spacing));
        int words_per_line = (w % (ltb.font.fontSize + ltb.font.spacing) / ltb.font.fontSize) + w / (ltb.font.fontSize + ltb.font.spacing);
        tb->cursorLocation = MIN(text_getLength(tb->content), (row - 1) * words_per_line + colum);
    }
}

Textbox textbox_newDefault(char *ds, int x1, int y1, int x2, int y2){
    Textbox tb;
    memset(&tb, 0, sizeof(tb));
    tb.defaultContent = ds;
    tb.font.fontSize = 24;
    tb.font.fontColor = _BLACK,
    tb.font.spacing = 2;
    tb.font.rowSpacing = 0;
    tb.posX1 = x1;
    tb.posX2 = x2;
    tb.posY1 = y1;
    tb.posY2 = y2;
    return tb;
}