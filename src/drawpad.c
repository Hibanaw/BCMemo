/**
 * @file drawpad.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "drawpad.h"

int drawPad(char *saveFilePath){
    int px = 310, py = 80;
    int signal = 0;
    int color1 = _BLACK;
    int isDrawing = 0;
    int x0, y0;
    Button saveButton = button_new(680, 450, 780, 480, "±£´æ", button_drawWithText);
    mouse_hide();
    setfillstyle(1, hexfffbf0);
    bar(300, 70, 800, 500);
    setfillstyle(1, hexd4dfff);
    bar(308, 78, 792, 442);
    setfillstyle(1, _WHITE);
    bar(310, 80, 790, 440);
    button_draw(&saveButton);
    mouse_show();
    while(!signal){
        int k = bioskey(1);
        keybord_eat();
        mouse_update();
        if(keybord_isESCAPE(k)){
            bioskey(0);
            signal = -1;
        }
        if(mouse_isClickedInBox(310, 80, 790, 440) == 1){
            int x = mouse()->posX;
            int y = mouse()->posY;
            if(!isDrawing){
                isDrawing = 1;
                mouse()->visibility = 0;
                mouse_hide();
            }
            else{
                setcolor(color1);
                setlinestyle(0, 0, 3);
                line(x0, y0, x, y);
            }
            setfillstyle(1, color1);
            setcolor(color1);
            x0 = x;
            y0 = y;
        }
        else if(isDrawing){
            isDrawing = 0;
            mouse()->visibility = 1;
            mouse_show();
        }
        if(button_event(&saveButton)){
            signal = 1;
        }
    }
    switch (signal)
    {
    case -1:
        return 1;
        break;
    
    case 1:
        {
            FILE *fp;
            short w = 480, h = 360;
            int i, j;
			sprintf(saveFilePath, "data/img%05ld.bin", time(NULL)%100000);
            fp = fopen(saveFilePath, "wb");
            fwrite(&w, sizeof(short), 1, fp);
            fwrite(&h, sizeof(short), 1, fp);
            for(i = 0; i < h; i++){
                for(j = 0; j < w; j++){
					char c = getpixel(px+j, py+i);
                    fwrite(&c, 1, 1, fp);
                }
            }
            fclose(fp);
        }
        return 0;
        break;
    }
}