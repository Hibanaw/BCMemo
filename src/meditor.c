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

void memoEditor_draw(MemoEditor *e){
    MemoEditor me = *e;
    setfillstyle(1, hexfffbf0);
    bar(me.posX, me.posY, MAXWIDTH, me.posY+40);
    bar(me.posX, me.posY, me.posX+7, me.posY+7);
    setcolor(hexd4dfff);
    setfillstyle(1, _WHITE);
    arc(me.posX+6, me.posY+47, 90, 180, 7);
    setlinestyle(0, 1, 2);
    line(me.posX+6, me.posY+40, MAXWIDTH, me.posY+40);
    button_draw(&me.drawButton);
    button_draw(&me.imageButton);
    button_draw(&me.checkboxButton);
    button_draw(&me.saveButton);
    button_draw(&me.shareButton);
    button_draw(&me.settingsButton);
    mouse_show();
    memoEditor_updateList(e);
    mouse_hide();
    me.titleBar.draw(&me.titleBar);
}

MemoEditor memoEditor_new(char *fileName, char *uid){
    MemoEditor me;
    Memo *m = memo();
    char filePath[20];
    memset(m, 0, sizeof(m));
	sprintf(filePath, "data\\%s.MEM", fileName);
    *m = memofile_read(filePath);
    memset(&me, 0, sizeof(me));
    me.fileName         = fileName;
    me.beginMemoBlock   = m->head;
    me.posX             = 75;
    me.posY             = 30;
    me.focusedBlock     = NULL;
    me.drawButton       = button_new(me.posX + 10, me.posY+3, me.posX + 42, me.posY + 35, "", memoEditor_button_drawDrawpad);
    me.imageButton      = button_new(me.posX + 52, me.posY+3, me.posX + 84, me.posY + 35, "", memoEditor_button_drawAddPicture);
    me.checkboxButton   = button_new(me.posX + 94, me.posY+3, me.posX + 126, me.posY + 35, "", memoEditor_button_drawAddCheckbox);
    me.shareButton      = button_new(MAXWIDTH - 126, me.posY+3, MAXWIDTH - 94, me.posY + 35, "", memoEditor_button_drawSharebutton);
    me.settingsButton   = button_new(MAXWIDTH - 84, me.posY+3, MAXWIDTH - 52, me.posY + 35, "", memoEditor_button_drawEditbutton);
    me.saveButton       = button_new(MAXWIDTH - 42, me.posY+3, MAXWIDTH - 10, me.posY + 35, "", memoEditor_button_drawSavebutton);
    me.uid              = uid;
    me.scrollBar        = scrollBar_new(MAXWIDTH - 15, me.posY + 50, MAXHEIGHT - (me.posY + 60));
    me.titleBar         = textinput_newTitle("无标题", 300, 35, 794, 65, memo()->title);
    me.unSaved          = 1;
    me.titleBar.textbox.bgColor = hexfffbf0;
    me.authType = auth_get(fileName).type;
    strcpy(memo()->fileName, me.fileName);
    return me;
}

/**
 * @brief 
 * 
 * @param me 
 * @return 
 */
