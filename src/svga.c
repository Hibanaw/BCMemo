/**********************************************
   本文件作为一些图形显示，鼠标操作函数
   其中画一般直线line 和画实心圆函数为参考代码 不计入总代码量 
   首次编译时间8月23日
   制作人：黄昱恺

   第一次改动时间：9月13日 增加0x117显示模式
***********************************************/

#include"svga.h"

/*BMP文件头结构*/
typedef struct tagBITMAPFILEHEADER
{
	int	bfType;	         /*  通常是 'BM' 。现在来看似乎判断 OS/2 的标识已无什么意义*/
	long	 bfSize;	/*  文件大小，以字节为单位*/
	int	bfReserved1;	/*保留，必须设置为 0*/
	int	bfReserved2;	/*保留，必须设置为 0*/
	long	bfOffBits;
} BITMAPFILEHEADER ;

/*BMP信息头结构*/
typedef struct tagBITMAPINFOHEADER
{
	long	biSize;	/* 信息头大小 */
	long	biWidth;	/* 图像宽度 */
	long	biHeight;	/* 图像高度 */
	int   	biPlanes;	/*  必须为 1 */
	int	    biBitCount;	/*  每像素位数，必须是 1, 4, 8 或 24 */
	long	biCompression;	/*  压缩方法 */
	long	biSizeImage;	/* 实际图像大小，必须是 4 的倍数 */
	long	biXPelsPerMeter;	/*  水平方向每米像素数 */
	long	biYPelsPerMeter;	/*  垂直方向每米像素数*/
	long	biClrUsed;	/*  所用颜色数*/
	long	biClrImportant;	/* 重要的颜色数 */
} BITMAPINFOHEADER;

typedef struct tagRGBQUAD
{
	unsigned char B;	/*蓝色分量，RED缩写*/
	unsigned char G;	/*绿色分量，GREEN缩写*/
	unsigned char R;	/*红色分量，BLUE缩写*/
	unsigned char reserved;		/*保留字*/
} RGBQUAD;


/***********************************************/
/*在dos.h中REGS的定义如下：
	struct WORDREGS
	{
		unsigned int ax, bx, cx, dx, si, di, cflag, flags;
	};

	struct BYTEREGS
	{
		unsigned char al, ah, bl, bh, cl, ch, dl, dh;
	};

	union REGS
	{
		struct WORDREGS x;
		struct BYTEREGS h;
	};
**************************************************/

/**************************************************************
功能说明：延迟函数
参数说明：x为延迟时间
无返回值
**************************************************************/
 void delay0(int x)
 {
 	int i,j,k;
 	for(i=0;i<x;i++)
 	{
		for (j = 0; j < 1100; j++);
		
	}
 } 

/*设置SVGA显示模式 1024*768 256*/
void  SetSVGA256()
{

  union REGS in;
  in.x.ax=0x4f02;
  in.x.bx=0x105;           /*1024*768*256对应的模式编号*/
  int86(0x10,&in,&in);
  if(in.x.ax!=0x004f)     /*(1)功能调用成功，返回AX = 004Fh；
							 (2)不支持该功能，一般返回AX = 4F00h；
							 (3)支持该功能但该功能调用失败，返回AX = 014Fh*/
  {
   printf("There is an error in setting SVGA256,0x%x\n",in.x.ax);
   exit(1);
  }
}



/*设置SVGA显示模式 1024*768 64k*/
void  SetSVGA64k()
{

  union REGS in;
  in.x.ax=0x4f02;
  in.x.bx=0x117;           /*1024*768*64k对应的模式编号*/
  int86(0x10,&in,&in);
  if(in.x.ax!=0x004f)     /*(1)功能调用成功，返回AX = 004Fh；
							 (2)不支持该功能，一般返回AX = 4F00h；
							 (3)支持该功能但该功能调用失败，返回AX = 014Fh*/
  {
   printf("There is an error in setting SVGA256,0x%x\n",in.x.ax);
   exit(1);
  }
}



/***********************************************
  功能说明：获得当前SVGA显示模式的信息
  返回参数说明：得到显示模式号
************************************************/
unsigned int GetSVGA(void)
{
 union REGS out;
 out.x.ax=0x4f03;
 int86(0x10,&out,&out);
 if(out.x.ax!=0x004f)
 {
  printf("there is an error 0x%x\n",out.x.ax);
  exit(1);
 }
 return(out.x.bx);
}
/****************************************************/

