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

void log(enum LogLevel l, string s){
    string t;
    if(l >= LOGLEVEL){
        switch (l)
        {
        case DEBUG:
            t = "[DBG]";
            break;
        case LOG:
            t = "[LOG]";
        default:
            t = "[ERR]";
        }
        printf("%s%s\n", t, s);
    }
}