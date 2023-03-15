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
	int x1 = b->posX1, y1 = b->posY1,
		x2 = b->posX2, y2 = b->posY2;
    setfillstyle(1,_GRAY);
    bar(x1+3, y1+3, x2+3, y2+3);
    setfillstyle(1, _WHITE);
    bar(x1, y1, x2, y2);
}

int button_event(Button *b){
    int s;
    int x1 = b -> posX1, y1 = b -> posY1,
        x2 = b -> posX2, y2 = b -> posY2;
    s = mouse_isClickedInBox(x1, y1, x2, y2);
    if(b -> status == ButtonFocused && s == 1){
        log(DEBUG, "Button clicked.");
        b -> status = ButtonSelected;
        button_draw(b);
        mouse_chunkUpdate();
        return 0;
    }
    if(b -> status == ButtonSelected && s == 2){
        log(DEBUG, "Button released.");
        b -> status = ButtonDefault;
        button_draw(b);
        mouse_chunkUpdate();
        return 1;
    }
    if(b -> status == ButtonDefault && s == 2){
        log(DEBUG, "Button focused.");
        b -> status = ButtonFocused;
        button_draw(b);
        mouse_chunkUpdate();
        return 0;
    }
    if(b -> status != ButtonDefault && s == 0){
        log(DEBUG, "Button disfocused.");
        b -> status = ButtonDefault;
        button_draw(b);
        mouse_chunkUpdate();
        return 0;
    }
    return 0;
}
