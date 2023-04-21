/**
 * @file share.h
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __MSHARE_H__
#define __MSHARE_H__

#include <time.h>
#include "button.h"
#include "textipt.h"

typedef char shareCode[10];

typedef struct
{
    shareCode code;
    char memoName[20];
    time_t expiryTime;
}Share;

typedef struct
{
    Button radioBox[5];
    TextInput textInput;
}ShareRadioBoxArea;

void share_page(char *memoName);
int share_add(char *memoName, char *shareCodeBuffer, time_t expireTime);
int share_determine(char *shareCode, char *uid);

share_newRadioBoxArea(ShareRadioBoxArea *ra, char *buffer);
void share_drawRadioBoxArea(ShareRadioBoxArea *sr);
int share_radioBoxAreaEvent(ShareRadioBoxArea *sr);

#include "svga.h"
#include "mouse.h"
#include "keyboard.h"
#include "digclock.h"
#include "auth.h"
#endif