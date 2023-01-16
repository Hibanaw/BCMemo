#include"page.h"

/**
 * @brief 渲染主页固定页面
 * 
 */
void drawHome(){
	putImage(0, 0, "RES\\HOMEPAGE.BIN");
	puthz(449,500,"点击任意键登陆", 16, 18, _WHITE);
	return;
}

/**
 * @brief 渲染登陆固定页面
 * 
 */
void drawLogin(Textbox tu, Textbox tp, Button b){
	log("Show login page");
	//绘图
	//setfillstyle(SOLID_FILL, _WHITE);
	//bar(0, 0, 1023, 767);
	drawTextbox(tu);
	drawTextbox(tp);
	drawButton(b);
	return ;
}