int memoEditor_event(MemoEditor *me){
	MemoBlock *p = me->beginMemoBlock;
    int k = bioskey(1);
    int i;
    int ss;
    int sum = memo_getBlockSum();
    MemoBlock *mb;
    if(button_event(&me->shareButton)){
        share_page(me->fileName);
        memoEditor_updateList(me);
        return 0;
    }
    if(button_event(&me->settingsButton)){
        mset_page(me);
        memoEditor_updateList(me);
        return 0;
    }
    if(button_event(&me->saveButton)){
        memoEditor_save(me);
    }
    ss = scrollBar_event(&me->scrollBar);
    textinput_event(&me->titleBar);
    switch (ss)
    {
        case -1:
            if(me->beginMemoBlock != memo()->head){
                me->beginMemoBlock = memo_preBlock(me->beginMemoBlock);
                memoEditor_updateList(me);
            }
            break;
        case 1:
			if(me->list.memoBlock[me->list.count-1]->next){
                me->beginMemoBlock = me->beginMemoBlock->next;
                memoEditor_updateList(me);
            }
            break;
    }
    // button
    if(button_event(&me->drawButton)){
        int tg;
        char path[100];
        if(sum >= BLOCKMAX)
            return 0;
        sprintf(path, "data/%s", memo()->fileName);
        tg = drawPad(path);
        if(tg == 0){
            if(me->focusedBlock == NULL){
                mb = memo_newBlock(IMAGE, 0, path);
                strcpy(mb->lastEditUser, me->uid);
                me->unSaved = 1;
                memo_addBlock(mb);
            }
            else{
                if(*(me->focusedBlock->content) == 0){
                    strcpy(me->focusedBlock->content, path);
                    me->focusedBlock->type = IMAGE;
                    strcpy(me->focusedBlock->lastEditUser, me->uid);
                    me->unSaved = 1;
                }
                else{
                    mb = memo_newBlock(IMAGE, 0, path);
                    strcpy(mb->lastEditUser, me->uid);
                    me->unSaved = 1;
                    memo_insertBlock(me->focusedBlock, mb);
                    me->focusedBlock = mb;
                }
            }
        }
        memoEditor_updateList(me);
        return 0;
    }
    if(button_event(&me->imageButton)){
        char path[50];
        int tg;
        memset(path, 0, sizeof(path));
        if(sum >= BLOCKMAX)
                return 0;
        tg = addImage(path);
        if(tg == 0){
            if(me->focusedBlock == NULL){
                mb = memo_newBlock(IMAGE, 0, path);
                strcpy(mb->lastEditUser, me->uid);
                me->unSaved = 1;
                memo_addBlock(mb);
            }
            else{
                if(*(me->focusedBlock->content) == 0){
                    strcpy(me->focusedBlock->content, path);
                    me->focusedBlock->type = IMAGE;
                    strcpy(me->focusedBlock->lastEditUser, me->uid);
                    me->unSaved = 1;
                }
                else{
                    mb = memo_newBlock(IMAGE, 0, path);
                    strcpy(mb->lastEditUser, me->uid);
                    memo_insertBlock(me->focusedBlock, mb);
                    me->unSaved = 1;
                    me->focusedBlock = mb;
                }
            }
        }
        memoEditor_updateList(me);
        return 0;
    }
    if(button_event(&me->checkboxButton)){
        if(me->focusedBlock == NULL){
            if(sum >= BLOCKMAX)
                return 0;
            mb = memo_newBlock(CHECKBOX, 0, "");
            strcpy(mb->lastEditUser, me->uid);
            me->unSaved = 1;
            memo_addBlock(mb);
            memoEditor_updateList(me);
            return 0;
        }
        else{
            if(me->focusedBlock->type == CHECKBOX){
                me->focusedBlock->type = PARAGRAPH;
            }
            else{
                me->focusedBlock->type = CHECKBOX;
            }
            strcpy(me->focusedBlock->lastEditUser, me->uid);
            me->unSaved = 1;
            memoEditor_updateList(me);
            return 0;
        }
    }
    //page move
    if(me->focusedBlock == NULL){
        MemoBlock *mb;
        switch (k){
            case KEYUP:
                bioskey(0);
                
                if(me->beginMemoBlock != memo()->head){
                    me->beginMemoBlock = memo_preBlock(me->beginMemoBlock);
                    memoEditor_updateList(me);
                }
                break;
            case KEYDOWN:
                bioskey(0);
                if(me->beginMemoBlock->next){
                    me->beginMemoBlock = me->beginMemoBlock->next;
                    memoEditor_updateList(me);
                }
        }
        
    }
    else{
        switch (k){
            case KEYUP:
                bioskey(0);
                if(me->focusedBlock != me->beginMemoBlock){
                    me->focusedBlock = memo_preBlock(me->focusedBlock);
                    me->focusedBlockCursorLocation = MIN(me->focusedBlockCursorLocation, text_getLength(me->focusedBlock->content));
                    memoEditor_updateList(me);
                }
                else{
                    if(me->beginMemoBlock != memo()->head){
                        me->beginMemoBlock = memo_preBlock(me->beginMemoBlock);
                        me->focusedBlock = memo_preBlock(me->focusedBlock);
                        me->focusedBlockCursorLocation = MIN(me->focusedBlockCursorLocation, text_getLength(me->focusedBlock->content));
                        memoEditor_updateList(me);
                    }
                }
                break;
            case KEYDOWN:
                bioskey(0);
                if(me->focusedBlock != me->list.memoBlock[me->list.count-1]){
                    me->focusedBlock = me->focusedBlock->next;
                    me->focusedBlockCursorLocation = MIN(me->focusedBlockCursorLocation, text_getLength(me->focusedBlock->content));
                    memoEditor_updateList(me);
                }
                else{
                    if(me->beginMemoBlock != memo_preBlock(memo()->head)){
                        me->beginMemoBlock = me->beginMemoBlock->next;
                        me->focusedBlock = (me->focusedBlock->next != NULL ? me->focusedBlock->next : me->focusedBlock);
                        me->focusedBlockCursorLocation = MIN(me->focusedBlockCursorLocation, text_getLength(me->focusedBlock->content));
                        memoEditor_updateList(me);
                    }
                }
        }
    }
    for(i = 0; i < me->list.count; i++){
        Textbox *tb;
		int lh;
        int ls;
        ImageBox *ib;
        MemoEditor_Checkbox *cb;
        int trigger;
        int trigger2;
        char lc[160];
        strcpy(lc, me->list.memoBlock[i]->content);
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
                    me->focusedBlockCursorLocation = tb->cursorLocation;
                }
				if(tb->status == TextboxSelected && lh != text_getHeight(textbox_convert2text(*tb))){
                    memoEditor_updateList(me);
                    return 0;
                }
                if(trigger == 1){
                    MemoBlock *mb;
                    char sn[160];
                    if(sum >= BLOCKMAX)
                        return 0;
                    strcpy(sn, text_getNthChar(tb->content, tb->cursorLocation));
                    mb = memo_newBlock(PARAGRAPH, 0, sn);
                    *text_getNthChar(tb->content, tb->cursorLocation) = 0;
                    me->focusedBlockCursorLocation = 0;
                    me->focusedBlock = memo_insertBlock(me->list.memoBlock[i], mb);
                    strcpy(me->focusedBlock->lastEditUser, me->uid);
                    me->unSaved = 1;
                    if(tb->posY2 > MAXHEIGHT - 100){
                        me->beginMemoBlock = me->beginMemoBlock->next;
                    }
                    memoEditor_updateList(me);
                    return 0;
                }
                if(trigger == -1){
                    if(me->focusedBlock != memo()->head){
                        MemoBlock *mb = memo_preBlock(me->list.memoBlock[i]);
                        if(text_getLength(mb->content) + text_getLength(me->list.memoBlock[i]->content) <= 75){
                            me->focusedBlockCursorLocation = text_getLength(mb->content);
                            strcat(mb->content, tb->content);
                            me->focusedBlock = mb;
                            if(me->list.memoBlock[i] == me->beginMemoBlock){
                                me->beginMemoBlock = memo_preBlock(me->list.memoBlock[i]);
                            }
                            memo_deleteBlock(me->list.memoBlock[i]);
                            memoEditor_updateList(me);
                            return 0;
                        }
                    }
                }
                if(me->list.memoBlock[i] == me->focusedBlock && tb->status != TextboxSelected){
                    me->focusedBlock = NULL;
                }
                break;
            case IMAGE:
                ib = me->list.widget[i];
                trigger = imageBox_event(ib);
                if(trigger == 1){
                    me->focusedBlock = me->list.memoBlock[i];
                    me->focusedBlockCursorLocation = 1;
                }
                if(trigger == 2){
                    return 1;
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
                            me->focusedBlockCursorLocation = text_getLength(me->focusedBlock->content);
                            strcpy(me->focusedBlock->lastEditUser, me->uid);
                            me->unSaved = 1;
                            memoEditor_updateList(me);
                            return 0;
                            break;
                        case KEYENTER:
                            bioskey(0);
                            mb = memo_newBlock(PARAGRAPH, 0, "");
                            me->focusedBlockCursorLocation = 0;
                            me->focusedBlock = memo_insertBlock(me->list.memoBlock[i], mb);
                            strcpy(me->focusedBlock->lastEditUser, me->uid);
                            me->unSaved = 1;
                            memoEditor_updateList(me);
                            return 0;
                            break;
                    }
                }
                break;
            case CHECKBOX:
                cb = me->list.widget[i];
                ls = cb->textbox.status;
                tb = &cb->textbox;
                lh = text_getHeight(textbox_convert2text(*tb));
                trigger = button_checkboxEvent(&cb->checkbox);
                trigger2 = textbox_event(&cb->textbox);
                if(ls == TextboxSelected && tb->status == TextboxDefault && mouse_isClickedInBox(me->posX, me->posY + 3, me->posX + 126, me->posY + 35) == 1){
                    tb->status = TextboxSelected;
                }
                if(tb->status == TextboxSelected){
                    me->focusedBlock = me->list.memoBlock[i];
                    me->focusedBlockCursorLocation = tb->cursorLocation;
                }
				if(tb->status == TextboxSelected && lh != text_getHeight(textbox_convert2text(*tb))){
                    memoEditor_updateList(me);
                    return 0;
                }
                if(trigger){
                    me->list.memoBlock[i]->checkBoxisChecked = (int)cb->checkbox.content;
                }
                if (trigger2 == 1){
                        MemoBlock *mb;
                        char sn[310];
                        strcpy(sn, text_getNthChar(tb->content, tb->cursorLocation));
                        mb = memo_newBlock(CHECKBOX, 0, sn);
                        *text_getNthChar(tb->content, tb->cursorLocation) = 0;
                        me->focusedBlockCursorLocation = 0;
                        me->focusedBlock = memo_insertBlock(me->list.memoBlock[i], mb);
                        strcpy(me->focusedBlock->lastEditUser, me->uid);
                        me->unSaved = 1;
                        memoEditor_updateList(me);
                        return 0;
                }
                if(trigger2 == -1){
                    me->focusedBlock->type = PARAGRAPH;
                    strcpy(me->focusedBlock->lastEditUser, me->uid);
                    me->unSaved = 1;
                    memoEditor_updateList(me);
                    return 0;
                }
                break;
        }
        if(strcmp(lc, me->list.memoBlock[i]->content)){
            strcpy(me->list.memoBlock[i]->lastEditUser, me->uid);
            me->unSaved = 1;
        }
    }
    return 0;
}

