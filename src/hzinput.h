#ifndef _HZINPUT_H_
#define _HZINPUT_H_

//以下头文件如总头文件中已包含则不用，在input.c中包括头文件即可
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
//汉字输入法

int input_method(int x,int y,char *str,int value,char *py) ;
//汉字输入法调入

char *itostr(int a,char *s);
//数字标号

void pyFrm(int x1,int y1,int x2,int y2);
//输入法小框

int xouttextxy(int x,int y,char *s,int color);
//字符输入法

#endif
