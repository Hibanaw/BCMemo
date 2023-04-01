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
    if(tb->status == TextboxSelected){
        int c, r;
        int lx , ly;
        int loc = tb->cursorLocation;
        int w = tb->posX2 - tb->posX1;
        int wpl = (w % (tb->font.fontSize + tb->font.spacing) / tb->font.fontSize) + w / (tb->font.fontSize + tb->font.spacing);
        r = (loc+1) / wpl;
        c = loc - r*wpl;
        ly = r * (tb->font.fontSize+tb->font.rowSpacing) + tb->posY1;
        lx = c * (tb->font.fontSize+tb->font.spacing) + tb->font.spacing / 2 + tb->posX1;
        setcolor(tb->cursorStatus ? _BLACK : _WHITE);
        setlinestyle(0, 1, 5);
        line(lx, ly+2, lx, ly+tb->font.fontSize-2);
    }
}

int textbox_event(Textbox *tb)
{
    int otbs = tb->status;
    char *s = tb->content;
    Mouse *m = mouse();
    int mx = m->posX, my = m->posY;
    int change = 0;
    textbox_determinState(tb);
    if(otbs != tb->status){
        mouse_hide();
        textbox_draw(tb);
        mouse_show();
    }
    if (tb->status == TextboxSelected){
        clock_t lt, nt, dt;
        nt = clock();
        lt = tb->cursorLastBlink;
        dt = nt - lt;
        if(dt / CLK_TCK >= 0.6){
            tb->cursorLastBlink = nt;
            tb->cursorStatus = !tb->cursorStatus;
            mouse_hide();
            textbox_draw(tb);
            mouse_show();
        }
    }
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
        is = ime_input(inss);
        if(is == 0){
            return 0;
        }
        log(DEBUG, inss);
        strcpy(olds, tb->content);
        for(i = 0; i < strlen(olds); i++){
            if(i < cl){
                olds1[i] = olds[i];
            }
            else{
                olds2[i-cl] = olds[i];
            }
        }
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
            tb->cursorLocation += is;
            mouse_hide();
            textbox_draw(tb);
            mouse_show();
        }
    }
}

void textbox_determinState(Textbox *tb)
{
    Textbox ltb = *tb;
    Mouse *m = mouse();
    int mx = m->posX, my = m->posY, mc = m->click;
    
    if (ltb.mstatus == TextboxMouseDefault && mouse_isClickedInBox(tb->posX1, tb->posY1, tb->posX2, tb->posY2) > 0)
    {
        tb->mstatus = TextboxMouseFocused;
        m->style = CURSORTEXT;
    }
    if (ltb.mstatus != TextboxMouseDefault && mouse_isClickedInBox(tb->posX1, tb->posY1, tb->posX2, tb->posY2) == 0)
    {
        tb->mstatus = TextboxMouseDefault;
        m->style = CURSORPOINTER;
    }
    if(ltb.mstatus == TextboxMouseClicked && mouse_isClickedInBox(tb->posX1, tb->posY1, tb->posX2, tb->posY2) != 1){
        tb->mstatus = TextboxMouseFocused;
    }
    // 在框里点，需要改变编辑器光标位置
    if (mouse_isClickedInBox(tb->posX1, tb->posY1, tb->posX2, tb->posY2) == 1 && tb->mstatus != TextboxMouseClicked)
    {
        int x = tb->posX1, y = tb -> posY1;
		int w = tb->posX2 - tb->posX1, h = tb->posY2 - tb->posY1;
        int row = CEILING(1.0 * (my-y) / (tb->font.fontSize + tb->font.rowSpacing))-1;
        int colum = CEILING(1.0 * (mx - x) / (tb->font.fontSize + tb->font.spacing));
        int words_per_line = (w % (ltb.font.fontSize + ltb.font.spacing) / ltb.font.fontSize) + w / (ltb.font.fontSize + ltb.font.spacing);
        tb->status = TextboxSelected;
        tb->cursorLocation = MIN(text_getLength(tb->content), row * words_per_line + colum);
        tb->cursorLastBlink = 0;
        tb->cursorStatus = 0;
        tb->mstatus = TextboxMouseClicked;
    }
    if (tb->status == TextboxSelected &&mouse_isClickedInBox(tb->posX1, tb->posY1, tb->posX2, tb->posY2) == -1){
        tb->status = TextboxDefault;
    }
}

Textbox textbox_newDefault(char *ds, int x1, int y1, int x2, int y2){
    Textbox tb;
    memset(&tb, 0, sizeof(tb));
    tb.status = TextboxDefault;
    tb.mstatus = TextboxMouseDefault;
    tb.cursorStatus = 0;
    tb.defaultContent = ds;
    tb.maxLength = 100;
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