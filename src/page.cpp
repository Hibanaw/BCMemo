#include"page.h"

/**
 * @brief 绘制按钮
 * 
 * @param x 横坐标
 * @param y 纵坐标
 * @param text 填充内容
 * @param sizex 宽度
 * @param sizey 高度
 * 
 */
int pageButton(int x, int y, char* text, int width, int height){
	
}
/**
 * @brief 渲染主页固定页面
 * 
 */
void pageHome(){
	putImage(0, 0, "RES\\HOMEPAGE.BIN");
	puthz(449,500,"点击任意键登陆", 16, 18, _WHITE);
	return;
}

/**
 * @brief 渲染登陆固定页面
 * 
 */
void pageLogin(){
	log("Show login page");
	int goLogin, goExit;
	//绘图
	setfillstyle(SOLID_FILL, BLUE);
	bar(0, 0, 1023, 767);
	//textButton(100,100);
	
	return ;
}
