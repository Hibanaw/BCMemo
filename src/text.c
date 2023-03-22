/**
 * @file text.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-03-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "text.h"

void text_display(Text t){
	int x = t.posX, y = t.posY,
		w = t.width, h = t.hight;
	int c = t.font.fontColor;
	int tx = x, ty = y;
	int fs = t.font.fontSize;
	int d = t.font.fontSize + t.font.spacing;
	int rd = t.font.rowSpacing;
    char *p = t.content;
    log(LOG, "Start display text");
    while(*p != '\0'){
		char s[3] = {0, 0, 0};
        // printf("1");
        if((unsigned)*p < 128){
            //ascii
            s[0] = *p;
            p++;
            if(w && tx+d*0.6 > x+w){
                if(h && ty+ d + rd > y){
                    return;
                }
                tx = x;
                ty += rd;
            }
            setcolor(c);
            settextstyle(SANS_SERIF_FONT, HORIZ_DIR, fs/8-1);
            //setusercharsize(1, 1, 1, 1);
            setwritemode(COPY_PUT);
            outtextxy(tx, ty-2, s);
            tx+=d*0.6;
        }
        else{
            //gb2312
            s[0] = *p;
            p++;
            s[1] = *p;
            p++;
            if(w && tx+d > x+w){
                if(h && ty+ d + rd > y){
                    return;
                }
                tx = x;
                ty += rd;
            }
            hz_puthz(s, tx, ty, fs, d, c);
            tx+=d;
        }
    }
}