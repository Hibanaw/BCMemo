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
#include "button.h"

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

    Button button;
}Ime;

void ime_init();
int ime_input(char *s);
int ime_en(char *s);
void ime_check();
void ime_next();
void ime_draw();
#endif