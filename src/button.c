/**
 * @file button.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-02-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "button.h"


void button_draw(Button *b){
    b->draw(b);
}

void button_drawDefault(Button *b){
	int x1 = b->posX1, y1 = b->posY1,
		x2 = b->posX2, y2 = b->posY2;
    setfillstyle(1,_LIGHTGRAY);
    bar(x1, y1, x2, y2);
    switch (b->status)
    {
    case ButtonDefault:
        setfillstyle(1, hexfffbf0);
        bar(x1, y1, x2, y2-2);
        setfillstyle(1, _WHITE);
        bar(x1+1, y1+2, x2-1, y2-2);
        break;
    case ButtonFocused:
        setfillstyle(1, hexffdfaa);
        bar(x1, y1, x2, y2-2);
        setfillstyle(1, hexfffbf0);
        bar(x1+1, y1+2, x2-1, y2-2);
        break;
    case ButtonSelected:
        setfillstyle(1, hexffdfaa);
        bar(x1, y1, x2, y2-2);
        setfillstyle(1, hexfffbf0);
        bar(x1+1, y1+2, x2-1, y2-2);
        break;
    default:
        break;
    }
}

void button_drawWithText(Button *b){
    int x1 = b->posX1, y1 = b->posY1,
		x2 = b->posX2, y2 = b->posY2;
    Text t;
    t.content = b->content;
    t.posX = b->posX1+110;
    t.posY = b->posY1+15;
    t.width = 0,
    t.hight = 0,
    t.font.fontSize = 24;
    t.font.fontColor = _BLACK,
    t.font.spacing = 2;
    t.font.rowSpacing = 0;
    if(b->status == ButtonSelected){
        t.font.fontColor = hex555f55;
    }
    button_drawDefault(b);
	text_display(t);
}

int button_event(Button *b){
    int s;
    Mouse *m = mouse();
    int x1 = b -> posX1, y1 = b -> posY1,
        x2 = b -> posX2, y2 = b -> posY2;
	void (*thisdraw)() = button_draw;
    if(thisdraw == NULL){
        thisdraw = button_drawDefault;
    }
    s = mouse_isClickedInBox(x1, y1, x2, y2);
    if(b -> status == ButtonFocused && s == 1){
        debug(DEBUG, "Button clicked.");
        b -> status = ButtonSelected;
        m -> style = CURSORSELECT;
        mouse_hide();
        thisdraw(b);
        mouse_show();
        return 0;
    }
    if(b -> status == ButtonSelected && s == 2){
        debug(DEBUG, "Button released.");
        b -> status = ButtonDefault;
        m -> style = CURSORPOINTER;
        mouse_hide();
        thisdraw(b);
        mouse_show();
        return 1;
    }
    if(b -> status == ButtonDefault && s == 2){
        debug(DEBUG, "Button focused.");
        b -> status = ButtonFocused;
        m -> style = CURSORSELECT;
        mouse_hide();
        thisdraw(b);
        mouse_show();
        return 0;
    }
    if(b -> status != ButtonDefault && s == 0){
        debug(DEBUG, "Button disfocused.");
        b -> status = ButtonDefault;
        m -> style = CURSORPOINTER;
        mouse_hide();
        thisdraw(b);
        mouse_show();
        return 0;
    }
    return 0;
}

Button button_new(int x1, int y1, int x2, int y2, char *s, void (*f)()){
    Button b;
    memset(&b, 0, sizeof(b));
    b.posX1 = x1;
    b.posX2 = x2;
    b.posY1 = y1;
    b.posY2 = y2;
    b.content = s;
    b.draw = f;
    b.animationDrawedTick = 0;
    return b;
}


void button_checkboxAnimation(Button *cb){
    int x1, y1;
    x1 = cb->posX1;
    y1 = cb->posY1;
    if(cb->content){
        clock_t t = clock() - cb->animationStartTime;
        float k = t / (0.15 * CLK_TCK);
        if(k < 1){
            if(cb->animationDrawedTick == 0 || t - cb->animationDrawedTick > 0){
                mouse_hide();
                setcolor(_WHITE);
                setlinestyle(0, 1, 3);
                if(k > 0.1){
                    float p = MIN((k-0.1)/ 0.3, 1);
                    line(x1+5, y1 + 12, x1+5+p*3, y1 + 12+6*p);
                }
                if(k > 0.4)
                {
                    float p = (k-0.4)/ 0.7;
                    line(x1+8, y1 + 18, x1+8 + p*11, y1 + 18-p*12);
                }
                mouse_show();
                cb->animationDrawedTick = t;
            }
        }
        else if(cb->animationDrawedTick < 0.2 * CLK_TCK){
            mouse_hide();
            setlinestyle(0, 1, 3);
            setcolor(_WHITE);
            line(x1+5, y1 + 12, x1+8, y1 + 18);
            line(x1+8, y1 + 18, x1+19, y1 + 6);
            mouse_show();
            cb->animationDrawedTick = t;
        }
    }
}

int button_checkboxEvent(Button *cb){
	int k = button_event(cb);
    if(k){
        cb->content = !(int)cb->content;
    }
    if(k && cb->content == 1){
        cb->animationDrawedTick = 0;
        cb->animationTick = 0;
        cb->animationStartTime = clock();
    }
    button_checkboxAnimation(cb);
    return k;
}

void button_checkboxDraw(Button *cb){
    int x1, y1, x2, y2;
    int c0, c1, c2;
    x1 = cb->posX1;
    x2 = cb->posX2;
    y1 = cb->posY1;
    y2 = cb->posY2;
    switch ((int)cb->content)
    {
        case 0:
            switch (cb->status)
            {
                case ButtonDefault:
                    c0 = hex808080;
                    c1 = _WHITE;
                    break;
                case ButtonFocused:
                    c0 = hex808080;
                    c1 = hexfffbf0;
                    break;
                case ButtonSelected:
                    c0 = hexc0c0c0;
                    c1 = hexc0c0c0;
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
            break;
		case 1:
            switch (cb->status)
            {
                case ButtonDefault:
                    c0 = hexff7f00;
                    c2 = _WHITE;
                    break;
                case ButtonFocused:
                    c0 = hexff9f00;
                    c2 = _WHITE;
                    break;
                case ButtonSelected:
                    c0 = hexd47f00;
                    c2 = hexd4bfaa;
                    break;
            }
            setfillstyle(1, c0);
            setcolor(c0);
            bar(x1+5, y1, x2-5, y2);
            bar(x1, y1+5, x2, y2-5);
            pieslice(x1 + 5, y1 + 5, 90, 180, 5);
            pieslice(x1 + 5, y2 - 5, 180, 270, 5);
            pieslice(x2 - 5, y1 + 5, 0, 90, 5);
            pieslice(x2 - 5, y2 - 5, 270, 360, 5);
            if(cb->animationDrawedTick > 0.15*CLK_TCK){
                setcolor(c2);
                setlinestyle(0, 1, 3);
                line(x1+5, y1 + 12, x1+8, y1 + 18);
                line(x1+8, y1 + 18, x1+19, y1 + 6);
            }
    }
}