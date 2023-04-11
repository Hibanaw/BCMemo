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
#include "file.h"

#define EDITORHEIGHT 680
#define EDITORWIDTH 800

typedef struct{
    void *widget[25];
    enum Memotype type[25];
    MemoBlock *memoBlock[25];
    int count;
} MemoEditorWidgetList;

typedef struct{
    char *uid;
    char *filePath;
    MemoBlock *beginMemoBlock;
    MemoBlock *focusedBlock;
    int focusedBlockCursorLocation;
    int posX;
    int posY;
    MemoEditorWidgetList list;
    Button paragraphButton;
    Button imageButton;
    Button checkboxButton;
    Button saveButton;
} MemoEditor;

typedef struct{
    Button checkbox;
    Textbox textbox;
} MemoEditor_Checkbox;

MemoEditor memoEditor_new(char *filePath, char *uid);
int memoEditor_event(MemoEditor *me);
void memoEditor_updateList(MemoEditor *e);
#endif