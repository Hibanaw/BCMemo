#include"module.h"

void drawButton(Button b){
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

void drawTextbox(Textbox t){
    setfillstyle(SOLID_FILL, _WHITE);
    bar(t.posX, t.posY, t.posX+t.width, t.posY+t.height);
    setcolor(_BLACK);
    setlinestyle(SOLID_LINE, 1, 10);
    line(t.posX, t.posY, t.posX+t.width, t.posY);
    line(t.posX, t.posY+t.height, t.posX+t.width, t.posY+t.height);
    line(t.posX+t.width, t.posY, t.posX+t.width, t.posY+t.height);
    line(t.posX, t.posY, t.posX, t.posY+t.height);
    //puthz(t.posX, t.posY, t.text, t.fontSize, t.fontSize + 2, t.fontColor);
}

void *saveBg(int x1, int y1, int x2, int y2){
	unsigned long size = imagesize();
    void *buffer=malloc(size);
	if(buffer!=NULL)
		getimage(x1,y1, min(SCREENWIDTH-1, x2),min(SCREENHEIGHT-1, y2),buffer);
	else
		log("save background error", ERR);
}
