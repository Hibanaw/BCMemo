#include"page.h"

/**
 * @brief ��Ⱦ��ҳ�̶�ҳ��
 * 
 */
void drawHome(){
	putImage(0, 0, "RES\\HOMEPAGE.BIN");
	puthz(449,500,"����������½", 16, 18, _WHITE);
	return;
}

/**
 * @brief ��Ⱦ��½�̶�ҳ��
 * 
 */
void drawLogin(Textbox tu, Textbox tp, Button b){
	log("Show login page");
	//��ͼ
	//setfillstyle(SOLID_FILL, _WHITE);
	//bar(0, 0, 1023, 767);
	drawTextbox(tu);
	drawTextbox(tp);
	drawButton(b);
	return ;
}
