#ifndef _INPUT_H_
#define _INPUT_H_

//����ͷ�ļ�����ͷ�ļ����Ѱ������ã���input.c�а���ͷ�ļ�����
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <math.h>
#include <bios.h>
#include <conio.h>
#include <dos.h>
#include "hz.h"
#include "mouse.h"

enum imekeyvalue{
    BACK = 0xe08,
    ENTER = 0x1c0d,
    SPACE = 0x3920,
    LASTLINE = 0x4800,
    NEXTLINE = 0x5000,
    LEFT = 0x4b00,
    RIGHT = 0x4d00,
    FIRST = 0x231,
    SECOND = 0x332,
    THIRD = 0x433,
    FOURTH = 0x534
    
};

enum imestatus{
    SUCCESS = 1,
    FAIL = -1
};

enum imevarable{MAXPY = 5};

int hz_input(int x1,int y1,int x2,int y2,char *s,int len,int color,int color2, int size);
//�������뷨

int input_method(int x,int y,char *str,int value,char *py) ;
//�������뷨����

char *itostr(int a,char *s);
//���ֱ��

void pyFrm(int x1,int y1,int x2,int y2);
//���뷨С��

int xouttextxy(int x,int y,char *s,int color);
//�ַ����뷨

#endif