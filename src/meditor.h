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
#include "button.h"
#include "scroll.h"
#include "textipt.h"
#include "auth.h"

#define EDITORHEIGHT 680
#define EDITORWIDTH 800

#define BLOCKMAX 30

typedef struct{
    void *widget[30];
    enum Memotype type[30];
    MemoBlock *memoBlock[30];
    int count;
} MemoEditorWidgetList;

typedef struct{
    char *uid;
    char *fileName;
    MemoBlock *beginMemoBlock;
    MemoBlock *focusedBlock;
    int focusedBlockCursorLocation;
    int posX;
    int posY;
    MemoEditorWidgetList list;
    Button drawButton;
    Button imageButton;
    Button checkboxButton;
    Button shareButton;
    Button settingsButton;
    Button saveButton;
    TextInput titleBar;
    ScrollBar scrollBar;
    int unSaved;
    enum AuthType authType;
} MemoEditor;

typedef struct{
    Button checkbox;
    Textbox textbox;
} MemoEditor_Checkbox;

MemoEditor memoEditor_new(char *fileName, char *uid);
void memoEditor_draw(MemoEditor *e);
int memoEditor_event(MemoEditor *me);
void memoEditor_updateList(MemoEditor *e);
void memoEditor_distruct(MemoEditor *me);
void memoEditor_save(MemoEditor *me);

void memoEditor_button_drawAddPicture(Button *b);
void memoEditor_button_drawAddCheckbox(Button *b);
void memoEditor_button_drawDrawpad(Button *b);

#include "textbox.h"
#include "imagebox.h"
#include "mfile.h"
#include "app.h"
#include "drawpad.h"
#include "addimage.h"
#endif