#include"frontend.h"

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
	puthz(300,300,"����������½", 16, 18, WHITE);
	
	return 0;
}

/**
 * @brief 
 * 
 * @return LoginPageContent �����û��������롢״̬������1Ϊ�����½��-1Ϊ�˳�
 */
int loginPage(Textbox* uBox, Textbox* pBox){
	log("Show login page");
	int goLogin, goExit;
	//��ͼ
	setfillstyle(SOLID_FILL, WHITE);
	bar(0, 0, 1023, 767);
	//genButton(100,100);
	
	//����¼�
	int x, y, c;
	newmouse(&x, &y, &c);
	//�����¼�
	int k = -1;
	if(bioskey(1)){
		k = bioskey(0);
	}

	//��ȡ�ı���

	//�жϵ�½

	if(goLogin){
		return 1;
	}
	//�ж��˳�
	if(k == ESCAPE) goExit = 1;
	if(goExit){
		return -1;
	}
	return 0;
}
