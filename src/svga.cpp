#include"svga.h"
int huge detectSVGA256(void) //������������ĺ���
{
	return SVGA1024x768x256; //�߷ֱ���ʵ��
}

int initsvga256(void) //��ʼ������
{
	int G_driver = DETECT, G_model;
	char Gr_error; //������Ϣ����
	installuserdriver("SVGA256", detectSVGA256);
	initgraph(&G_driver, &G_model, "");
	Gr_error = graphresult();
	if (Gr_error != grOk)
	{
        log("SVGA256 init faild as %d", ERR, Gr_error);
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