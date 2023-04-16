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


enum{
    AppRouterExpand = 1,
    AppExit
};

typedef struct
{
    char uid[10][20];
    char *currentUser;
}AppData;

AppData *appData();

void app();

#include <graphics.h>
#include "svga.h"
#include "keyboard.h"
#include "mouse.h"
#include "global.h"
#include "textbox.h"
#include "image.h"
#include "anim.h"
#include "meditor.h"
#include "router.h"
#endif