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
int ime_input(char *s){
    int k;
    switch(ime()->status){
        case IMEOFF:
            //log(DEBUG, "imeoff, get input");
            k = keybord_getKey();
            if(keybord_isBACKSPACE(k)){
                return -1;
            }
            if(keybord_isCharacter(k)){
                *s = keybord_bios2ascii(k);
                return 1;
            }
            break;
        case IMEPINYIN:
            
            break;
        case IMEEMOJI:
            break;
    }
    return 0;
}

Ime ime_check(){
    // ¼à²â¿ì½Ý¼üÇÐ»»
    if(bioskey(1)){
        if(bioskey(2)&0x04 && bioskey(0) & 0xff == ' '){
            ime_next();
        }
    }
    // ¼à²âÌáÊ¾¿ò
    if(clock()-ime()->lastChangeTime / CLK_TCK > 2){

    }
}

void ime_next(){
    ime() -> status = (ime() -> status + 1) % 3;
    ime() -> lastChangeTime = clock();
    if(!ime()->noticeBox){
        ime()->noticeBox = 1;
        //ime_saveBackgrond();
    }
}

void ime_draw(int x, int y, enum imeStatus status){
    Text t = text_newDefault(NULL, x+2, y+2, 0, 0);
    t.font.fontSize = 16;
    t.font.fontColor = _BLACK,
    t.font.spacing = 2;
    t.font.rowSpacing = 0;
    setcolor(_BLACK);
    bar(x, y, x+20, y+20);
    setcolor(_WHITE);
    bar(x+2, y+2, x+18, y+18);
    switch (status){
        case IMEOFF:
            t.content = "Aa";
            break;
        case IMEPINYIN:
            t.content = "ÎÄ";
            break;
        case IMEEMOJI:
            t.content = "\160\0";
            break;
    }
    text_display(t);
}

void ime_saveBackgrond(int x, int y, void *buffer){
    int size = imagesize(0, 0, 20, 20);
    buffer = malloc(size);
    getimage(x, y, x+20, y+20, buffer);
}

void ime_clearIme(int x, int y, void *buffer){

    putimage(x, y, buffer, COPY_PUT);
    free(buffer);
}