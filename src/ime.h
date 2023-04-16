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

#include "button.h"

enum imeStatus{
    IMEOFF,
    IMEPINYIN,
    IMEEMOJI
};

typedef struct
{
    enum imeStatus status;
    int pw;
    char buffer[8241];
    Button button;
}Ime;

Ime *ime();
void ime_init();
int ime_input(char *s, int x, int y);
int ime_en(char *s);
void ime_check();
void ime_next();
void ime_draw();

#include <bios.h>
#include <time.h>
#include "text.h"
#include "hzinput.h"
#endif