/*获取SVGA显示模式号bx。摘录常用的模式号如下：
				模式号		分辨率		颜色数
				0x101		640*480		256
				0x103		800*600		256
				0x104		1024*768	16
				0x105		1024*768	256
				0x110		640*480		32K
				0x111		640*480		64K
				0x112		640*480		16.8M
				0x113		800*600		32K
				0x114		800*600		64K
				0x115		800*600		16.8M
				0x116		1024*768	32K
				0x117		1024*768	64K
				0x118		1024*768	16.8M
 ******************************************************/


 /******************************************************
 功能说明：显存换页
 参数说明: page ,页面号
 ********************************************************/
unsigned int SelectPage(unsigned char page)
{
	union REGS r;
	static unsigned char old_page = 0;    
	static unsigned char flag = 0;
	r.x.ax = 0x4f05;
	r.x.bx = 0;
	if (flag == 0)
	{
		old_page = page;
		r.x.dx = page;
		int86(0x10, &r, &r);
		flag++;
	}
	if (page != old_page)
	{
		old_page = page;
		r.x.dx = page;
		int86(0x10, &r, &r);
	}

	return 0;
}
 /********************************************************/

 /********************************************************
	功能说明 ：画点函数
	参数说明：x,y 所要画点位置 color 颜色
**********************************************************/
   void   putpixel(int x,int y,int color)
 {
  unsigned char far*VideoBuffer=(unsigned char far*)0xa0000000L;
  unsigned long int pos;
  register int Newpage=0;
  /*计算显存地址偏移量和对应的页面号，做换页操作 */
  pos=((unsigned long int)y<<10)+x;
  Newpage=pos>>16;
  SelectPage(Newpage);
  VideoBuffer[pos]=color;
  }
/**********************************************************
  功能说明：得到某点的颜色值；
  参数说明：x,y为该点的坐标；
  返回值：color为该点的颜色值
***********************************************************/ 

int  getpixel(int x,int y)
 {
  int color;
  unsigned char far*VideoBuffer=(unsigned char far*)0xa0000000L;
  unsigned long int pos;
  register int Newpage=0;
  /*计算显存地址偏移量和对应的页面号，做换页操作 */
  pos=((unsigned long int)y<<10)+x;
  Newpage=pos>>15;
  SelectPage(Newpage);
  color=VideoBuffer[pos];
  return color;
  }

  
  
 /*******************************************************
 功能说明：  异或画点函数
 参数说明：   x,y为像素位置，color 为异或的颜色
 返回值：    无
/**********************************************************/
void Xorpixel (int x, int y, int color)
{
	/*显存指针常量，指向显存首地址，指针本身不允许修改*/
	unsigned int far * const video_buffer = (unsigned int far *)0xa0000000L;

	/*要切换的页面号*/
	unsigned char newpage = 0;

	unsigned char oldpage;
	/*对应显存地址偏移量*/
	unsigned long int page;

	/*计算显存地址偏移量和对应的页面号，做换页操作*/
	page = ((unsigned long int)y << 10) + x;
	newpage = page >> 15;	                          /*32k个点一换页，除以32k的替代算法*/

	
		SelectPage(newpage);


	/*向显存写入颜色，对应点画出*/
	video_buffer[page] = video_buffer[page]^color;
}

/*************************************************************
功能函数：用64k的模式画点
参数说明：画点的位置
返回值说明： 无返回
***************************************************************/
void Putpixel64k(int x, int y,  int color)
{
	if(x>=0&&x<=1024&&y>=0&&y<=768)
	{
	/*显存指针常量，指向显存首地址，指针本身不允许修改*/
	unsigned int far * const video_buffer = (unsigned int far *)0xa0000000L;
	
	/*要切换的页面号*/
	unsigned char newpage=0;
	
//	unsigned char oldpage=0;
	/*对应显存地址偏移量*/
	unsigned long int page;

	
	/*计算显存地址偏移量和对应的页面号，做换页操作*/
	page = ((unsigned long int)y << 10) + x;
	newpage = page >> 15;	/*32k个点一换页，除以32k的替代算法*/
	

		SelectPage(newpage);

	
	
	/*向显存写入颜色，对应点画出*/
	video_buffer[page] = color;	
    }
}

