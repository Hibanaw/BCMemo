/**
 * @file mset.h
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __MSET_H__
#define __MSET_H__

#include "button.h"
#include "meditor.h"

typedef struct{
    Button radioBox[4];
}MsetRadioBoxArea;
int mset_page(MemoEditor *me);
int mset_newRadioBoxArea(MsetRadioBoxArea *ra, int y, int defualt);
void mset_drawRadioBoxArea(MsetRadioBoxArea *sr);
int mset_radioBoxAreaEvent(MsetRadioBoxArea *sr);

#include <graphics.h>
#include "svga.h"
#include "mouse.h"
#include "keyboard.h"
#include "textipt.h"
#include "memo.h"
#include "meditor.h"
#endif