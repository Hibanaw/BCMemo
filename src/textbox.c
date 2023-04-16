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
    setfillstyle(1, _WHITE);
    bar(x1, y1, x2, y2);
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
        int wpl = ((w % (tb->font.fontSize + tb->font.spacing) > tb->font.fontSize) ? 1 : 0) + w / (tb->font.fontSize + tb->font.spacing);
        r = (loc-1) / wpl;
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
    int r = 0;
    textbox_determinState(tb);
    if(otbs != tb->status){
        mouse_hide();
        textbox_draw(tb);
        mouse_show();
    }
    //cursor blink
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
    //cursor position key
	if (tb->status == TextboxSelected){
        int k;
        if(k = bioskey(1)){
            switch(k){
                case KEYLEFT:
                    bioskey(0);
                    tb->cursorLocation--;
                    tb->cursorLocation = MAX(0, tb->cursorLocation);
                    break;
                case KEYRIGHT:
                    bioskey(0);
                    tb->cursorLocation++;
                    tb->cursorLocation = MIN(tb->cursorLocation, text_getLength(tb->content));
                    break;
                case KEYHOME:
                    bioskey(0);
                    tb->cursorLocation = 0;
                    break;
                case KEYEND:
                    bioskey(0);
                    tb->cursorLocation = text_getLength(tb->content);
                    break;
            }
            tb->cursorLastBlink = 0;
            tb->cursorStatus = 0;
            mouse_hide();
            textbox_draw(tb);
            mouse_show();
        }
    }
    if (tb->status == TextboxSelected){
        int k = bioskey(1);
        if(k == KEYENTER){
            bioskey(0);
            return 1;
        }
    }
    // input
    if (tb->status == TextboxSelected)
    {
        char olds[500], inss[20], olds1[500], olds2[500], finals[500];
        int cl = tb->cursorLocation;
        int i;
        int is;
        int clp;
        memset(inss, 0, sizeof(inss));
        memset(olds1, 0, sizeof(olds1));
        memset(olds2, 0, sizeof(olds2));
        memset(finals, 0, sizeof(finals));
        is = ime_input(inss, textbox_getCursorPositionX(*tb) + 20, textbox_getCursorPositionY(*tb) + 30);
        if(is == 0){
            return 0;
        }
        debug(DEBUG, inss);
        strcpy(olds, tb->content);
        clp = text_getNthChar(olds, cl) - olds;
        for(i = 0; i < strlen(olds); i++){
            if(i < clp ){
                olds1[i] = olds[i];
            }
            else{
                olds2[i-clp] = olds[i];
            }
        }
        if(text_getLength(olds) + text_getLength(inss) > tb->maxLength){
            return 0;
        }
        if(is == -1){
            if(cl != 0){
                *text_getNthChar(olds1, MAX(0, cl-1)) = 0;
            }
            else{
                r = 1;
            }
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
    if(r) return -1;
    return 0;
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
        int row = CEILING(1.0 * (my - y) / (tb->font.fontSize + tb->font.rowSpacing))-1;
        int colum = (int)(1.0 * (mx - x) / (tb->font.fontSize + tb->font.spacing)*2.0) - ((mx - x) / (tb->font.fontSize + tb->font.spacing));
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

Textbox textbox_newDefault(char *ds, int x1, int y1, int x2, int y2, char *buffer){
    Textbox tb;
    memset(&tb, 0, sizeof(tb));
    tb.status = TextboxDefault;
    tb.mstatus = TextboxMouseDefault;
    tb.cursorStatus = 0;
    tb.defaultContent = ds;
    tb.content = buffer;
    tb.maxLength = 150;
    tb.font.fontSize = 24;
    tb.font.fontColor = _BLACK,
    tb.font.spacing = 2;
    tb.font.rowSpacing = 2;
    tb.posX1 = x1;
    tb.posX2 = x2;
    tb.posY1 = y1;
    tb.posY2 = y2;
    return tb;
}

int textbox_getCursorPositionX(Textbox t){
    int p = t.cursorLocation;
    int w = t.posX2 - t.posX1;
    int rm = (w % (t.font.fontSize + t.font.spacing) / t.font.fontSize) + w / (t.font.fontSize + t.font.spacing);
    int r = p % rm ? p % rm : rm;
    if(!strlen(t.content)) r = 0;
    return t.posX1 + r * (t.font.fontSize + t.font.spacing);
}

int textbox_getCursorPositionY(Textbox t){
    int p = t.cursorLocation;
    int w = t.posX2 - t.posX1;
    int rm = (w % (t.font.fontSize + t.font.spacing) / t.font.fontSize) + w / (t.font.fontSize + t.font.spacing);
    int c = CEILING((float) p / rm)-1;
    if(!strlen(t.content)) c = 0;
    return t.posY1 +  c*(t.font.fontSize + t.font.rowSpacing);
}

Text textbox_convert2text(Textbox tb){
    Text t;
    t.hight = tb.posY2 - tb.posY1;
    t.width = tb.posX2 - tb.posX1;
    t.font = tb.font;
    t.content = tb.content;
    return t;
}