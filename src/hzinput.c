#include "hzinput.h"

/************************************************************************
FUNCTION:hz_input
DESCRIPTION: 汉字输入法
INPUT:x1,x2,y1,y2,s(input string),len(string's maxlength),color(input box background color),color2(font color),size(font size)
RETURN:汉字个数len
IMPROVE:只能输入小写字母,可输出汉字或英文
************************************************************************/

int hz_input(int x1,int y1,int x2,int y2,char *s,int len,int color,int color2, int size)
{
	int i;
	int flag=0;
	int ST=-1;//输入法返回方式：1.安SPACE键返回输入汉字 2.按ENTER键返回输入英文 3.退格键返回不输入
	char *image;
	char *p=s+len;
	int value=0;
	int asc;
	int xx1=x1+2,xx2=x2-2;//防止输入溢出
	int L_maxwords=(xx2-xx1)/(size/2),maxline=(y2-y1)/30;
	int Line=len/L_maxwords+1,L_len=len%L_maxwords,pylen;    //当前所在行数Line（按0行开始计数） 该行长度 L_len  pylen拼音长度 //行宽30像素
	int barx1,barx2,bary1,bary2;
	char str[3]={'\0','\0','\0'};//一个汉字装入
	char py[12]={'\0','\0','\0','\0','\0','\0','\0','\0',
	            '\0','\0','\0','\0'};//拼音字符串(西文字符串)
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	mouse_hide();
	// setfillstyle(SOLID_FILL, color);
	// bar(x1,y1,x2,y2);
	while(bioskey(1))//清除键盘缓冲区  防止误输入
	{
		bioskey(0);
	}
	if((image=malloc(8241))==NULL)
	{
		closegraph();
		printf("error!,hz_input");
		getch();
		exit(1);
	}
	while(1)
	{
		if(kbhit())
		{
			value=bioskey(0);
			/*特殊键处理*/
		    switch(value)
			{
				case KEYBACKSPACE:
					if((L_len==0)&&(Line>1))//换行处理
					{
						L_len=L_maxwords;
						Line--;
					}
					else if(L_len<=0&&Line==1) break;//删除结束 无法删除
					if(*(p-1)>31&&*(p-1)<127)
					{
						setfillstyle(1,color);
						bar(xx1+L_len*8-8,y1+Line*30-30,xx1+L_len*8,y1+Line*30);
						p--;
						*p='\0';
						len--;
						L_len--;
					}
					else
					{
						setfillstyle(1,color);
						bar(xx1+L_len*(size/2+1)-size-2,y1+Line*30-30,xx1+L_len*(size/2+1)-1,y1+Line*30);
						p-=2;
						p[0]='\0';
						p[1]='\0';
						len-=2;
						L_len-=2;
					}
					break;
				case KEYENTER:
					*p='\0';
					free(image);
					if (len == 0)
					{
						setfillstyle(SOLID_FILL, color);
	                    bar(x1-1,y1,x2,y2);
					}
					return len;	//结束输入
			}
			/*进入汉字输入法*/
			asc=value&0xff;
			if(asc>=97&&asc<=122)
			{
				barx1=(x1+L_len*8-50>0)?(x1+L_len*8-50):0;       //计算输入法位置  离所输入距离较近且不溢出屏幕
	    		barx2=(barx1+200<630)?(barx1+200):(barx1=430,630);
				bary1=y1+Line*30+10;
				bary2=(bary1+40<480)?(bary1+40):(bary1=y1+Line*30-80,bary1+40);
				getimage(barx1,bary1,barx2,bary2,image);
				pyFrm(barx1,bary1,barx2,bary2);
				setfillstyle(1,color);
				ST=input_method(barx1,bary1,str,value,py);
				switch(ST)
				{
					case 1://由数字键或空格键退出输入法  输入汉字
					    if(strlen(str))//返回字符串可能为空
						{
							if((L_len+5)>=L_maxwords&&Line<maxline)//换行输入
							{
								/*用空格来填补不足位，跳转到下一行*/
								if(L_len+1==L_maxwords)
								{
									*p=' ';
									p++;
									len++;
								}
								Line++;
								L_len=0;
							}
							else if((L_len+1>=L_maxwords&&Line==maxline)||Line>maxline)//无法输入
							{
								putimage(barx1,bary1,image,0);
								break;
							}
							strcpy(p,str);
							if (flag == 0)
							{
								flag = 1;
							}
							hz_puthzold(xx1+L_len*(size/2+1),y1+Line*30-30,str,size,size+2,color2);
							p+=2;
					    	len+=2;
							L_len+=2;
						}
						putimage(barx1,bary1,image,0);
					    break;
					case 2://由回车键退出输入法 （键入西文）
						pylen=strlen(py);
					    if((L_len+pylen>L_maxwords&&Line==maxline)||(Line>maxline))//位置已满
						{
							putimage(barx1,bary1,image,0);
							break;
						}
						else if(L_len+pylen>L_maxwords&&Line<maxline)//该行已满 换行
						{
							for(i=0;i<L_maxwords-L_len;i++)
							{
								p[i]=' ';
							}
							p+=L_maxwords-L_len;
							len+=L_maxwords-L_len;
							Line++;
							L_len=0;
						}
						putimage(barx1,bary1,image,0);
						setcolor(DARKGRAY);
						xouttextxy(xx1+L_len*8,y1+Line*30-28,py,DARKGRAY);
						strcpy(p,py);
						len+=pylen;
						p+=pylen;
						L_len+=pylen;
					    break;
					case 3://西文删除为0自动退出输入法  不输入
						putimage(barx1,bary1,image,0);
					    break;
				}
				value=0;
				ST=-1;
			}
			else if(asc>31&&asc<127)//字符输入
			{
				continue;
				/*py[0]=asc;
				if(L_len+1<=L_maxwords&&Line<=maxline)//正常输入
				{
					*p=asc;
				}
				else if(Line+1<=maxline)//换行输入
				{
					*p=' ';
					Line++;
					L_len=0;
				}
				else
				{
					continue;
				}
				p++;
				len++;
				setcolor(DARKGRAY);
				xouttextxy(xx1+L_len*8,y1+Line*30-21,py,DARKGRAY);
				L_len++;*/
			}
			memset(py,'\0',12);
			memset(str,'\0',3);
		}
		if((mouse()->posX<x1||mouse()->posX>x2||mouse()->posY<y1||mouse()->posY>y2)&&mouse()->click)
		{
			*p='\0';
			free(image);
			return len;
		}
	}
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
	char *ABpath="pinyin\\";//汉语拼音检索标准路径
	char pypath[45];					//汉语拼音检索相对路径
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	strcpy(pypath,"pinyin\\");
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
	setfillstyle(1,WHITE);
	bar(x1,y1,x2,y2);
	setcolor(BLUE);
	setlinestyle(0,0,1);
	line(x1+5,y1+20,x2-5,y1+20);
	setcolor(DARKGRAY);
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
	FILE *asc=NULL;
	int i,j,k;
	char *mat,*temp;
	int len;
	long offset;
	int mask;

	len=strlen(s);
	if(!len) return 0;//空字符串不执行操作
	if((asc=fopen("ETC\\HZK\\ASC16","rb"))==NULL)
	{
		closegraph();
		printf("outtextxy can't open asc16!,xouttextxy");
		delay(3000);
		exit(1);
	}
	if((mat=(char *)malloc(16*sizeof(char)*len))==NULL)//存放点阵
	{
		closegraph();
		printf("Failed!,xouttextxy");
		fclose(asc);
		getch();
		exit(1);
	}
	temp=mat;
	for(i=0;i<len;i++)
	{
		offset=(long)16*s[i];//计算字符的文件偏移
		fseek(asc,offset,SEEK_SET);
		fread(temp,sizeof(char),16,asc);//将所有字符点阵存入mat
		temp+=16;
	}
	fclose(asc);
	for(i=0;i<len;i++)//通过放点显示字符
	{
		for(j=0;j<16;j++)
		{
			mask=0x80;
			for(k=0;k<8;k++)
			{
				if(mat[i*16+j]&mask)
				putpixel(x+8*i+k,y+j,color);
				mask>>=1;
			}
		}
	}
	free(mat);
	return len;
}