/***********************************************************
	功能说明：从硬盘读取8位BMP直接到显存
	参数说明：x，y坐标  name：文件路径
	返回值说明：
/***********************************************************/

int   Readbmp256(int x,int y,char * path)
{
   FILE *fp;                   //指向图片文件的文件指针
   RGBQUAD * pc01;       //bmp颜色表结构指针
   unsigned char *buf;         //行像素缓存指针
   long int wide,high;         //图片宽度，长度
   long int perline;          //一行像素所占字节
   unsigned long int clrused;  //实际用的颜色数
   int i,j;
   unsigned int bitcount;

   if((fp=fopen(path,"rb"))==NULL)
   {
	printf("there file can't open\n");
	delay(5000);
	exit(1);
	}


	fseek(fp,28L,0);          /*先判断是不是8位BMP*/
	fread(&bitcount,2,1,fp);
	if(bitcount!=8)
	{
	 printf("it is not 8");
	 delay(5000);
	 return 0;
	}


	fseek(fp,18L,0);         /*将文件指针移动到储存宽度的位置并读取数据*/
	fread(&wide,4,1,fp);
	fread(&high,4,1,fp);

	perline=(wide*8+31)/8;   /*一个扫面行所占的字节数，必须是4的倍数*/
	perline=perline/4*4;

	fseek(fp,46l,0);          /*得到实际使用颜色*/
	fread(&clrused,4,1,fp);

	if(clrused==0)
	{
	 clrused=1U<<8;
	}

	if((pc01=(RGBQUAD*)malloc(4L*clrused))==NULL)   /*依据使用颜色个数来分配空间*/
	{
	 printf("the color is wrong");
	 delay(5000); 
	 return 0;
	}
	
	fseek(fp,54L,0);            /*读取颜色表数据*/
	fread(pc01,4L*clrused,1,fp); 
	
	for(i=0;i<clrused;i++,pc01++)
	{
	 outportb(0x3c8,i);
	 outportb(0x3c9,pc01->R>>2);
	 outportb(0x3c9,pc01->G>>2);
	 outportb(0x3c9,pc01->B>>2);
	}
	free(pc01);

	buf=(unsigned char *)malloc(perline);
	if(buf==NULL)  /*分配动态行像素数据储存空间*/
	{
	 return 0;
	}
	
	fseek(fp,54L+4L*clrused,0);              /*将每行的像素信息都显示出来*/
	for(i=high;i>-1;i--)
	{
	 fread(buf,perline,1,fp);
	  for(j=0;j<wide;j++)
	  {
	   putpixel(x+j,i+y,buf[j]);
	   }
	}
  free(buf);
  fclose(fp);
  return 1;
 }

 /******************************************************************/

  /******************************************************************
   功能说明：画水平线函数
   参数说明：x0,y0 起始坐标   x1,y1终止坐标  thick 厚度  color 颜色
   无返回值
 *******************************************************************/
  void linelevel(int x0,int y0,int x1,int y1,int thick,int color)
  {
   int i,j,k;
   if(x0>x1)                                       /*确保x0为较小的一方*/
   {
	k=x0;
	x0=x1;
	x1=k;
   }

   if(x1<=0||x1>=1024||y1<=0||y1>=768||x1>=1024)  /*确保画线在屏幕范围之内*/
	{
		printf("the line is beyond the screen!");
		return;
	}

   for(i=0;i<thick;i++)
   {
	for(j=0;j<x1-x0;j++)
	{
		Putpixel64k(x0+j,y0+i,color);
	}
   }
 }

/**************************************************************/



/***************************************************************
   功能说明：画竖线函数
   参数说明：x0,y0 起始坐标   x1,y1终止坐标  thick 厚度  color 颜色
   无返回值
***************************************************************/
void linever(int x0,int y0,int x1,int y1,int thick,int color)
  {
	int   i = 0;
	int   j = 0;
	int   k=0;
   int high;
   high = y1 - y0;
  /* if(y0>y1)                                       确保y0为较小的一方
   {
	k=y0;
	y0=y1;
	y1=k;
   }  
   */
   if(x1<=0||x1>=1024||y1<=0||y1>=768||x1>=1024)  /*确保画线在屏幕范围之内*/
	{
		printf("the line is beyond the screen!");
		return;
	}

   for(i=0;i<thick;i++)
   {
	for(j=0;j<high;j++)
	{
		Putpixel64k(x0+i,y0+j,color);
	}
   }
 }


