/**
 * @file router.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "router.h"

Router router_new(){
	Router r;
    memset(&r, 0, sizeof(r));
    r.expandButton = button_new(10, 35, 65, 65, "", router_button_drawExpandButton);
    r.newMemoButton = button_new(20, 600, 55, 635, "", router_button_drawNewMemoButton);
	sprintf(r.memoName, "%06ld", time(NULL)%1000000);
    router_refresh(&r);
    return r;
}

void router_draw(Router *r){
	button_draw(&r->expandButton);
    button_draw(&r->newMemoButton);
}

int router_expand(Router *r){
    Memo *p, *ep;
    Button mb[10];
    char *jumpPath;
    int i;
    int lc = 0;
    ScrollBar sb = scrollBar_new(333, 100, 435);
    sb.bgColor = hexfffbf0;
    router_refresh(r);
    while(1){
        int signal = 0;
        int exitflag = 0;
        sb.ithItem = memos_getNum(r->topMemo);
        sb.sumItem = memos_getSum();
        for(i = 0, p = r->topMemo; i < 6 && p != NULL; i++, p = p->next){
            mb[i] = button_new(10, 100+75*i , 330, 160+75*i , p, router_button_drawMemoList);
        }
        ep = memos_preMemo(p);
        lc = i;
        sb.inScreenItem = lc;
		scrollBar_event(&sb);
        mouse_hide();
        setfillstyle(1, hexfffbf0);
        bar(0, 0, 350, MAXHEIGHT);
        setcolor(hexd4dfff);
        setlinestyle(0, 1, 2);
        line(350, 0, 350, MAXHEIGHT);
        button_draw(&r->expandButton);
        button_draw(&r->newMemoButton);
        for(i = 0; i < lc; i++){
            button_draw(mb+i);
        }
        scrollBar_draw(&sb);
        mouse_show();
        digitalClock_getTime();
        while(!signal){
            int k = bioskey(1);
            int sbs = scrollBar_event(&sb);
            keybord_eat();
            mouse_update();
            digitalClock_getTime();
            for(i = 0; i < lc; i++){
                int k;
                k = button_event(mb+i);
                if(k){
                    jumpPath = ((Memo *)((mb+i)->content))->fileName;
                    signal = 3;
                }
            }
            if(button_event(&r->expandButton)){
                signal = 1;
            }
            if(button_event(&r->newMemoButton)){
                signal = 2;
            }
            if(exitflag == 1 && mouse_isClickedInBox(350, 0, MAXWIDTH, MAXHEIGHT) == 2){
                signal = 1;
            }
            if(mouse_isClickedInBox(350, 0, MAXWIDTH, MAXHEIGHT) == 1){
                exitflag = 1;
            }
            else{
                exitflag = 0;
            }
            if(keybord_isESCAPE(k)){
                bioskey(0);
                signal = 1;
            }
            switch (sbs)
            {
            case 1:
                if(r->topMemo->next != ep){
                    r->topMemo = r->topMemo->next;
                    signal = 4;
                }
                break;
            
            case -1:
                if(r->topMemo != memos()->head){
                    r->topMemo = memos_preMemo(r->topMemo);
                    signal = 4;
                }
                break;
            }
        }
        switch (signal)
        {
        case 1:
            return 0;
            break;
        case 2:
			sprintf(r->memoName, "%06ld", time(NULL)%1000000);
            return RouterChangeMemo;
            break;
        case 3:
            if(strcmp(r->memoName, jumpPath)){
                strcpy(r->memoName, jumpPath);
                return RouterChangeMemo;
            }
            else{
                break;
            }
        case 4:
            break;
        default:
            break;
        }
    }
}

int router_event(Router *r){
    int k;
    if(button_event(&r->expandButton))
        return RouterExpand;
    if(button_event(&r->newMemoButton)){
        sprintf(r->memoName, "%06ld", time(NULL)%1000000);
        return RouterChangeMemo;
    }
    return 0;
}

void router_getWidgetList(Router *r){
    Memo *p = r->topMemo;
    int i;
    for(i = 0; i < 10 && p != NULL; i++, p = p->next){
        // r->memoButton[i] = button_new(0, i, 10, j, "", 1);
    }
}

void router_button_drawMemoList(Button *b){
    int c0, c1, ct;
    int x1 = b->posX1, y1 = b->posY1,
        x2 = b->posX2, y2 = b->posY2;
    char *name = ((Memo *)(b->content))->fileName;
    char *owner = ((Memo *)(b->content))->owner;
    Text t, t2;
    t.content = ((Memo *)(b->content))->title;
    t.content = ((*t.content == 0) ? "ÎÞ±êÌâ" : t.content);
    t.width = 0,
    t.hight = 0,
    t.font.fontColor = _BLACK,
    t.font.rowSpacing = 0;
    t.posY = y1 + 10;
    t2 = t;
    t2.content = owner;
	t2.posY = y1 + 35;
    t2.font.spacing = 0;
    t2.font.fontSize = 16;
    t2.posX = x2-text_getLength(t2.content)*(16)-10;
    if(text_getLength(t.content) > 10){
        t.font.fontSize = 16;
        t.font.spacing = 0;
        t.posX = x2-text_getLength(t.content)*(16)-10;
        t.posY = y1 + 15;
    }
    else{
        t.font.fontSize = 24;
        t.font.spacing = -2;
        t.posX = x2-text_getLength(t.content)*(24-2)-10;
    }
    
    if(!strcmp(name, memo()->fileName)){
        switch (b->status)
        {
            case ButtonDefault:
                c1 = hexff7f00;
                c0 = hex808080;
                ct = _WHITE;
                break;
            case ButtonFocused:
                c1 = hexff9f00;
                c0 = hex808080;
                ct = _WHITE;
                break;
            case ButtonSelected:
                c1 = hexc0c0c0;
                c0 = hexfffbf0;
                ct = hexfffbf0;
                break;
        }
        setfillstyle(1, c1);
        setcolor(c1);
        bar(x1+5, y1, x2-5, y2);
        bar(x1, y1+5, x2, y2-5);
        pieslice(x1 + 5, y1 + 5, 90, 180, 5);
        pieslice(x1 + 5, y2 - 5, 180, 270, 5);
        pieslice(x2 - 5, y1 + 5, 0, 90, 5);
        pieslice(x2 - 5, y2 - 5, 270, 360, 5);
        setcolor(c0);
        setlinestyle(0, 1, 2);
        line(x1 + 5, y1, x2 - 5, y1);
        line(x1 + 5, y2, x2 - 5, y2);
        line(x1, y1 + 5, x1, y2 - 5);
        line(x2, y1 + 5, x2, y2 - 3);
        arc(x1 + 5, y1 + 5, 90, 180, 5);
        arc(x1 + 5, y2 - 5, 180, 270, 5);
        arc(x2 - 5, y1 + 5, 0, 90, 5);
        arc(x2 - 5, y2 - 5, 270, 360, 5);
        t.font.fontColor = ct;
        t2.font.fontColor = ct;
        text_display(t);
        text_display(t2);
    }
    else{
        switch (b->status)
        {
            case ButtonDefault:
                c1 = _WHITE;
                c0 = hex808080;
                ct = _BLACK;
                break;
            case ButtonFocused:
                c1 = hexfffbf0;
                c0 = hex555f55;
                ct = _BLACK;
                break;
            case ButtonSelected:
                c0 = hex555f55;
                c1 = hexaa9faa;
                ct = hexfffbf0;
                break;
        }
        setfillstyle(1, c1);
        setcolor(c1);
        bar(x1+5, y1, x2-5, y2);
        bar(x1, y1+5, x2, y2-5);
        pieslice(x1 + 5, y1 + 5, 90, 180, 5);
        pieslice(x1 + 5, y2 - 5, 180, 270, 5);
        pieslice(x2 - 5, y1 + 5, 0, 90, 5);
        pieslice(x2 - 5, y2 - 5, 270, 360, 5);
        setcolor(c0);
        setlinestyle(0, 1, 2);
        line(x1 + 5, y1, x2 - 5, y1);
        line(x1 + 5, y2, x2 - 5, y2);
        line(x1, y1 + 5, x1, y2 - 5);
        line(x2, y1 + 5, x2, y2 - 3);
        arc(x1 + 5, y1 + 5, 90, 180, 5);
        arc(x1 + 5, y2 - 5, 180, 270, 5);
        arc(x2 - 5, y1 + 5, 0, 90, 5);
        arc(x2 - 5, y2 - 5, 270, 360, 5);
        t.font.fontColor = ct;
        t2.font.fontColor = ct;
        text_display(t);
        text_display(t2);
    }
}

void router_distrcut(){
    Memo *p, *q;
    p = memos()->head;
    while(p->next != NULL){
        q = p->next->next;
        free(p->next);
        p->next = q;
    }
    memset(memos(), 0, sizeof(Memos));
}

void router_refresh(Router *r){
    memos_getList(appData()->currentUser);
	r->topMemo = memos()->head;
}

void router_button_drawExpandButton(Button *b){
    int x1 = b->posX1, x2 = b->posX2,
        y1 = b->posY1, y2 = b->posY2;
    int lx1, ly1, lw, lh;
    setfillstyle(1, hexfffbf0);
    bar(x1, y1, x2, y2);
    if(b->status == ButtonSelected || b->status == ButtonFocused){
        setcolor(hexd4dfff);
        setlinestyle(0, 1, 2);
        line(x1 + 5, y1, x2 - 5, y1);
        line(x1 + 5, y2, x2 - 5, y2);
        line(x1, y1 + 5, x1, y2 - 5);
        line(x2, y1 + 5, x2, y2 - 3);
        arc(x1 + 5, y1 + 5, 90, 180, 5);
        arc(x1 + 5, y2 - 5, 180, 270, 5);
        arc(x2 - 5, y1 + 5, 0, 90, 5);
        arc(x2 - 5, y2 - 5, 270, 360, 5);
    }
    if(b->status == ButtonDefault || b->status == ButtonFocused){
        lw = 25;
        lh = 10;
        
    }
    else{
        lw = 15;
        lh = 10;
    }
    lx1 = b->posX1 + (b->posX2 - b->posX1 - lw)/2;
    ly1 = b->posY1 + (b->posY2 - b->posY1 - lh)/2;
    setcolor(_GRAY);
    line(lx1, ly1, lx1+lw, ly1);
    line(lx1, ly1+lh/2, lx1+lw, ly1+lh/2);
    line(lx1, ly1+lh, lx1+lw, ly1+lh);
}

void router_button_drawNewMemoButton(Button *b){
    int x1 = b->posX1, x2 = b->posX2,
        y1 = b->posY1, y2 = b->posY2;
    int lx1, ly1, lw, lh;
    setfillstyle(1, hexfffbf0);
    bar(x1, y1, x2, y2);
    if(b->status == ButtonSelected || b->status == ButtonFocused){
        setcolor(hexd4dfff);
        setlinestyle(0, 1, 2);
        line(x1 + 5, y1, x2 - 5, y1);
        line(x1 + 5, y2, x2 - 5, y2);
        line(x1, y1 + 5, x1, y2 - 5);
        line(x2, y1 + 5, x2, y2 - 3);
        arc(x1 + 5, y1 + 5, 90, 180, 5);
        arc(x1 + 5, y2 - 5, 180, 270, 5);
        arc(x2 - 5, y1 + 5, 0, 90, 5);
        arc(x2 - 5, y2 - 5, 270, 360, 5);
    }
    setcolor(_GRAY);
    setlinestyle(0, 1, 2);
    line((x1+x2)/2, (y1+y2)/2-10, (x1+x2)/2, (y1+y2)/2+10);
    line((x1+x2)/2-10, (y1+y2)/2, (x1+x2)/2+10, (y1+y2)/2);
}
void router_button_drawUserButton(Button *b)
{
     int x1 = b->posX1+3, x2 = b->posX2-3,
        y1 = b->posY1+3, y2 = b->posY2-3;
    int x3,x4,y3,y4;
    float k=0.8;
    float r;
    button_drawWINUI(b);
     if (b->status != ButtonSelected)
    {
        k = 1;
    }
    else
    {
        k = 0.8;
    }
    x3 = (x1 + x2) / 2 - (x2 - x1) * k / 2;
    x4 = (x1 + x2) / 2 + (x2 - x1) * k / 2;
    y3 = (y1 + y2) / 2 - (y2 - y1) * k / 2;
    y4 = (y1 + y2) / 2 + (y2 - y1) * k / 2;
    r=(y4-y3)/2;
    setcolor(_BLACK);
    setlinestyle(0,1,2);
    circle((x3+x4)/2,(y3+y4)/2,r);
    circle((x3+x4)/2,(y3+y4)/2-(r/4),r/4);
    arc((x3+x4)/2,(y3+y4)/2+r,30,150,r);
}