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



int init();//��ʼ��
int login();//��½���ܣ��ǳɹ�����1��ʧ�ܷ���0���˳�����-1
void mainLoop();//��ѭ��
void leftColumn();
void rightColumn();
int home();

void close();

#endif