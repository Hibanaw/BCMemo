#include"module.h"

void newButton(Button b){
    switch(b.status){
        case 0:
            setfillstyle(SOLID_FILL, _WHITE);
            break;
        case 1:
            setfillstyle(SOLID_FILL, _GRAY);
            break;
        case 2:
            setfillstyle(SOLID_FILL, _DARKGRAY);
            break;
    }
    int x = b.posX, y = b.posY, width = b.width, height = b.height;
    int point[] = {
		x, y,
		x+width, y,
		x+width, y+height,
		x, y+height,
		x, y
	};
	fillpoly(5, point);
}