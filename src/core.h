#ifndef _CORE_H_
#define _CORE_H_

#include<stdio.h>
#include<string.h>
#include"mouse.h"
#include"memo.h"
#include"memos.h"
#include"page.h"
#include"event.h"
#include"log.h"
#include"svga.h"
#include"module.h"



int init();//初始化
int login();//登陆功能，登成果返回1，失败返回0，退出返回-1
void mainLoop();//主循环
void leftColumn();
void rightColumn();
int home();

void close();

#endif