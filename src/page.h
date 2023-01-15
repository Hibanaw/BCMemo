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


void pageHome();
void pageLogin(struct Textbox tu, struct Textbox tp, struct Button b);

#endif