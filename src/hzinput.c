#include "hzinput.h"

/************************************************************************
FUNCTION:hzinput
DESCRIPTION: 汉字输入法
INPUT:x1,x2,y1,y2,s(input string),len(string's maxlength),color(input box background color),color2(font color),size(font size)
RETURN:汉字个数len
IMPROVE:只能输入小写字母,可输出汉字或英文
************************************************************************/

int hzinput(int x,int y, char *s)
{
	int i;
	int flag=0;
	int ST=-1;//输入法返回方式：1.安SPACE键返回输入汉字 2.按ENTER键返回输入英文 3.退格键返回不输入
	char *image;
	int value=0;
	int asc;
	int barx1,barx2,bary1,bary2;
	char str[3]={'\0','\0','\0'};//一个汉字装入
	char py[12]={'\0','\0','\0','\0','\0','\0','\0','\0',
	            '\0','\0','\0','\0'};//拼音字符串(西文字符串)s
	int color = _WHITE, color2 = _BLACK;
	int size = 16;
	int return_value = 0;
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	mouse_hide();
	while(bioskey(1))//清除键盘缓冲区  防止误输入
	{
		bioskey(0);
	}
	if((image=malloc(8241))==NULL)
	{
		closegraph();
		printf("error!,hzinput");
		getch();
		exit(1);
	}
	if(kbhit())
	{
		value=bioskey(0);

		/*进入汉字输入法*/
		asc=value&0xff;
		if(asc>=97&&asc<=122)
		{
			barx1=x;       //计算输入法位置  离所输入距离较近且不溢出屏幕
			barx2=x+200;
			bary1=y;
			bary2=y+40;
			getimage(barx1,bary1,barx2,bary2,image);
			pyFrm(barx1,bary1,barx2,bary2);
			setfillstyle(1,color);
			ST=input_method(barx1,bary1,str,value,py);
			switch(ST)
			{
				case 1://由数字键或空格键退出输入法  输入汉字
					strcpy(s, str);
					return_value = 2;
					break;
				case 2://由回车键退出输入法 （键入西文）
					strcpy(s, py);
					return_value = strlen(py);
					break;
				case 3://西文删除为0自动退出输入法  不输入
					return_value = 0;
					break;
			}
		}
		putimage(barx1,bary1,image,0);
	}
	return return_value;
}

/************************************************************************
FUNCTION:input_method
DESCRIPTION: 汉字输入法调入
INPUT:x,y,str,value,py
RETURN:1:输出汉字；2：输出字母；3：输出空格
************************************************************************/

