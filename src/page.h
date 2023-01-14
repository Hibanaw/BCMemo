#ifndef _FRONTEND_H_
#define _FRONTEND_H_

#include <graphics.h>
#include<dos.h>
#include"log.h"
#include"mouse.h"
#include"keyboard.h"
#include"hz.h"
#include"core.h"
#include"image.h"


#ifndef NULL
#define NULL 0
#endif


int pageButton(int x, int y, char* text, int width, int height);
void pageTextBox();
void pageHome();
void pageLogin();

#endif