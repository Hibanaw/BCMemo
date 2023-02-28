/**
 * @file log.h
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-02-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __LOG_H__
#define __LOG_H__

#define LOGLEVEL 0

#include <stdio.h>
#include "global.h"

enum LogLevel{
    DEBUG,
    LOG,
    ERROR
};

void log(enum LogLevel, string);

#endif