#include"page.h"

/**
 * @brief 绘制按钮
 * 
 * @param x 横坐标
 * @param y 纵坐标
 * @param text 填充内容
 * @param sizex 宽度
 * @param sizey 高度
 * @return int 是否被按下，0为否1为真
 */
int textButton(int x, int y, char* text, int width, int height){
	int point[] = {
		x, y,
		x+width, y,
		x+width, y+height,
		x, y+height,
		x, y
	};
	
	setcolor(BLACK);
	if(1){
		setfillstyle(SOLID_FILL, WHITE);
	}
	else{
		setfillstyle(SOLID_FILL, CYAN);
	}
	fillpoly(5, point);
	return 0;
}

void pageHome(){
	setfillstyle(SOLID_FILL, GREEN);
	bar(0, 0, 1023, 767);
	puthz(300,300,"点击任意键登陆", 16, 18, WHITE);
	
	return;
}


void pageLogin(){
	log("Show login page");
	int goLogin, goExit;
	//绘图
	setfillstyle(SOLID_FILL, BLUE);
	bar(0, 0, 1023, 767);
	textButton(100,100);
	
	return ;
}
