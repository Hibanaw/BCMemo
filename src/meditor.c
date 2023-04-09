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

MemoEditor memoEditor_new(char *filePath, char *uid){
    MemoEditor me;
    Memo *m = memo();
    *m = memofile_read(filePath);
    memset(&me, 0, sizeof(me));
    if(m->head == NULL){
        MemoBlock *mb = memo_newBlock(PARAGRAPH, 0, "");
		strcpy(mb->lastEditUser, uid);
        memo_addBlock(mb);
    }
    me.filePath = filePath;
    me.beginMemoBlock = m->head;
    me.posX = 75;
    me.posY = 30;
    me.focusedBlock = memo_preBlock(m->head);
    me.paragraphButton  = button_new(me.posX + 10, me.posY+3, me.posX + 42, me.posY + 35, "", button_drawDefault);
    me.imageButton      = button_new(me.posX + 52, me.posY+3, me.posX + 84, me.posY + 35, "", button_drawDefault);
    me.checkboxButton   = button_new(me.posX + 94, me.posY+3, me.posX + 126, me.posY + 35, "", button_drawDefault);
    me.saveButton       = button_new(MAXWIDTH - 40, me.posY+3, MAXWIDTH - 8, me.posY + 35, "", button_drawDefault);
    me.uid = uid;
    mouse_hide();
    setfillstyle(1, hexfffbf0);
	bar(me.posX, me.posY, MAXWIDTH, me.posY+40);
	bar(me.posX, me.posY, me.posX+7, me.posY+7);
    setcolor(hexd4dfff);
    setfillstyle(1, _WHITE);
    arc(me.posX+6, me.posY+47, 90, 180, 7);
    setlinestyle(0, 1, hexd4dfff);
    line(me.posX+6, me.posY+40, MAXWIDTH, me.posY+40);
    button_draw(&me.paragraphButton);
    button_draw(&me.imageButton);
    button_draw(&me.checkboxButton);
    button_draw(&me.saveButton);
    mouse_show();
    memoEditor_updateList(&me);
    return me;
}

/**
 * @brief 
 * 
 * @param me 
 * @return int 1 for exit.
 */
int memoEditor_event(MemoEditor *me){
	MemoBlock *p = me->beginMemoBlock;
    int k = bioskey(1);
    int i;
    if(button_event(&me->saveButton)){
        memofile_write(me->filePath, memo());
    }
    if(me->focusedBlock == NULL){
        switch (k){
            case KEYUP:
                bioskey(0);
                me->beginMemoBlock = memo_preBlock(me->beginMemoBlock);
                memoEditor_updateList(me);
                break;
            case KEYDOWN:
                bioskey(0);
                if(me->beginMemoBlock->next)
                    me->beginMemoBlock = me->beginMemoBlock->next;
                else me->beginMemoBlock = memo()->head;
                memoEditor_updateList(me);
        }
        if(button_event(&me->paragraphButton)){
            MemoBlock *mb = memo_newBlock(PARAGRAPH, 0, "");
            strcpy(mb->lastEditUser, me->uid);
            memo_addBlock(mb);
            memoEditor_updateList(me);
            return 0;
        }
        if(button_event(&me->imageButton)){
            MemoBlock *mb = memo_newBlock(IMAGE, 0, "");
            strcpy(mb->lastEditUser, me->uid);
            memo_addBlock(mb);
            memoEditor_updateList(me);
            return 0;
        }
        if(button_event(&me->checkboxButton)){
            MemoBlock *mb = memo_newBlock(CHECKBOX, 0, "");
            strcpy(mb->lastEditUser, me->uid);
            memo_addBlock(mb);
            memoEditor_updateList(me);
            return 0;
        }
    }
    else{
        if(button_event(&me->paragraphButton)){
            me->focusedBlock->type = PARAGRAPH;
            strcpy(me->focusedBlock->lastEditUser, me->uid);
            memoEditor_updateList(me);
            return 0;
        }
        if(button_event(&me->imageButton)){
            me->focusedBlock->type = IMAGE;
            strcpy(me->focusedBlock->lastEditUser, me->uid);
            memoEditor_updateList(me);
            return 0;
        }
        if(button_event(&me->checkboxButton)){
            me->focusedBlock->type = CHECKBOX;
            strcpy(me->focusedBlock->lastEditUser, me->uid);
            memoEditor_updateList(me);
            return 0;
        }
    }
    for(i = 0; i < me->list.count; i++){
        Textbox *tb;
		int lh;
        int ls;
        ImageBox *ib;
        int trigger;
        switch (me->list.type[i]){
            case PARAGRAPH:
                tb = me->list.widget[i];
				lh = text_getHeight(textbox_convert2text(*tb));
                ls = tb->status;
                trigger = textbox_event(tb);
                if(ls == TextboxSelected && tb->status == TextboxDefault && mouse_isClickedInBox(me->posX, me->posY + 3, me->posX + 126, me->posY + 35) == 1){
                    tb->status = TextboxSelected;
                }
                if(tb->status == TextboxSelected){
                    me->focusedBlock = me->list.memoBlock[i];
                    me->list.focusedBlockCursorLocation = tb->cursorLocation;
                }
				if(tb->status == TextboxSelected && lh != text_getHeight(textbox_convert2text(*tb))){
                    memoEditor_updateList(me);
                    return 0;
                }
                if(trigger == 1){
                    MemoBlock *mb;
                    char sn[310];
                    strcpy(sn, text_getNthChar(tb->content, tb->cursorLocation));
                    mb = memo_newBlock(PARAGRAPH, 0, sn);
                    *text_getNthChar(tb->content, tb->cursorLocation) = 0;
                    me->list.focusedBlockCursorLocation = 0;
                    me->focusedBlock = memo_insertBlock(me->list.memoBlock[i], mb);
                    strcpy(me->focusedBlock->lastEditUser, me->uid);
                    memoEditor_updateList(me);
                    return 0;
                    break;
                }
                if(trigger == -1){
                    if(me->focusedBlock != memo()->head){
                        MemoBlock *mb = memo_preBlock(me->list.memoBlock[i]);
                        if(text_getLength(mb->content) + text_getLength(me->list.memoBlock[i]) <= 150){
                            me->list.focusedBlockCursorLocation = text_getLength(mb->content);
                            strcat(mb->content, tb->content);
                            me->focusedBlock = mb;
                            memo_deleteBlock(me->list.memoBlock[i]);
                            memoEditor_updateList(me);
                            return 0;
                        }
                    }
                    break;
                }
                if(me->list.memoBlock[i] == me->focusedBlock && tb->status != TextboxSelected){
                    me->focusedBlock = NULL;
                }
                break;
            case IMAGE:
                ib = me->list.widget[i];
                if(imageBox_event(ib)){
                    me->focusedBlock = me->list.memoBlock[i];
                    me->list.focusedBlockCursorLocation = 1;
                }
				if(me->focusedBlock == me->list.memoBlock[i] && mouse_isClickedInBox(ib->posX1, ib->posY1, ib->posX2, ib->posY2) == -1 && mouse_isClickedInBox(me->posX, me->posY + 3, me->posX + 126, me->posY + 35) != 1){
                    me->focusedBlock = NULL;
                }
                if(me->focusedBlock == me->list.memoBlock[i]){
                    MemoBlock *mb;
                    switch(bioskey(1)){
                        case KEYBACKSPACE:
                            bioskey(0);
                            me->focusedBlock->type = PARAGRAPH;
                            me->list.focusedBlockCursorLocation = text_getLength(me->focusedBlock->content);
                            strcpy(me->focusedBlock->lastEditUser, me->uid);
                            memoEditor_updateList(me);
                            return 0;
                            break;
                        case KEYENTER:
                            bioskey(0);
                            mb = memo_newBlock(PARAGRAPH, 0, "");
                            me->list.focusedBlockCursorLocation = 0;
                            me->focusedBlock = memo_insertBlock(me->list.memoBlock[i], mb);
                            strcpy(me->focusedBlock->lastEditUser, me->uid);
                            memoEditor_updateList(me);
                            return 0;
                            break;
                    }
                }
                break;
        }
    }
    
}

