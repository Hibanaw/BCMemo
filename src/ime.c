/**
 * @file ime.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-03-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ime.h"

Ime *ime(){
    static Ime i;
    return &i;
}

/**
 * @brief Input Function
 * 
 * @param s Inputed string.
 * @return int as string length. -1 if backspace.
 */
int ime_input(char *s, int x, int y){
    int k = bioskey(1);
    if(keybord_isControlOn()){
        return;
    }
    if(keybord_isBACKSPACE(k)){
        bioskey(0);
        return -1;
    }
    switch(ime()->status){
        case IMEOFF:
            return ime_en(s);
            break;
        case IMEPINYIN:
            return hzinput(x, y, s);
            break;
        case IMEEMOJI:
            break;
    }
    return 0;
}

void ime_check(){
    if(ime()->pw){
        ime()->status = IMEOFF;
        return;
    }
    // ����ݼ��л�
    if(bioskey(2)&0x04){
        if(bioskey(1) == KEYSPACE){
            bioskey(0);
            ime_next();
        }
    }
    if(button_event(&ime()->button)){
        ime_next();
    }
}

void ime_next(){
    ime() -> status = (ime() -> status + 1) % 2;
    ime_draw();
    debug(DEBUG, "IME change");
}

void ime_draw(){
    int x = 900, y = 0;
    Text t = text_newDefault(NULL, x+3, y+2, 0, 0);
    int status = ime()->status;
    t.font.fontSize = 16;
    t.font.fontColor = _BLACK,
    t.font.spacing = 2;
    t.font.rowSpacing = 0;
    setfillstyle(1, _BLACK);
    bar(x, y, x+20, y+20);
    setfillstyle(1, _WHITE);
    bar(x+1, y+1, x+19, y+19);
    switch (status){
        case IMEOFF:
            t.content = "Ӣ";
            break;
        case IMEPINYIN:
            t.content = "��";
            break;
        case IMEEMOJI:
			t.content = "��";
            break;
    }
    text_display(t);
}

int ime_en(char *s){
    int k = bioskey(1);
    if(keybord_isCharacter(k)){
        bioskey(0);
        *s = keybord_bios2ascii(k);
        return 1;
    }
    return 0;
}

void ime_init(){
    Ime *i = ime();
    memset(i, 0, sizeof(Ime));
    i->button = button_new(
        900, 0,
        920, 20,
        NULL,
        ime_draw
    );
}