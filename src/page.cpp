#include"page.h"

/**
 * @brief ���ư�ť
 * 
 * @param x ������
 * @param y ������
 * @param text �������
 * @param sizex ���
 * @param sizey �߶�
 * 
 */
int pageButton(int x, int y, char* text, int width, int height){
	
}
/**
 * @brief ��Ⱦ��ҳ�̶�ҳ��
 * 
 */
void pageHome(){
	putImage(0, 0, "RES\\HOMEPAGE.BIN");
	puthz(449,500,"����������½", 16, 18, _WHITE);
	return;
}

/**
 * @brief ��Ⱦ��½�̶�ҳ��
 * 
 */
void pageLogin(){
	log("Show login page");
	int goLogin, goExit;
	//��ͼ
	setfillstyle(SOLID_FILL, BLUE);
	bar(0, 0, 1023, 767);
	//textButton(100,100);
	
	return ;
}
