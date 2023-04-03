/**
 * @file memoeditor.h
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

#define EDITORHEIGHT 680
#define EDITORWIDTH 800

enum MemoEditorStatus{
    MemoEditorFocused,
    MemoEditorDefault
};

typedef struct{
    MemoBlock *BeginMemoBlock;
    int posX;
    int posY;
    enum MemoEditorStatus status;
} MemoEditor;

typedef Button MemoEditorImageBox;

#endif