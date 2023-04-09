/**
 * @file imagebox.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "imagebox.h"

void imageBox_draw(ImageBox *ib){
    char *path = ib->content;
    int x1 = ib->posX1, y1 = ib->posY1, x2 = ib->posX2, y2 = ib->posY2;
    // if(x2 - x1 > 600){
    //     path = "";
    //     x2 = x1 + 64;
    //     y2 = y1 + 64;
    // }
    if(ib->status == -1){
        image_render(path, x1, y1);
        ib->status = 0;
    }
    switch(ib->status){
        case ButtonDefault:
            setcolor(_WHITE);
            setlinestyle(0, 0, 2);
            line(x1, y1, x1, y2);
            line(x1, y1, x2, y1);
            line(x1, y2, x2, y2);
            line(x2, y1, x2, y2);
            break;
        default:
            setcolor(hexff9f00);
            setlinestyle(0, 0, 2);
            line(x1, y1, x1, y2);
            line(x1, y1, x2, y1);
            line(x1, y2, x2, y2);
            line(x2, y1, x2, y2);
            break;
    }
}

int imageBox_event(ImageBox *ib){
    return button_event(ib);
}

ImageBox imageBox_new(char *filePath, int x, int y){
    ImageBox ib;
    int w, h;
	image_getSize(filePath, &w, &h);
	ib = button_new(x, y, x + w, y + h, filePath, imageBox_draw);
    ib.status = -1;
    return ib;
}