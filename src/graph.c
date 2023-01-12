#include"graph.h"

int initsvga256(void) //��ʼ������
{
	int G_driver = DETECT, G_model;
	char Gr_error; //������Ϣ����
	chdir("C:\\win_pro\\etc");
	installuserdriver("Svga256", detectSVGA256);
	initgraph(&G_driver, &G_model, "");
	Gr_error = graphresult();
	if (Gr_error != grOk)
	{
		return 0;
	}
	return 1;
}

int closesvga256(void) //�ر�ͼ��ģʽ����
{
	char Gr_error; //������Ϣ����
	closegraph();
	Gr_error = graphresult();
	if (Gr_error != grOk)
	{
		return 0;
	}
	return 1;
}