#include"page.h"

/**
 * @brief ���ư�ť
 * 
 * @param x ������
 * @param y ������
 * @param text �������
 * @param sizex ���
 * @param sizey �߶�
 * @return int �Ƿ񱻰��£�0Ϊ��1Ϊ��
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
	puthz(300,300,"����������½", 16, 18, WHITE);
	
	return;
}


void pageLogin(){
	log("Show login page");
	int goLogin, goExit;
	//��ͼ
	setfillstyle(SOLID_FILL, BLUE);
	bar(0, 0, 1023, 767);
	textButton(100,100);
	
	return ;
}
