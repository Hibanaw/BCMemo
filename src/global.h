/**
 * @file global.h
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-02-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __GLOBAL_H__
#define __GLOBAL_H__


#define MAXHEIGHT 768
#define MAXWIDTH 1024

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define ABS(x) ((x) > 0 ? (x) : -(x))
#define CEILING(f) ((int)(f) + (((f) - (int)(f) > 0) ? 1 : 0))

typedef enum{false, true} bool;

#include "debug.h"

#endif