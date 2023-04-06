/**
 * @file meditor.h
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __MEMOEDITOR_H__
#define __MEMOEDITOR_H__

#include "memo.h"
#include "image.h"
#include "button.h"
#include "textbox.h"
#include "imagebox.h"

#define EDITORHEIGHT 680
#define EDITORWIDTH 800

typedef struct{
    void *widget[20];
    enum Memotype type[20];
    int count;
} MemoEditorWidgetList;

typedef struct{
    MemoBlock *beginMemoBlock;
    int posX;
    int posY;
    MemoEditorWidgetList list;
} MemoEditor;


#endif