void memoEditor_updateList(MemoEditor *e){
    int x = e->posX;
    int y = e->posY + 60;
    int i;
    int dy;
    int sum = memo_getBlockSum();
    int no = memo_getBlockNum(e->beginMemoBlock);
    MemoBlock *p = e->beginMemoBlock;
    if(p == NULL){
        p = e->beginMemoBlock = memo()->head;
    }
    for(i = 0; i < e->list.count && e->list.widget[i] != NULL; i++){
        free(e->list.widget[i]);
    }
    mouse_hide();
    setfillstyle(1, _WHITE);
    bar(x+5, y, MAXWIDTH, MAXHEIGHT);
    e->list.count = 0;
    i = 0;
    while(i < 25 && y < 700 && p != NULL){
        Textbox *tb;
        ImageBox *ib;
        e->list.type[i] = p->type;
        e->list.memoBlock[i] = p;
        switch (p->type){
        case PARAGRAPH:
            tb = malloc(sizeof(Textbox));
            e->list.widget[i] = tb;
            *tb = textbox_newDefault("ÐÂµÄ¶ÎÂä", x + 20, y, MAXWIDTH - 20, y, p->content);
			dy = text_getHeight(textbox_convert2text(*tb));
            tb->posY2 = y + dy;
            if(p == e->focusedBlock){
                if(e->list.focusedBlockCursorLocation == -1){
                    e->list.focusedBlockCursorLocation = text_getLength(tb->content);
                }
                tb->status = TextboxSelected;
                tb->cursorLocation = e->list.focusedBlockCursorLocation;
            }
            textbox_draw(tb);
            y += dy;
            break;
		case IMAGE:
            if(image_illegal(p->content)){
                p->type = PARAGRAPH;
                continue;
            }
            y+=10;
            ib = malloc(sizeof(ImageBox));
			e->list.widget[i] = ib;
            *ib = imageBox_new(p->content, x + 20, y);
            ib->status = -1;
            y+=ib->posY2 - ib->posY1;
            y+=10;
            imageBox_draw(ib);
            break;
        case CHECKBOX:
            
            break;
        }
        p = p->next;
        i++;
        y+= 15;
    }
    e->list.count = i;
    if(i < sum){
        int y1, y2, l;
        l = (MAXHEIGHT - e->posY - 80) * i / sum;
        y1 = (MAXHEIGHT - e->posY - 80) * no / sum + e->posY + 60;
        y2 = y1+l;
        setfillstyle(1, hex555f55);
        bar(MAXWIDTH - 10, y1, MAXWIDTH - 5, y2);
    }
    mouse_show();
}
