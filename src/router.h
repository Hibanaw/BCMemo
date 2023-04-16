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

#include <bios.h>
#include "memos.h"
#include "meditor.h"
#include "keyboard.h"
#include "button.h"
#include "app.h"
#include "digclock.h"

typedef struct{
    Memos list;
    Button expandButton;
    Button newMemoButton;
    char memoFilePath[50];
    MemoEditor memoEditor;
}Router;

enum {
	RouterExpand = 1
};

Router router_new();
void router_draw(Router *r);
int router_expand(Router *r);
int router_event(Router *r);

#endif