#ifndef _IMAGE_H_
#define _IMAGE_H_

#include<graphics.h>
#include"svga.h"
#include"hz.h"

#ifndef NULL
#define NULL 0
#endif

void putImage(int x, int y, const char* imagePath);

#endif