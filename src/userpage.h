/**
 * @file userpage.h
 * @author wywgwt (2504133124@qq.com)
 * @brief 
 * @date 2023-04-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __USERPAGE_H__
#define __USERPAGE_H__

#include <graphics.h>
#include "svga.h"
#include "keyboard.h"
#include "mouse.h"
#include "global.h"
#include "textbox.h"
#include "image.h"
#include "anim.h" 
#include "meditor.h"
#include"text.h"
#include"textipt.h"
#include"textbox.h"
#include"app.h"
#include"malloc.h"
#include"button.h"
#include<string.h>
#include"user.h"
#include"button.h"
int userpage();

int userpage_login(int j);

int userpage_deleteuser(int j,int k);
void userpage_button_draw1(Button *b);
void userpage_button_draw2(Button *b);
void userpage_button_draw3(Button *b);
void userpage_button_draw4(Button *b);
void userpage_button_draw5(Button *b);

//userpage_addUser()

//userpage_deleteUser()
#endif