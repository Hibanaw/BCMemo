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

MemoEditor memoEditor_new(Memo *m){
    MemoEditor me;
    memset(&me, 0, sizeof(me));
    memo() = m;
    me.beginMemoBlock = m->head;
    me.posX = 75;
    me.posY = 20;
    memoEditor_updateList(&me);
    return me;
}

void memoEditor_event(MemoEditor *me){
    MemoBlock *p = me.BeginMemoBlock;
    int k = bioskey(1);
    int i;
    if(me->status){
        for(i = 0; i < me->list.count; i++){
            switch (me->list.type[i]){
                case PARAGRAPH:
                    Textbox *tb = me->list.widget[i];
                    int ls = tb->status;
                    textbox_event(tb);
                    if(ls != TextboxFocused && tb->status == TextboxFocused){
                        tb->posY2 = 5*(tb->font.fontSize+tb->font.rowSpacing);
                    }
                    if(ls == TextboxFocused && tb->status != TextboxFocused){
                        memoEditor_updateList(me);
                    }
                    break;
                case IMAGE:
                    ImageBox *ib = me->list.widget[i];
                    imageBox_event(ib);
                    break;
            }
        }
    }
    
}

void memoEditor_updateList(MemoEditor *e){
    int y = 30;
    int i;
    MemoBlock *p = e->beginMemoBlock;
    for(i = 0; i < e->list.count && e->list.widget[i] != NULL; i++){
        free(e->list.widget[i]);
    }
    e->list.count = 0;
    i = 0;
    while(i < 10 && y < 700 && p != NULL){
        switch (p->type)
        {
        case PARAGRAPH:
            Textbox *t = e->list.widget[i];
            t = malloc(sizeof(Textbox));
            *t = textbox_newDefault("ÐÂµÄ¶ÎÂä", e->posX + 20, y, MAXWIDTH, y + 30);
            t->content = p->content;
            y+=text_getHeight(*t);

            break;
        case IMAGE:
            ImageBox *ib = e->list.widget[i];
            ib = malloc(sizeof(ImageBox));
            *ib = memoEditor_newImageBox(p->content, e->posX + 20, y);
            y+=ib->posY2 - ib->posY1;
            break;
        case CHECKBOX:
            
            break;
        }
        y+=20;
        p = p->next;
        i++;
    }
    e->list.count = i;
}
