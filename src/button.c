/**
 * @file button.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-02-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "button.h"


void button_draw(Button *b){
	int x1 = b->posX1, y1 = b->posY1,
		x2 = b->posX2, y2 = b->posY2;
    setcolor(_GRAY);
    bar(x1+1, y1+1, x2+1, y2+1);
    setbkcolor(_WHITE);
    setfillstyle(EMPTY_FILL, _WHITE);
    setcolor(_BLACK);
    bar(x1, y1, x2, y2);
}