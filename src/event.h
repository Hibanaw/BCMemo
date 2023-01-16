#ifndef _LISTENER_H_
#define _LISTENER_H_

#include<bios.h>
#include<string.h>
#include<string.h>
#include"mouse.h"
#include"ime.h"
#include"log.h"
#include"keyboard.h"
#include"core.h"
#include"module.h"


int homeEvent(Mouse*);
int loginEvent(Textbox *bu, Textbox *bp, Button *b, Mouse *m);
int buttonEvent( Button *b, Mouse *m);
int textboxEvent(Textbox *b, Mouse *m);
int keyEvent();

#endif
