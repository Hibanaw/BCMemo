/**
 * @file app.h
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-02-27
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
void userpage();

int userpage_login(int j);

int userpage_deleteuser(int j,int k);
void memoeditor_button_draw1(Button *b);
void memoeditor_button_draw2(Button *b);
void memoeditor_button_draw3(Button *b);
//userpage_addUser()

//userpage_deleteUser()
#endif