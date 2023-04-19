/**
 * @file scroll.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "scroll.h"

ScrollBar scrollBar_new(int x, int y, int h){
    ScrollBar sb;
    memset(&sb, 0, sizeof(sb));
    sb.posX = x;
    sb.posY = y;
    sb.status = 0;
    sb.width = 15;
    sb.height = h;
    sb.length = 0;
    sb.inScreenItem = sb.sumItem = 0;
    sb.barPosY1 = sb.barPosY2 = 0;
    sb.mouseLastPosY = 0;
    sb.bgColor = _WHITE;
    return sb;
}

int scrollBar_event(ScrollBar *sb){
    int dy;
    int h;
    int ls = sb->status;
    int y1, y2, l;
    if(ls != ScrollBarDefault && mouse_isClickedInBox(sb->posX, sb->posY, sb->posX+sb->width, sb->posY + sb->height) <= 0){
        sb->status = ScrollBarDefault;
        mouse()->style = CURSORPOINTER;
        mouse_hide();
		scrollBar_draw(sb);
        mouse_show();
    }
    if(ls != ScrollBarFocused && mouse_isClickedInBox(sb->posX, sb->posY, sb->posX+sb->width, sb->posY + sb->height) == 2){
        sb->status = ScrollBarFocused;
        mouse()->style = CURSORPOINTER;
        mouse_hide();
		scrollBar_draw(sb);
        mouse_show();
	}
	if(ls != ScrollBarSelected && mouse_isClickedInBox(sb->posX, sb->posY, sb->posX+sb->width, sb->posY + sb->height) == 1){
		sb->status = ScrollBarSelected;
        mouse()->style = CURSORPOINTER;
		sb->mouseLastPosY = mouse()->posY;
        mouse_hide();
		scrollBar_draw(sb);
        mouse_show();
	}
	if(!sb->sumItem){
		return 0;
	}
    h = sb->height * sb->inScreenItem / sb->sumItem;
    if(sb->status == ScrollBarSelected){
        dy = mouse()->posY - sb->mouseLastPosY;
        sb->barPosY1 += dy;
        if(sb->barPosY1 > sb->posY+sb->height-h){
            sb->barPosY1 = sb->posY+sb->height-h;
        }
        if(sb->barPosY1 < sb->posY){
            sb->barPosY1 = sb->posY;
        }
        sb->barPosY2 = sb->barPosY1 + h;
        if(ABS(sb->lastDrawBarPosY1 - sb->barPosY1) > 5 || ABS(sb->lastDrawBarPosY2 - sb->barPosY2) > 5){
            mouse_hide();
            scrollBar_draw(sb);
            mouse_show();
            sb->lastDrawBarPosY1 = sb->barPosY1;
            sb->lastDrawBarPosY2 = sb->barPosY2;
        }
        if((sb->barPosY1-sb->posY) / (sb->height/sb->sumItem) < sb->ithItem){
            return -1;
        }
        if((sb->barPosY1-sb->posY) / (sb->height/sb->sumItem) > sb->ithItem){
            return 1;
        }
        sb->mouseLastPosY = mouse()->posY;
    }
    else{
        sb->barPosY1 = sb->posY + sb->height * sb->ithItem / sb->sumItem;
        sb->barPosY2 = sb->barPosY1 + h;
        return 0;
    }

}

void scrollBar_draw(ScrollBar *sb){
    int x;
    setfillstyle(1, sb->bgColor);
    bar(sb->posX, sb->posY, sb->posX+sb->width, sb->posY+sb->height);
    if(sb->inScreenItem == sb->sumItem){
        return;
    }
    x = sb->posX + 5;
    switch (sb->status)
    {
    case ScrollBarDefault:
        setfillstyle(1, hex808080);
        bar(x+4, sb->barPosY1, x+5, sb->barPosY2);
        break;
    case ScrollBarFocused:
        setfillstyle(1, hex555f55);
        setcolor(hex555f55);
        pieslice(x+3, sb->barPosY1+3, 0, 180, 2);
        pieslice(x+3, sb->barPosY2-3, 180, 360, 2);
        bar(x+1, sb->barPosY1+3, x+5, sb->barPosY2-3);
        break;
    case ScrollBarSelected:
        setfillstyle(1, hex555f55);
        setcolor(hex555f55);
        pieslice(x+3, sb->barPosY1+3, 0, 180, 2);
        pieslice(x+3, sb->barPosY2-3, 180, 360, 2);
		bar(x+1, sb->barPosY1+3, x+5, sb->barPosY2-3);
        break;
    }
    return;
}