/**
 * @file ime.h
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-03-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __IME_H__
#define __IME_H__

#include <bios.h>
#include <time.h>
#include "text.h"
#include "hzinput.h"

enum imeStatus{
    IMEOFF,
    IMEPINYIN,
    IMEEMOJI
};

typedef struct
{
    int posX;
    int posY;
    enum imeStatus status;
    int noticeBox;
    clock_t lastChangeTime;
    void *buffer;
}Ime;

int ime_input(char *s);
void ime_next();
void ime_draw(int x, int y, enum imeStatus status);
void ime_saveBackgrond(int x, int y, void *buffer);
void ime_clearIme(int x, int y, void *buffer);

#endif