int input_method(int x,int y,char *str,int value,char *py)
{
	FILE *fp=NULL,*oldfp=NULL;
	int fJudge=FAIL;
	char *p=py;
	int trigger=1;//进入时触发输入标志
	char temphz[5][3]={{'\0','\0','\0'},{'\0','\0','\0'},
	                   {'\0','\0','\0'},{'\0','\0','\0'},
					   {'\0','\0','\0'}},temp[3];
	int fposition=0;
	int hznow=0,hznum=0;
	int asc,i;
	int PyStartx=x+8,PyStarty=y+4;
	int HzStartx=x+8,HzStarty=y+22;
	char *ABpath="etc\\pinyin\\";//汉语拼音检索标准路径
	char pypath[45];					//汉语拼音检索相对路径
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	strcpy(pypath,"etc\\pinyin\\");
	while(1)
	{
		if(trigger||kbhit())//第一次进入自动触发 以后均需键盘
		{
			mouse_hide();
			trigger=0;
			if(kbhit()) value=bioskey(0);
			asc=value&0xff;
			/*特殊按键处理*/
			switch(value)
			{
				case KEYBACKSPACE:
					p--;
					*p='\0';
					if(py[0]=='\0')
					{
						if(oldfp) fclose(oldfp);
						if(fp) fclose(fp);
						return 3;
					}
					break;
				case KEYSPACE:
					strcpy(str,temphz[hznow]);
					if(oldfp) fclose(oldfp);
					if(fp) fclose(fp);
					return 1;
				case KEYENTER:
					if(oldfp) fclose(oldfp);
					if(fp) fclose(fp);
					return 2;
				case KEYUP:
					if(fposition>=8)//接下来重定位文件指针前八个字节（四个汉字）
					{
						fposition-=8;
					}
					break;
				case KEYDOWN:
					if(!feof(fp))//接下来重定位文件指针后八个字节（四个汉字）
					{
						fposition+=8;
					}
					break;
				case KEYLEFT://左移动一个
					if(hznow)
					{
						hznow--;
					}
					else if(fposition>=8)//需要左换页
					{
						fposition-=8;
						hznow=3;
					}
					break;
				case KEYRIGHT:
					if(hznow<hznum-1)//同左
					{
						hznow++;
					}
					else if(!feof(fp))
					{
						fposition+=8;
						hznow=0;
					}
					break;
					/*按数字键选中输入汉字*/
				case KEYONE:
					strcpy(str,temphz[0]);
					if(oldfp) fclose(oldfp);
					if(fp) fclose(fp);
					return 1;
				case KEYTWO:
					strcpy(str,temphz[1]);
					if(oldfp) fclose(oldfp);
					if(fp) fclose(fp);
					return 1;
				case KEYTHREE:
					strcpy(str,temphz[2]);
					if(oldfp) fclose(oldfp);
					if(fp) fclose(fp);
					return 1;
				case KEYFOUR:
					strcpy(str,temphz[3]);
					if(oldfp) fclose(oldfp);
					if(fp) fclose(fp);
					return 1;
			}
			/*输入字符处理*/
			if(asc>31&&asc<127&&strlen(py)<=6&&asc!='['&&asc!=']')    //有效输入时则复位
			{
				*p=asc;
				p++;
				fposition=0;
				hznow=0;
			}
			pyFrm(x,y,x+200,y+40);
			setfillstyle(1,WHITE);
			settextstyle(1,0,2);
			outtextxy(PyStartx,PyStarty,py);        //拼音字体
		    strcat(pypath,py);
		    strcat(pypath,".txt");
		    if(fJudge) //将当前文件指针保存 同时关闭上一个文件  为输入特殊字符准备
			{
				if(oldfp)
				{
					fclose(oldfp);
				}
				oldfp=fp;
			}
		    if((fp=fopen(pypath,"r"))==NULL)//特殊字符存在  保留上一个文件检索结果
		    {
		    	fJudge=FAIL;
		    	fp=oldfp;
			}
			else
			{
				fJudge=SUCCESS;
			}
			if(fp)
			{
				fseek(fp,fposition,SEEK_SET);
		  		for(i=0;i<5;i++)
		    	{
		    		fread(temphz[i],2,1,fp);//读入一个汉字
		    		if(feof(fp))//读到文件尾
		    		{
		    			hznum=i;//按道理此处文件尾多读一次 需要减一  然而此处不减一的效果更好
		    			break;
					}
				}
				if(!feof(fp))//未读到文件尾 全显汉字
				{
					hznum=4;
				}
				for(i=0;i<hznum;i++)
				{
					setcolor(BLUE);
                    settextstyle(1,0,2);
		   		    xouttextxy(HzStartx+i*50,HzStarty+5,itostr(i+1,temp),DARKGRAY);
    				hz_puthzold(HzStartx+i*50+16,HzStarty,temphz[i],16,16,DARKGRAY);
				}
				hz_puthzold(HzStartx+hznow*50+16,HzStarty,temphz[hznow],16,16,CYAN);//显示选中汉字
			}
		}
		strcpy(pypath,ABpath);          //绝对路径复原（不可少）
		value=0;
	}
}

/************************************************************************
FUNCTION:itostr
DESCRIPTION: 数字标号
INPUT:a,s
RETURN:数字s
************************************************************************/

char *itostr(int a,char *s)
{
	switch(a)
	{
		case 1:
			strcpy(s,"1.");
			return s;
		case 2:
			strcpy(s,"2.");
			return s;
		case 3:
			strcpy(s,"3.");
			return s;
		case 4:
			strcpy(s,"4.");
			return s;
	}
	return s;
}

/************************************************************************
FUNCTION:pyFrm
DESCRIPTION: 输入法小框
INPUT:x1,y1,x2,y2
RETURN:无
************************************************************************/

void pyFrm(int x1,int y1,int x2,int y2)
{
	setfillstyle(1,_WHITE);
	bar(x1,y1,x2,y2);
	setcolor(BLUE);
	setlinestyle(0,0,1);
	line(x1+5,y1+20,x2-5,y1+20);
	setcolor(_DARKGRAY);
	rectangle(x1,y1,x2,y2);
}

/************************************************************************
FUNCTION:xouttextxy
DESCRIPTION: 字符输入法
INPUT:x,y,s,color
RETURN:字符长度len
************************************************************************/

int xouttextxy(int x,int y,char *s,int color)//8x16点阵字库
{
	Text t;
	t.content = s;
	t.posX = x,
	t.posY = y,
	t.font.fontSize = 24;
	t.font.fontColor = color;
	t.font.spacing = 2;
	t.font.rowSpacing = 2;
	text_display(t);
}