#ifndef _LISTENER_H_
#define _LISTENER_H_

#include<bios.h>
#include<string.h>
#include"mouse.h"
#include"ime.h"
#include"log.h"
#include"keyboard.h"
#include"core.h"

int listenerHome(Mouse*);
int listenerLogin(struct Textbox *bu, struct Textbox *bp, Mouse*);
int listenerTextbox(Textbox *b);
int listenerKey();

#endif
