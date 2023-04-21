/**
 * @file router.h
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __ROUTER_H__
#define __ROUTER_H__

#include "memos.h"
#include "meditor.h"
#include "button.h"

typedef struct{
    Memo *topMemo;
    Button expandButton;
    Button newMemoButton;
    Button userButton;
    Button setButton;
    Button memoButton[10];
    char memoName[20];
}Router;

enum {
	RouterExpand = 1,
    RouterChangeMemo,
    RouterUserPage,
    RouterSettingsPage
};

Router router_new();
void router_draw(Router *r);
int router_expand(Router *r);
int router_event(Router *r);
void router_button_drawMemoList(Button *b);
void router_distrcut();
void router_refresh(Router *r);
void router_button_drawExpandButton(Button *b);
void router_button_drawNewMemoButton(Button *b);
void router_button_drawUserButton(Button *b);
void router_button_drawSetButton(Button *b);
#include <bios.h>
#include "keyboard.h"
#include "app.h"
#include "digclock.h"
#include "scroll.h"
#include "textipt.h"
#include "mshare.h"
#endif