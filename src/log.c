/**
 * @file log.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-02-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "log.h"

void log(enum LogLevel l, char *s){
    char * t;
    char str[101];
    int fl;
    if(l >= LOGLEVEL){
        switch (l)
        {
        case DEBUG:
            t = "[DBG]";
            break;
        case LOG:
            t = "[LOG]";
            break;
        default:
            t = "[ERR]";
        }
        sprintf(str, "%s%s", t, s);
        settextstyle(0, 0, 2);
        fl = textwidth(str);
        setfillstyle(1, _WHITE);
        bar(0, 0, fl, 16);
        setcolor(_BLACK);
        setwritemode(COPY_PUT);
        outtextxy(0, 0, str);
    }
}