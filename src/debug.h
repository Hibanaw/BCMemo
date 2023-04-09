/**
 * @file debug.h
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-02-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __LOG_H__
#define __LOG_H__

#define LOGLEVEL 3

#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "global.h"
#include "svga.h"

enum LogLevel{
    DEBUG,
    LOG,
    ERROR
};

void debug(enum LogLevel, char *);

#endif