/**********************************************************/


/**********************************************************
Function：		Horizline

Description：	画水平线函数
可以接收超出屏幕范围的数据，只画出在屏幕内部分
因为没有防止整型变量溢出的判断，画超出屏幕的线时应防止输入特大数据

Calls：			Selectpage

Called By：		Line
Bar
Circlefill

Input：			int x					起始点横坐标，从左到右增加，0为最小值（屏幕参考系）
int y					起始点纵坐标，从上到下增加，0为最小值（屏幕参考系）
int width				水平长度，为正向右延伸，为负向左延伸
unsigned char color		颜色数，共有256种

Output：		屏幕上画出水平线

Return：		None
Others：		None
**********************************************************/
void Horizline(int x, int y, int width, int  color)
{
	/*显存指针常量，指向显存首地址，指针本身不允许修改*/
	unsigned int  far * const video_buffer = (unsigned int  far *)0xa0000000L;

	/*要切换的页面号*/
	unsigned char new_page = 0;

//	unsigned char old_page = 0;
	/*对应显存地址偏移量*/
	unsigned long int page;

	/*i是x的临时变量，后作循环变量*/
	int i;

	/*判断延伸方向，让起始点靠左*/
	if (width < 0)
	{
		x = x + width;
		width = -width;
	}

	i = x;

	/*省略超出屏幕左边部分*/
	if (x < 0)
	{
		x = 0;
		width += i;
	}

	/*整条线在屏幕外时退出*/
	if (x >= 1024)
	{
		return;
	}

	/*整条线在屏幕外时退出*/
	if (y < 0 || y >= 768)
	{
		return;
	}

	/*省略超出屏幕右边部分*/
	if (x + width > 1024)
	{
		width = 1024 - x;
	}

	/*计算显存地址偏移量和对应的页面号，做换页操作*/
	page = ((unsigned long int)y << 10) + x;
	new_page = page >> 15;
	
		SelectPage(new_page);
	


	/*向显存写入颜色，水平线画出*/
	for (i = 0; i < width; i++)
	{
		*(video_buffer + page + i) = color;
	}
}


/************************************************************
   功能说明：画水平矩形函数
   参数说明: x0,y0 左上角坐标   x1,y1右下角坐标 color 颜色
************************************************************/
void bar(int x0, int y0, int x1, int y1, int color)
{

	int i;

	int wide;                /*计算矩形的长和宽*/
	wide = x1 - x0;


	for (i = y0; i <= y1; i++)
	{
		Horizline(x0, i, wide, color);
	}
}


/**************************************************************
 功能说明：以(x,y)点为圆心，以radius为半径画圆，没有防止超出屏幕的判断，
 可以将没有超出的部分画出。
 参数说明：x,y为圆点，radius 为半径，color为颜色。
 无返回值：
 **************************************************************/
 void circle(int x0,int y0,int radius,int color)
 {
  
	int x, y, d;
	y = radius;
	d = 3 - radius << 1;
	
	for (x = 0; x <= y; x++)
	{
		Putpixel64k(x0 + x, y0 + y, color);
		Putpixel64k(x0 + x, y0 - y, color);
		Putpixel64k(x0 - x, y0 - y, color);
		Putpixel64k(x0 - x, y0 + y, color);
		Putpixel64k(x0 + y, y0 + x, color);
		Putpixel64k(x0 + y, y0 - x, color);
		Putpixel64k(x0 - y, y0 - x, color);
		Putpixel64k(x0 - y, y0 + x, color);
		
		if (d < 0)
		{
			d += x * 4 + 6;
		}
		
		else
		{
			d += (x - y) * 4 + 10;
			y--;
		}
	}
}






