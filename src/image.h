/**
 * @file image.h
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-02-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __IMAGE_H__
#define __IMAGE_H__


void image_render(char *, int, int);
void image_getSize(char *, int*, int *);
int image_illegal(char *path);


#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include "global.h"

#endif