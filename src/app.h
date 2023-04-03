/**
 * @file app.h
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-02-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __APP_H__
#define __APP_H__

#include <graphics.h>
#include "svga.h"
#include "keyboard.h"
#include "mouse.h"
#include "global.h"
#include "textbox.h"
#include "image.h"

typedef struct{
    char * uid;
    bool leftBar;
	//Memos *memoList;
}AppData;

AppData *app_data();
void app();

void _app_init();

#endif