/**************************************************************************
      功能说明：画实心圆
      参数说明：x,y为圆心
     无返回值
**************************************************************************/
 void FillCircle(int x, int y, int r, int color)
{
	int tx = 0, ty = r, d = 3 - 2 * r, i;

	while( tx < ty)
	{
		// 画水平两点连线(<45度)
		for (i = x - ty; i <= x + ty; i++)
		{
			Putpixel64k(i, y - tx, color);
			if (tx != 0)	// 防止水平线重复绘制
				Putpixel64k(i, y + tx, color);
		}

		if (d < 0)			// 取上面的点
			d += 4 * tx + 6;
		else				// 取下面的点
		{
			// 画水平两点连线(>45度)
			for (i = x - tx; i <= x + tx; i++)
			{
				Putpixel64k(i, y - ty, color);
				Putpixel64k(i, y + ty, color);
			}

			d += 4 * (tx - ty) + 10, ty--;
		}

		tx++;
	}

	if (tx == ty)			// 画水平两点连线(=45度)
		for (i = x - ty; i <= x + ty; i++)
		{
			Putpixel64k(i, y - tx, color);
			Putpixel64k(i, y + tx, color);
		}
}


/*************************************************/


 unsigned int Getpixel64k(int x, int y)
 {
	 /*显存指针常量，指向显存首地址，指针本身不允许修改*/
	 unsigned int far * const video_buffer = (unsigned int far *)0xa0000000L;

	 /*要切换的页面号*/
	 unsigned char new_page;

	 /*对应显存地址偏移量*/
	 unsigned long int page;

	 /*判断点是否在屏幕范围内，不在就退出*/
	 if (x < 0 || x >(1024 - 1) || y < 0 || y >(768 - 1))
	 {
		 return 0;
	 }

	 /*计算显存地址偏移量和对应的页面号，做换页操作*/
	 page = ((unsigned long int)y << 10) + x;
	 new_page = page >> 15;	/*32k个点一换页，除以32k的替代算法*/
	 SelectPage(new_page);

	 /*返回颜色*/
	 return video_buffer[page];
 }

/**********************************************************************
   功能说明：读取24位图片
   参数说明：X,Y 图片位置 ，name 为路径
   返回值： 返回0为失败，1为成功
************************************************************************/ 
int Putbmp64k(int x, int y, const char * path)
{
	/*指向图片文件的文件指针*/
	FILE * fpbmp;

	/*行像素缓存指针*/
	WESHEN * buffer;

	/*图片的宽度、高度、一行像素所占字节数（含补齐空字节）*/
	long int width, height, linebytes;

	/*循环变量*/
	int i, j;

	/*图片位深*/
	unsigned int bit;

	/*压缩类型数*/
	unsigned long int compression;

	/*打开文件*/
	if ((fpbmp = fopen(path, "rb")) == NULL)
	{
		return -1;
	}

	/*读取位深*/
	fseek(fpbmp, 28L, 0);
	fread(&bit, 2, 1, fpbmp);

	/*非24位图则退出*/
	if (bit != 24U)
	{
		return -1;
	}

	/*读取压缩类型*/
	fseek(fpbmp, 30L, 0);
	fread(&compression, 4, 1, fpbmp);

	/*采用压缩算法则退出*/
	if (compression != 0UL)
	{
		return -1;
	}

	/*读取宽度、高度*/
	fseek(fpbmp, 18L, 0);
	fread(&width, 4, 1, fpbmp);
	fread(&height, 4, 1, fpbmp);


	/*计算一行像素占字节数，包括补齐的空字节*/
	linebytes = (3 * width) % 4;

	if(!linebytes)
	{
		linebytes = 3 * width;
	}
	else
	{
		linebytes = 3 * width + 4 - linebytes;
	}

	/*开辟行像素数据动态储存空间*/
	if ((buffer = (WESHEN *)malloc(linebytes)) == 0)
	{
		return -1;
	}

	/*行扫描形式读取图片数据并显示*/
	fseek(fpbmp, 54L, 0);
	for (i = height - 1; i > -1; i--)
	{
		fread(buffer, linebytes, 1, fpbmp);	/*读取一行像素数据*/

		/*一行像素的数据处理和画出*/
		for (j = 0; j < width; j++)
		{
			/*0x117模式下，原图红绿蓝各8位分别近似为5位、6位、5位*/
			buffer[j].R >>= 3;
			buffer[j].G >>= 2;
			buffer[j].B >>= 3;
			Putpixel64k(j + x, i + y,
			((((unsigned int)buffer[j].R) << 11)
			| (((unsigned int)buffer[j].G) << 5)
			| ((unsigned int)buffer[j].B)));	/*计算最终颜色，红绿蓝从高位到低位排列*/
		}
	}

	free(buffer);
	fclose(fpbmp);
	return 0;
}




