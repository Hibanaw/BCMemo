#include"frontend.h"

int genButton(int x, int y, char* text = NULL, int sizex = 100, int sizey = 30){
	int point[] = {
		x, y,
		x+sizex, y,
		x+sizex, y+sizey,
		x, y+sizey,
		x, y
	};
	setcolor(BLACK);
	if(1){
		setfillstyle(SOLID_FILL, BLACK);
	}
	else{
		setfillstyle(SOLID_FILL, WHITE);
	}
	fillpoly(5, point);
	return 0;
}

void welcomePage(){
	
	setbkcolor(LIGHTBLUE);
}

int loginPage(){
	genButton(100,100);
	//»æÍ¼
	//ÅÐ¶Ï°´Å¥µã»÷
	return 0;
}
