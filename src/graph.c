#include"graph.h"

int initsvga256(void) //初始化函数
{
	int G_driver = DETECT, G_model;
	char Gr_error; //错误信息储存
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

int closesvga256(void) //关闭图像模式函数
{
	char Gr_error; //错误信息储存
	closegraph();
	Gr_error = graphresult();
	if (Gr_error != grOk)
	{
		return 0;
	}
	return 1;
}