int Putbmp64k00(int x, int y, const char * path)
{
	/*指向图片文件的文件指针*/
	FILE * fpbmp;

	/*行像素缓存指针*/
	WESHEN * buffer;

	/*图片的宽度、高度、一行像素所占字节数（含补齐空字节）*/
	long int width, height, linebytes;

	/*循环变量*/
	int i, j;

	/*图片位深*/
	unsigned int bit;

	/*压缩类型数*/
	unsigned long int compression;

	/*打开文件*/
	if ((fpbmp = fopen(path, "rb")) == NULL)
	{
		return -1;
	}

	/*读取位深*/
	fseek(fpbmp, 28L, 0);
	fread(&bit, 2, 1, fpbmp);

	/*非24位图则退出*/
	if (bit != 24U)
	{
		return -1;
	}

	/*读取压缩类型*/
	fseek(fpbmp, 30L, 0);
	fread(&compression, 4, 1, fpbmp);

	/*采用压缩算法则退出*/
	if (compression != 0UL)
	{
		return -1;
	}

	/*读取宽度、高度*/
	fseek(fpbmp, 18L, 0);
	fread(&width, 4, 1, fpbmp);
	fread(&height, 4, 1, fpbmp);


	/*计算一行像素占字节数，包括补齐的空字节*/
	linebytes = (3 * width) % 4;

	if(!linebytes)
	{
		linebytes = 3 * width;
	}
	else
	{
		linebytes = 3 * width + 4 - linebytes;
	}

	/*开辟行像素数据动态储存空间*/
	if ((buffer = (WESHEN *)malloc(linebytes)) == 0)
	{
		return -1;
	}

	/*行扫描形式读取图片数据并显示*/
	fseek(fpbmp, 54L, 0);
	for (i = height - 1; i > -1; i--)
	{
		fread(buffer, linebytes, 1, fpbmp);	/*读取一行像素数据*/

		/*一行像素的数据处理和画出*/
		for (j = 0; j < width; j++)
		{
			/*0x117模式下，原图红绿蓝各8位分别近似为5位、6位、5位*/
			buffer[j].R >>= 3;
			buffer[j].G >>= 2;
			buffer[j].B >>= 3;
			if(((((unsigned int)buffer[j].R) << 11)
			| (((unsigned int)buffer[j].G) << 5)
			| ((unsigned int)buffer[j].B))!=0xffff)
			{
			
			Putpixel64k(j + x, i + y,
			((((unsigned int)buffer[j].R) << 11)
			| (((unsigned int)buffer[j].G) << 5)
			| ((unsigned int)buffer[j].B)));
			}	/*计算最终颜色，红绿蓝从高位到低位排列*/
		}
	}

	free(buffer);
	fclose(fpbmp);
	return 0;
}



/**************************************************
                9月26日编写
function:       get_image

description:     得到一片区域的图像信息

Input:          x0,y0,左上角起始坐标，X1,Y2右下角坐标，save 指向存储信息的数组

out:              无输出
**************************************************************/

void    get_image(int x0,int y0,int x1,int y1,unsigned int far *save)
{
	
	int i=0;                                   /*循环变量*/
	int j=0;
	int wide=x1-x0;
    int high=y1-y0;	
	
	unsigned   int far *VideoBuffer=(unsigned int far *)0xa0000000L  ;
	
	long int newpage=0;
//    long int oldpage=0;
	
	unsigned long pos;

	for(i=0;i<high;i++)
	{
		for(j=0;j<x1-x0;j++)
		{

		   pos=((unsigned long)(y0+i)<<10)+x0+j;

		   newpage=pos>>15 ;                         /*除以32k的替代算法*/

			
			 SelectPage(newpage);
			
			save[i*wide+j]=VideoBuffer[pos];

		}
	}

}



/**************************************************
				9月26日编写
function:       put_image

description:     显示出存储空间的图像信息

Input:          x0,y0,左上角起始坐标，X1,Y2右下角坐标，save 指向存储信息的数组

out:              无输出
**************************************************************/

void    put_image(int x0,int y0,int x1,int y1,unsigned int far *save)
{

	int i=0;                                   /*循环变量*/
	int j=0;

	int wide=x1-x0;
	int high=y1-y0;

	unsigned   int far *VideoBuffer=(unsigned int far *)0xa0000000L ;

	long int newpage=0;
//	long int  oldpage=0;

	unsigned long pos;

	for(i=0;i<high;i++)
	{
		for(j=0;j<x1-x0;j++)
		{   
	        
	      pos=((unsigned long)(y0+i)<<10)+x0+j;
	
	      newpage=pos>>15 ;                         /*除以32k的替代算法*/
	
	      
			  SelectPage(newpage);
			

			VideoBuffer[pos]=save[i*wide+j];
		
		}
	}


}


