/**
 * @file mset.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "mset.h"

int mset_page(MemoEditor *me){
    int ol = memo()->level;
    int oa = me->authType;
    while(1){
        int fl = ol, fa = oa;
        Button saveButton = button_new(690, 450, 780, 490, "保存", button_drawWINUIAccent);
        Button exitButton = button_new(580, 450, 670, 490, "取消", button_drawWINUI);
        Text title = text_newDefault("备忘录设置", 486, 80, 0, 0);
        Text levelT = text_newSmall("等级：", 350, 150);
        Text authT = text_newSmall("权限：", 350, 300);
        Text levelTS = text_newSmall("低级       中级       高级", 390, 190);
        Text authTS = text_newSmall("私有       共有       白名单", 390, 340);
        MsetRadioBoxArea levelR;
        MsetRadioBoxArea authR;
        int signal = 0;
        mset_newRadioBoxArea(&levelR, 180, ol);
        mset_newRadioBoxArea(&authR, 330, oa);
        mouse_hide();
        setfillstyle(1, hexfffbf0);
        bar(300, 72, 800, 500);
        button_draw(&exitButton);
        button_draw(&saveButton);
        text_display(title);
        text_display(levelT);
        text_display(authT);
        text_display(levelTS);
        text_display(authTS);
        mset_drawRadioBoxArea(&levelR);
        mset_drawRadioBoxArea(&authR);

        mouse_show();
        while(!signal){
            int k = bioskey(1);
            int bs = button_event(&exitButton), sbs = button_event(&saveButton);
            int lras = 0, aras = 0;
            digitalClock_getTime();
            keybord_eat();
            mouse_update();
            lras = mset_radioBoxAreaEvent(&levelR);
            aras = mset_radioBoxAreaEvent(&authR);
            if(keybord_isESCAPE(k)){
                bioskey(0);
                signal = -1;
            }
            if(bs){
                signal = -1;
            }
            if(sbs){
                signal = 1;
            }
            if(lras){
                fl = lras - 1;
            }
            if(aras){
                fa = aras - 1;
            }
        }
        switch (signal)
        {
        case -1:
            return 0;
            break;
        
        case 1:
            memo()->level = fl;
            me->authType = fa;
            return 0;
            break;
        }
    }
}


int mset_newRadioBoxArea(MsetRadioBoxArea *ra, int y, int defualt){
    int i;
    for(i = 0; i < 3; i++){
        ra->radioBox[i] = button_new(360+i*144, y, 380+i*144, y+20, 0, button_checkboxDraw);
    }
    ra->radioBox[defualt%3].content = 1;
    return 0;
}

void mset_drawRadioBoxArea(MsetRadioBoxArea *sr){
    int i;
    for(i = 0; i < 3; i++){
        button_draw(sr->radioBox+i);
    }
}

int mset_radioBoxAreaEvent(MsetRadioBoxArea *sr){
    int k = 0;
    int lf, nf = -1;
    int i;
    for(i = 0; i < 3; i++){
        if((int)(sr->radioBox[i].content) == 1){
            lf = i;
        } 
        if(button_event(sr->radioBox+i) == 1){
            k = 1;
            nf = i;
        }
    }
    if(k && nf != lf){
        sr->radioBox[lf].content = 0;
        sr->radioBox[nf].content = 1;
        mouse_hide();
        mset_drawRadioBoxArea(sr);
        mouse_show();
    }
    return nf+1;
}