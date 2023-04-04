/**
 * @file meditor.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "meditor.h"

void memoEditor_init(MemoEditor *me){
    
}

void memoEditor_event(MemoEditor *me){
    MemoBlock *p = me.BeginMemoBlock;
    int k = bioskey(1);
    if(me->status){
        switch(k){
            case KEYUP:
                me->BeginMemoBlock = 0;
                memoEditor_draw(me);
                break;
        }
    }
    while(p){
        int h;
        switch(p->type){
            case IMAGE:
                MemoEditorImageBox ib = memoEditor_newImageBox(p->content);
                
                break;
            case PARAGRAPH:
                
            case CHECKBOX:
                
        }
        py += h;
        if(py >= m->posY + EDITORHEIGHT){
            break;
        }
        p = p->next;
    }
}

void memoEditor_drawImageBox(MemoEditorImageBox *ib){
    
}

void memoEditor_eventImageBox(MemoEditorImageBox *ib){
    button_event(ib);
}

void memoEditor_newImageBox(char *filePath, int x, int y){
    MemoEditorImageBox ib;
    int w, h;
    image_getSize(filePath, w, h);
    ib = button_newButton(x, y, x + w, y + h, filePath, memoEditor_drawImageBox);
    return ib;
}