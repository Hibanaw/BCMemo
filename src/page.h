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
#include"module.h"


#ifndef NULL
#define NULL 0
#endif


void drawHome();
void drawLogin(Textbox tu, Textbox tp, Button b);

#endif