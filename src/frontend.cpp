#include"frontend.h"

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
int genButton(int x, int y, char* text, int width, int height){
	int point[] = {
		x, y,
		x+width, y,
		x+width, y+height,
		x, y+height,
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

void homePage(){
	setfillstyle(SOLID_FILL, GREEN);
	bar(0, 0, 1023, 767);
	puthz(300,300,"点击任意键登陆", 16, 18, WHITE);
	
	return 0;
}

/**
 * @brief 
 * 
 * @return LoginPageContent 包含用户名、密码、状态，其中1为点击登陆，-1为退出
 */
int loginPage(Textbox* uBox, Textbox* pBox){
	log("Show login page");
	int goLogin, goExit;
	//绘图
	setfillstyle(SOLID_FILL, WHITE);
	bar(0, 0, 1023, 767);
	//genButton(100,100);
	
	//鼠标事件
	int x, y, c;
	newmouse(&x, &y, &c);
	//键盘事件
	int k = -1;
	if(bioskey(1)){
		k = bioskey(0);
	}

	//获取文本框

	//判断登陆

	if(goLogin){
		return 1;
	}
	//判断退出
	if(k == ESCAPE) goExit = 1;
	if(goExit){
		return -1;
	}
	return 0;
}
