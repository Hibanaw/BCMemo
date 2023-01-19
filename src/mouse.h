#ifndef _mouse_h_
#define _mouse_h_

#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdio.h>
#include<stdlib.h>
#include"svga.h"

#define MOUSEMAXX 1024
#define MOUSEMAXY 768

#ifndef _WIN32
#define min(a,b) (a)<(b)?(a):(b)
#define max(a,b) (a)>(b)?(a):(b)
#endif

/**
 * @brief 鼠标
 * 
 */
typedef struct{
    int posX, posY;
    enum{
        POINTERMOUSE = 0,
        SELECTMOUSE,
        TEXTMOUSE,
        CROSSMOUSE
        } style;
    int click;//点击
    union REGS regs;
    int flag;//可见性
    int release;//松开按键
}Mouse;

int mouse_press(int x1, int y1, int x2, int y2);//如果在???中点击，则返回1；在框中??点击，则返回2；不在???中则返??0
void mouse(int,int);//设???鼠??
void mouseinit(void);//初???化
//void mou_pos(int*,int*,int*);//更改鼠标位置
void mread(int *,int *,int*);//改坐标不??
void save_bk_mou(int x,int y);//存鼠标背??
void clrmous(int x,int y);//清除鼠标
void drawmous(int x,int y);//画鼠??
void newmouse(Mouse *m);   //更新鼠标

extern int MouseX;
extern int MouseY;
extern int MouseS;
extern int press;
extern union REGS regs;
#endif
