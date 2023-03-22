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
    setfillstyle(1,_GRAY);
    bar(x1+3, y1+3, x2+3, y2+3);
    switch (b->status)
    {
    case ButtonDefault:
        setfillstyle(1, _WHITE);
        bar(x1, y1, x2, y2);
        break;
    case ButtonFocused:
        setfillstyle(1, hexff9f00);
        bar(x1, y1, x2, y2);
        setfillstyle(1, _WHITE);
        bar(x1+2, y1+2, x2-2, y2-2);
        break;
    case ButtonSelected:
        setfillstyle(1, hexff9f00);
        bar(x1, y1, x2, y2);
        setfillstyle(1, hexffffaa);
        bar(x1+2, y1+2, x2-2, y2-2);
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
        log(DEBUG, "Button clicked.");
        b -> status = ButtonSelected;
        m -> style = CURSORSELECT;
        mouse_hide();
        thisdraw(b);
        mouse_show();
        return 0;
    }
    if(b -> status == ButtonSelected && s == 2){
        log(DEBUG, "Button released.");
        b -> status = ButtonDefault;
        m -> style = CURSORPOINTER;
        mouse_hide();
        thisdraw(b);
        mouse_show();
        return 1;
    }
    if(b -> status == ButtonDefault && s == 2){
        log(DEBUG, "Button focused.");
        b -> status = ButtonFocused;
        m -> style = CURSORSELECT;
        mouse_hide();
        thisdraw(b);
        mouse_show();
        return 0;
    }
    if(b -> status != ButtonDefault && s == 0){
        log(DEBUG, "Button disfocused.");
        b -> status = ButtonDefault;
        m -> style = CURSORPOINTER;
        mouse_hide();
        thisdraw(b);
        mouse_show();
        return 0;
    }
    return 0;
}
