#ifndef _HZINPUT_H_
#define _HZINPUT_H_

//����ͷ�ļ�����ͷ�ļ����Ѱ������ã���input.c�а���ͷ�ļ�����
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <bios.h>
#include <conio.h>
#include <dos.h>
#include "hz.h"
#include "mouse.h"
#include "keyboard.h"

#define FAIL 0
#define SUCCESS 1


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