void memoEditor_updateList(MemoEditor *e){
    int x;
    int y = e->posY + 60;
    int i;
    int dy;
    int sum = memo_getBlockSum();
    int no = memo_getBlockNum(e->beginMemoBlock);
    MemoBlock *p = e->beginMemoBlock;
    x = e->posX + ((appData()->displayLastEditUser)? 150 : 0);
	if(memo()->head == NULL){
		MemoBlock *mb = memo_newBlock(PARAGRAPH, 0, "");
        strcpy(mb->lastEditUser, e->uid);
		e->unSaved = 1;
		memo_addBlock(mb);
    }
    if(p == NULL){
        p = e->beginMemoBlock = memo()->head;
    }
    for(i = 0; i < e->list.count; i++){
        if(e->list.widget[i] != NULL){
            free(e->list.widget[i]);
            e->list.widget[i] = NULL;
        }
    }
    mouse_hide();
    setfillstyle(1, _WHITE);
    bar(e->posX+5, y-18, MAXWIDTH-20, MAXHEIGHT);
    e->list.count = 0;
    i = 0;
    while(i < 25 && y < MAXHEIGHT && p != NULL){
        Textbox *tb;
        ImageBox *ib;
        MemoEditor_Checkbox *cb;
        
        if(appData()->displayLastEditUser){
            Text ut;
            char buf[30];
            memset(buf, 0, sizeof(buf));
            strcat(buf, "<");
            strcat(buf, p->lastEditUser);
            strcat(buf, ">");
            ut = text_newSmall(buf, x-text_getLength(buf)*16+10, y+5);
            text_display(ut);
        }
        e->list.type[i] = p->type;
        e->list.memoBlock[i] = p;
        switch (p->type){
        case PARAGRAPH:
            tb = malloc(sizeof(Textbox));
            e->list.widget[i] = tb;
            *tb = textbox_newDefault("新的段落", x + 20, y, MAXWIDTH - 30, y, p->content);
			dy = text_getHeight(textbox_convert2text(*tb));
            tb->posY2 = y + dy;
            if(p == e->focusedBlock){
                tb->status = TextboxSelected;
                tb->cursorLocation = e->focusedBlockCursorLocation;
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
            cb = malloc(sizeof(MemoEditor_Checkbox));
			e->list.widget[i] = cb;
            cb->checkbox = button_new(x+20, y, x+44, y+24, 0, button_checkboxDraw);
            switch (p->checkBoxisChecked)
            {
                case 0:
                    cb->checkbox.content = 0;
                break;
                case 1:
                    cb->checkbox.content = 1;
                break;
            }
            cb->textbox = textbox_newDefault("新的任务", x + 50, y, MAXWIDTH - 30, y, p->content);
			dy = text_getHeight(textbox_convert2text(cb->textbox));
            cb->textbox.posY2 = y + dy;
            if(p == e->focusedBlock){
                cb->textbox.status = TextboxSelected;
                cb->textbox.cursorLocation = e->focusedBlockCursorLocation;
            }
            textbox_draw(&cb->textbox);
            button_draw(&cb->checkbox);
            y += dy;
            break;
        }
        p = p->next;
        i++;
        y+= 10;
    }
    e->list.count = i;
    e->scrollBar.ithItem = no;
    e->scrollBar.sumItem = sum;
    e->scrollBar.inScreenItem = i;
    scrollBar_event(&e->scrollBar);
	scrollBar_draw(&e->scrollBar);
    mouse_show();
}

void memoEditor_distruct(MemoEditor *me){
    int i = 0;
    for(i = 0; i < 25; i++){
        if(me->list.widget[i] != NULL){
            free(me->list.widget[i]);
            me->list.widget[i] = NULL;
        }
    }
    while(memo()->head != NULL){
        memo_deleteBlock(memo()->head);
    }
    memset(memo(), 0, sizeof(Memo));
}

void memoEditor_save(MemoEditor *me){
    char filePath[20];
    sprintf(filePath, "data//%s.MEM", me->fileName);
    memofile_write(filePath, memo());
    auth_set(me->fileName, memo()->owner, me->authType);
    me->unSaved = 0;
}


void memoEditor_button_drawAddPicture(Button *b)
{
    int x1 = b->posX1 + 5, y1 = b->posY1 + 5,
        x2 = b->posX2 - 5, y2 = b->posY2 - 5;
    float k = 0.8;
    int x3, x4, y3, y4, m;
    button_drawWINUI(b);
    if (b->status != ButtonSelected)
    {
        setcolor(_BLACK);
        setlinestyle(0, 1, 2);
        // setfillstyle(1,_WHITE);
        // bar(x1,y1,x2,y2);
        line(x1,y1,x2,y1);
        line(x2,y1,x2,y2);
        line(x2,y2,x1,y2);
        line(x1,y2,x1,y1);
        arc(x1, y2, 0, 90, (x2 - x1) / 2);
        arc(x2, y2 + (y2 - y1) / 4, 90, 135, 3 * (y2 - y1) / 4);
        circle((x2 + 3 * x1) / 4, (3 * y1 + y2) / 4, 2);
    }
    else
    {
        x3 = (x1 + x2) / 2 - (x2 - x1) * k / 2;
        x4 = (x1 + x2) / 2 + (x2 - x1) * k / 2;
        y3 = (y1 + y2) / 2 - (y2 - y1) * k / 2;
        y4 = (y1 + y2) / 2 + (y2 - y1) * k / 2;
        setcolor(_BLACK);
		setlinestyle(0,1,2);
        // setfillstyle(1,_WHITE);
        // bar(x3,y3,x4,y4);
        line(x3,y3,x4,y3);
        line(x4,y3,x4,y4);
        line(x4,y4,x3,y4);
        line(x3,y4,x3,y3);
        arc(x3, y4, 0, 90, (x4 - x3) / 2);
        arc(x4, y4 + (y4 - y3) / 4, 90, 135, 3 * (y4 - y3) / 4);
        circle((x4 + 3 * x3) / 4, (3 * y3 + y4) / 4, 2 * k);
    }
}
void memoEditor_button_drawAddCheckbox(Button *b)
{
    int x1 = b->posX1 + 5, y1 = b->posY1 + 5,
        x2 = b->posX2 - 5, y2 = b->posY2 - 5;
    int x3, x4, y3, y4, m;
    float k;
    button_drawWINUI(b);
    if (b->status != ButtonSelected)
    {
        k = 1;
    }
    else
    {
        k = 0.8;
    }
    x3 = (x1 + x2) / 2 - (x2 - x1) * k / 2;
    x4 = (x1 + x2) / 2 + (x2 - x1) * k / 2;
    y3 = (y1 + y2) / 2 - (y2 - y1) * k / 2;
    y4 = (y1 + y2) / 2 + (y2 - y1) * k / 2;
    setcolor(_BLACK);
    setlinestyle(0,1, 2);
      line(x3,y3,x4,y3);
        line(x4,y3,x4,y4);
        line(x4,y4,x3,y4);
        line(x3,y4,x3,y3);
    line((3 * x3 + x4) / 4, (y3 + y4) / 2, (x3 + x4) / 2, (3 * y4 + y3) / 4);
    line((x3 + x4) / 2, (3 * y4 + y3) / 4, (3 * x4 + x3) / 4, (3 * y3 + y4) / 4);
}
void memoEditor_button_drawDrawpad(Button *b)
{
    int x1 = b->posX1+3, y1 = b->posY1+3,
        x2 = b->posX2-3, y2 = b->posY2-3;
    float k=0.8;
    int x3, x4, y3, y4, m;
    button_drawWINUI(b);
     if (b->status != ButtonSelected)
    {
        k = 1;
    }
    else
    {
        k = 0.8;
    }
    x3 = (x1 + x2) / 2 - (x2 - x1) * k / 2;
    x4 = (x1 + x2) / 2 + (x2 - x1) * k / 2;
    y3 = (y1 + y2) / 2 - (y2 - y1) * k / 2;
    y4 = (y1 + y2) / 2 + (y2 - y1) * k / 2;
    setcolor(_BLACK);
    setlinestyle(0,1,2);
    line((4*x3+x4)/5,(y3+2*y4)/3,(x3+2*x4)/3,(4*y3+y4)/5);
    line((x3+2*x4)/3,(4*y3+y4)/5,(x3+x4)/2,(2*y3+3*y4)/5);
    line((x3+x4)/2,(2*y3+3*y4)/5,(2*x4+x3)/3,(3*y3+4*y4)/7);
    line((2*x4+x3)/3,(3*y3+4*y4)/7,(3*x3+7*x4)/10,(4*y4+1*y3)/5);
    line((3*x3+7*x4)/10,(4*y4+1*y3)/5,(9*x4+x3)/10,(4*y4+1*y3)/5);
}
void memoEditor_button_drawSharebutton(Button *b)
{
   int x1 = b->posX1+2, y1 = b->posY1+3,
        x2 = b->posX2-4, y2 = b->posY2-3;
    float k=0.8;
    int x3,x4,y3,y4;
    button_drawWINUI(b);
      if (b->status != ButtonSelected)
    {
        k = 1;
    }
    else
    {
        k = 0.8;
    }
    x3 = (x1 + x2) / 2 - (x2 - x1) * k / 2;
    x4 = (x1 + x2) / 2 + (x2 - x1) * k / 2;
    y3 = (y1 + y2) / 2 - (y2 - y1) * k / 2;
    y4 = (y1 + y2) / 2 + (y2 - y1) * k / 2;
    setcolor(_BLACK);
    setlinestyle(0,1,2);
    arc((5*x4+3*x3)/8,(6*y4+2*y3)/8,90,180,3*(y4-y3)/8);
    arc((5*x4+3*x3)/8,(33*y4-y1)/32,90,157.38,13*(y4-y3)/32);
    line((5*x4+3*x3)/8,(5*y3+3*y4)/8,(5*x4+3*x3)/8,(7*y3+y4)/8);
    line((5*x4+3*x3)/8,(5*y4+3*y3)/8,(5*x4+3*x3)/8,(7*y4+y3)/8);
    line((5*x4+3*x3)/8,(7*y3+y4)/8,(7*x4+x3)/8,(y3+y4)/2);
    line((5*x4+3*x3)/8,(7*y4+y3)/8,(7*x4+x3)/8,(y3+y4)/2);
}

void memoEditor_button_drawEditbutton(Button *b)
{
     int x1 = b->posX1+3, y1 = b->posY1+3,
        x2 = b->posX2-3, y2 = b->posY2-3;
    float k=0.8;
    int x3, x4, y3, y4, m;
    button_drawWINUI(b);
     if (b->status != ButtonSelected)
    {
        k = 1;
    }
    else
    {
        k = 0.8;
    }
    x3 = (x1 + x2) / 2 - (x2 - x1) * k / 2;
    x4 = (x1 + x2) / 2 + (x2 - x1) * k / 2;
    y3 = (y1 + y2) / 2 - (y2 - y1) * k / 2;
    y4 = (y1 + y2) / 2 + (y2 - y1) * k / 2;
    setcolor(_BLACK);
    setlinestyle(0,1,2);
    line((3*x4+x3)/4,(5*y3+y4)/6,(5*x4+x3)/6,(3*y3+y4)/4);
    line((5*x4+x3)/6,(3*y3+y4)/4,(3*x3+x4)/4,(5*y4+y3)/6);
    line((3*x3+x4)/4,(5*y4+y3)/6,(7*x3+x4)/8,(7*y4+y3)/8);
    line((7*x3+x4)/8,(7*y4+y3)/8,(5*x3+x4)/6,(3*y4+y3)/4);
    line((5*x3+x4)/6,(3*y4+y3)/4,(3*x4+x3)/4,(5*y3+y4)/6);
    arc((2*x3+x4)/3+(y4-y3)/15,(4*y4+y3)/5,0,180,(y4-y3)/10);
    arc((2*x3+x4)/3+2*(y4-y3)/10+(y4-y3)/15,(4*y4+y3)/5,180,360,(y4-y3)/10);
    arc((2*x3+x4)/3+2*2*(y4-y3)/10+(y4-y3)/15,(4*y4+y3)/5,0,180,(y4-y3)/10);
    arc((2*x3+x4)/3+3*2*(y4-y3)/10+(y4-y3)/15,(4*y4+y3)/5,180,360,(y4-y3)/10);
}
void memoEditor_button_drawSavebutton(Button *b)
{
     int x1 = b->posX1+5, y1 = b->posY1+6,
        x2 = b->posX2-5, y2 = b->posY2-5;
    float k=0.8;
    int x3, x4, y3, y4, m;
    button_drawWINUIAccent(b);
     if (b->status != ButtonSelected)
    {
        k = 1;
    }
    else
    {
        k = 0.8;
    }
    x3 = (x1 + x2) / 2 - (x2 - x1) * k / 2;
    x4 = (x1 + x2) / 2 + (x2 - x1) * k / 2;
    y3 = (y1 + y2) / 2 - (y2 - y1) * k / 2;
    y4 = (y1 + y2) / 2 + (y2 - y1) * k / 2;
    setcolor(_BLACK);
    setlinestyle(0,1,2);
    line(x3,y3,x4,y3);
    line(x4,y3,x4,y4);
    line(x4,y4,(4*x3+x4)/5,y4);
    line((4*x3+x4)/5,y4,x3,(4*y4+y3)/5);
    line(x3,(4*y4+y3)/5,x3,y3);
    line((7*x3+3*x4)/10,y4,(7*x3+3*x4)/10,(2*y4+y3)/3);
    line((7*x3+3*x4)/10,(2*y4+y3)/3,(7*x3+3*x4)/10+2*(x4-x3)/5,(2*y4+y3)/3);
    line((7*x3+3*x4)/10+2*(x4-x3)/5,(2*y4+y3)/3,(7*x3+3*x4)/10+2*(x4-x3)/5,y4);
    line((4*x3+x4)/5,y3,(4*x3+x4)/5,(2*y3+y4)/3);
    line((4*x3+x4)/5,(2*y3+y4)/3,(4*x4+x3)/5,(2*y3+y4)/3);
    line((4*x4+x3)/5,(2*y3+y4)/3,(4*x4+x3)/5,y3);
}