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


int listenerHome(Mouse*);
int listenerLogin(struct Textbox *bu, struct Textbox *bp,  Button *b, Mouse *m);
int listenerButton( Button *b, Mouse m);
int listenerTextbox(struct Textbox *b);
int listenerKey();

#endif
