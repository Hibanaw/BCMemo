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
        int w, h;
        float k = 1;
		image_getSize(path, &w, &h);
        if(w>400 || h > 500){
            k = MIN((float) 400 / w, (float) 500 / h);
        }
        image_renderZoom(path, x1, y1, k);
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
    int k = button_event(ib);
    if(k == 1){
        if(clock() - ib->animationStartTime < 0.5*CLK_TCK){
            imageBox_fullScreen(ib->content);
            return 2;
        }
        else{
            ib->animationStartTime = clock();
        }
    }
    return k;
}

ImageBox imageBox_new(char *filePath, int x, int y){
    ImageBox ib;
    int w, h;
    float k;
	image_getSize(filePath, &w, &h);
    if(w>400 || h > 500){
        k = MIN((float) 400/w, (float) 500/h);
        w = k*w;
        h = k*h;
    }
	ib = button_new(x, y, x + w, y + h, filePath, imageBox_draw);
    ib.status = -1;
    return ib;
}

void imageBox_fullScreen(char *filePath){
    int x, y;
    int w, h;
    float scale = 1;
    image_getSize(filePath, &w, &h);
    while(1){
        char percentage[5];
        Button eb = button_newExitButton();
        Button greater = button_new(50, 5, 75, 30, "+", button_drawWINUI);
        Button smaller = button_new(90, 5, 115, 30, "-", button_drawWINUI);
        Text pt = text_newDefault(percentage, MAXWIDTH - 120, MAXHEIGHT - 50, MAXWIDTH, MAXHEIGHT);
        int signal = 0;
        sprintf(percentage, "%d%%", (int)(scale*100));
        pt.font.fontColor = _WHITE;
		x = (MAXWIDTH - scale*w) /2;
		y = (MAXHEIGHT - scale*h) /2;
        mouse_hide();
        setfillstyle(1, hex2a1f00);
        bar(0, 0, MAXWIDTH, MAXHEIGHT);
		image_renderZoom(filePath, x, y, scale);
        button_draw(&eb);
        button_draw(&greater);
        button_draw(&smaller);
        text_display(pt);
        mouse_show();
        while(1){
            int k = bioskey(1);
            keybord_eat();
            mouse_update();
            if(button_event(&eb)){
                return;
            }
            if(keybord_isESCAPE(k)){
                bioskey(0);
                return;
            }
            if(button_event(&greater)){
                if(scale <= 3){
                    scale *= 1.2;
                    break;
                }
            }
            if(button_event(&smaller)){
                if(scale >= 0.3){
                    scale /= 1.2;
                    break;
                }
            }
        }
    }
}