/**************************************************
10月26日编写
function:       save_image

description:    显示出存储空间的图像信息

Input:          x0,y0,左上角起始坐标，X1,Y2右下角坐标,将图像信息存到文件里面

out:            
**************************************************************/
void save_image(int x0, int y0, int x1, int y1)
{
	FILE * fp;                            /*定义文件指针*/
     
	int i = 0;                                   /*循环变量*/
	int j = 0;
	int wide = x1 - x0;
	int high = y1 - y0;


	int save = 0;



	char fg[20] = "saveim";
	fp = fopen(fg, "wb");                  /*建立保存背景的文件*/
	if (fp == NULL)
	{
		printf("the file cant creat\n");
		exit(1);
	}


	for (i = 0; i<high; i++)
	{
		for (j = 0; j<wide; j++)
		{

			save = Getpixel64k(x0+j,y0+i);
			fwrite(&save,sizeof(int),1,fp);

		}
	}

	fclose(fp);

}


/**************************************************
10月26日编写
function:       printf_image

description:    从文件中读取这个背景像素

Input:          x0,y0,左上角起始坐标，X1,Y2右下角坐标,将图像信息覆盖到界面上

out:
**************************************************************/

void  printf_image(int x0, int y0, int x1, int y1)
{
	FILE * fpo;                            /*定义文件指针*/

	int i = 0;                                   /*循环变量*/
	int j = 0;
	int wide = x1 - x0;
	int high = y1 - y0;

	unsigned   int save = 0;

	char  fas[20]="saveim";
	fpo = fopen(fas, "rb");                  /*建立保存背景的文件*/
	if (fpo == NULL)
	{
		printf("the file cant creat\n");
		exit(1);
	}


	for (i = 0; i<high; i++)
	{
		for (j = 0; j<wide; j++)
		{

		 
			fread(&save,sizeof(int),1,fpo);
			Putpixel64k(x0 + j, y0 + i, save);

		}
	}

	fclose(fpo);

}


/**************************************************
10月26日编写
function:       save_image

description:    显示出存储空间的图像信息

Input:          x0,y0,左上角起始坐标，X1,Y2右下角坐标,将图像信息存到文件里面

out:            
**************************************************************/
void save_image0(int x0, int y0, int x1, int y1)
{
	FILE * fp;                            /*定义文件指针*/
     
	int i = 0;                                   /*循环变量*/
	int j = 0;
	int wide = x1 - x0;
	int high = y1 - y0;


	int save = 0;



	char fg[20] = "saveim0.dat";
	fp = fopen(fg, "wb+");                  /*建立保存背景的文件*/
	if (fp == NULL)
	{
		printf("the file cant creat\n");
		exit(1);
	}


	for (i = 0; i<high; i++)
	{
		for (j = 0; j<wide; j++)
		{

			save = Getpixel64k(x0+j,y0+i);
			fwrite(&save,sizeof(unsigned int),1,fp);

		}
	}

	fclose(fp);

}


/**************************************************
10月26日编写
function:       printf_image

description:    从文件中读取这个背景像素

Input:          x0,y0,左上角起始坐标，X1,Y2右下角坐标,将图像信息覆盖到界面上

out:
**************************************************************/

void  printf_image0(int x0, int y0, int x1, int y1)
{
	FILE * fpo;                            /*定义文件指针*/

	int i = 0;                                   /*循环变量*/
	int j = 0;
	int wide = x1 - x0;
	int high = y1 - y0;

	unsigned   int save = 0;

	char  fas[20]="saveim0.dat";
	fpo = fopen(fas, "rb+");                  /*建立保存背景的文件*/
	if (fpo == NULL)
	{
		printf("the file cant creat\n");
		exit(1);
	}


	for (i = 0; i<high; i++)
	{
		for (j = 0; j<wide; j++)
		{

		 
			fread(&save,sizeof(unsigned int),1,fpo);
			Putpixel64k(x0 + j, y0 + i, save);

		}
	}

	fclose(fpo);

}









