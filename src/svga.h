/*************************************************************
 SVGA头文件编写
*************************************************************/

#ifndef	_SVGAmode_H_
#define	_SVGAmode_H_


#include<stdio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<alloc.h>
#include<math.h>
#include<time.h>
typedef struct
{
	unsigned char B;	/*蓝色分量，BLUE缩写*/
	unsigned char G;	/*绿色分量，GREEN缩写*/
	unsigned char R;	/*红色分量，RED缩写*/
} WESHEN;
/***************************************************************
 延迟时间
****************************************************************/
 extern  void delay0(int x);

/**************************************************************
  SVGA显示模式设置函数      模式号0x105
**************************************************************/
extern void  SetSVGA256(void);



extern void  SetSVGA64k(void);


/**************************************************************
  得到当前SVGA显示模式函数
***************************************************************/
extern unsigned int GetSVGA(void);


/***************************************************************
   显存换页函数
***************************************************************/
extern unsigned int SelectPage(unsigned char page);


/***************************************************************
  画点函数
***************************************************************/
extern  void   putpixel(int x,int y,int color); 

extern void Putpixel64k(int x, int y, int color);
extern int Putbmp64k00(int x, int y, const char * path);
/****************************************************************
异或画点函数
***************************************************************/



/*************************************************************
异或画矩形
*************************************************************/


/*****************************************************************
异或画空心圆
******************************************************************/



/******************************************************************
异或画实心圆
*******************************************************************/


/*得到当前点的像素*/

extern   unsigned int Getpixel64k(int x, int y);


/***************************************************************
   得到当前点的颜色值
****************************************************************/ 
extern   int   getpixel(int x,int y);

 /**************************************************************
 画横线函数
 ***************************************************************/
extern void linelevel(int x0,int y0,int x1,int y1,int thick,int color);


 /**************************************************************
 画竖线函数
 ***************************************************************/
extern void linever(int x0,int y0,int x1,int y1,int thick,int color);







/**************************************************************
将8位无压缩bmp图片显示在屏幕指定位置上的函数
返回0为失败，返回1为成功 
*****************************************************************/
extern int   Readbmp256(int x,int y, char * path);
 
/*****************************************************************
 将24位无压缩图片显示在屏幕上
 *****************************************************************/
  
extern int Putbmp64k(int x, int y, const char * path);
 
//extern void bmp_fast(const char * path);
 

extern void Horizline(int x, int y, int width, int  color);

 /***************************************************************
 画矩形函数
 *****************************************************************/
 extern  void bar(int x0,int y0,int x1,int y1,int color);
 
 /******************************************************************
 画圆圈函数，空心不填充
 *********************************************************************/
 extern void circle(int x0,int y0,int radius,int color); 
 
  /*********************************************************************
 画实心圆函数
 **********************************************************************/
 extern  void FillCircle(int x, int y, int r, int color);
 
 /*************************************************************************
 得到一片区域的图像信息
 ********************************************************************/
extern  void get_image(int x0,int y0,int x1,int y1,unsigned int far *save);

/****************************************************************************
显示这一片区域的图像信息
*******************************************************************************/
extern void put_image(int x0,int y0,int x1,int y1,unsigned int far *save);
 

/**************************************************
10月26日编写
function:       save_image

description:    显示出存储空间的图像信息

Input:          x0,y0,左上角起始坐标，X1,Y2右下角坐标,将图像信息存到文件里面

out:            
**************************************************************/
extern void save_image(int x0, int y0, int x1, int y1);


/**************************************************
10月26日编写
function:       printf_image

description:    从文件中读取这个背景像素

Input:          x0,y0,左上角起始坐标，X1,Y2右下角坐标,将图像信息覆盖到界面上

out:
**************************************************************/

extern void  printf_image(int x0, int y0, int x1, int y1);


/**************************************************
10月26日编写
function:       save_image

description:    显示出存储空间的图像信息

Input:          x0,y0,左上角起始坐标，X1,Y2右下角坐标,将图像信息存到文件里面

out:            
**************************************************************/
extern void save_image0(int x0, int y0, int x1, int y1);


/**************************************************
10月26日编写
function:       printf_image

description:    从文件中读取这个背景像素

Input:          x0,y0,左上角起始坐标，X1,Y2右下角坐标,将图像信息覆盖到界面上

out:
**************************************************************/

extern void  printf_image0(int x0, int y0, int x1, int y1);




 #endif
