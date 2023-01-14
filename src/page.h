#ifndef _FRONTEND_H_
#define _FRONTEND_H_

#include <graphics.h>
#include<dos.h>
#include"log.h"
#include"mouse.h"
#include"keyboard.h"
#include"hz.h"
#include"core.h"


#ifndef NULL
#define NULL 0
#endif



int textButton(int x, int y, char* text = NULL, int sizex = 100, int sizey = 30);
void pageHome();
void pageLogin();

#endif