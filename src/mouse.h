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
 * @brief ���
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
    int click;//���
    union REGS regs;
    int flag;//�ɼ���
    int release;//�ɿ�����
}Mouse;

int mouse_press(int x1, int y1, int x2, int y2);//�����???�е�����򷵻�1���ڿ���??������򷵻�2������???����??0
void mouse(int,int);//��???��??
void mouseinit(void);//��???��
//void mou_pos(int*,int*,int*);//�������λ��
void mread(int *,int *,int*);//�����겻??
void save_bk_mou(int x,int y);//����걳??
void clrmous(int x,int y);//������
void drawmous(int x,int y);//����??
void newmouse(Mouse *m);   //�������

extern int MouseX;
extern int MouseY;
extern int MouseS;
extern int press;
extern union REGS regs;
#endif
