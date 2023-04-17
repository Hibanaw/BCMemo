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
    Button memoButton[10];
    char memoFilePath[20];
}Router;

enum {
	RouterExpand = 1,
    RouterChangeMemo
};

Router router_new();
void router_draw(Router *r);
int router_expand(Router *r);
int router_event(Router *r);
void router_button_drawMemoList(Button *b);
void router_distrcut();
void router_refresh(Router *r);

#include <bios.h>
#include "keyboard.h"
#include "app.h"
#include "digclock.h"
#include "scroll.h"
#endif