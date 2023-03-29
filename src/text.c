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
            settextstyle(SANS_SERIF_FONT, HORIZ_DIR, fs/8);
            //setusercharsize(1, 1, 1, 1);
            setwritemode(COPY_PUT);
            outtextxy(tx+fs/10, ty-fs/4, s);
            tx+=d;
        }
        if((unsigned)*p > 0xA0){
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
        if((unsigned)*p == 0xA0){
            //TODO: emoji
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
            hz_puthz("��", tx, ty, fs, d, c);
            tx+=d;
        }
    }
}

int text_getLength(char *s){
    char *p = s;
    int l = 0;
    while(*p != 0){
        if((unsigned char) *p < 128){
            p++;
            l++;
        }
        else{
            p+=2;
            l++;
        }
    }
    return l;
}

Text text_newDefault(char *s, int x1, int y1, int x2, int y2){
    Text t;
    t.content = s;
    t.posX = x1;
    t.posY = y1;
    t.width = x2-x1,
    t.hight = y2-y1,
    t.font.fontSize = 24;
    t.font.fontColor = _BLACK,
    t.font.spacing = 2;
    t.font.rowSpacing = 0;
    return t;
}