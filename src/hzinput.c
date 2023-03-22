#include "hzinput.h"

/************************************************************************
FUNCTION:hz_input
DESCRIPTION: �������뷨
INPUT:x1,x2,y1,y2,s(input string),len(string's maxlength),color(input box background color),color2(font color),size(font size)
RETURN:���ָ���len
IMPROVE:ֻ������Сд��ĸ,��������ֻ�Ӣ��
************************************************************************/

int hz_input(int x1,int y1,int x2,int y2,char *s,int len,int color,int color2, int size)
{
	int i;
	int flag=0;
	int ST=-1;//���뷨���ط�ʽ��1.��SPACE���������뺺�� 2.��ENTER����������Ӣ�� 3.�˸�����ز�����
	char *image;
	char *p=s+len;
	int value=0;
	int asc;
	int xx1=x1+2,xx2=x2-2;//��ֹ�������
	int L_maxwords=(xx2-xx1)/(size/2),maxline=(y2-y1)/30;
	int Line=len/L_maxwords+1,L_len=len%L_maxwords,pylen;    //��ǰ��������Line����0�п�ʼ������ ���г��� L_len  pylenƴ������ //�п�30����
	int barx1,barx2,bary1,bary2;
	char str[3]={'\0','\0','\0'};//һ������װ��
	char py[12]={'\0','\0','\0','\0','\0','\0','\0','\0',
	            '\0','\0','\0','\0'};//ƴ���ַ���(�����ַ���)
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	mouse_hide();
	// setfillstyle(SOLID_FILL, color);
	// bar(x1,y1,x2,y2);
	while(bioskey(1))//������̻�����  ��ֹ������
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
			/*���������*/
		    switch(value)
			{
				case KEYBACKSPACE:
					if((L_len==0)&&(Line>1))//���д���
					{
						L_len=L_maxwords;
						Line--;
					}
					else if(L_len<=0&&Line==1) break;//ɾ������ �޷�ɾ��
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
					return len;	//��������
			}
			/*���뺺�����뷨*/
			asc=value&0xff;
			if(asc>=97&&asc<=122)
			{
				barx1=(x1+L_len*8-50>0)?(x1+L_len*8-50):0;       //�������뷨λ��  �����������Ͻ��Ҳ������Ļ
	    		barx2=(barx1+200<630)?(barx1+200):(barx1=430,630);
				bary1=y1+Line*30+10;
				bary2=(bary1+40<480)?(bary1+40):(bary1=y1+Line*30-80,bary1+40);
				getimage(barx1,bary1,barx2,bary2,image);
				pyFrm(barx1,bary1,barx2,bary2);
				setfillstyle(1,color);
				ST=input_method(barx1,bary1,str,value,py);
				switch(ST)
				{
					case 1://�����ּ���ո���˳����뷨  ���뺺��
					    if(strlen(str))//�����ַ�������Ϊ��
						{
							if((L_len+5)>=L_maxwords&&Line<maxline)//��������
							{
								/*�ÿո��������λ����ת����һ��*/
								if(L_len+1==L_maxwords)
								{
									*p=' ';
									p++;
									len++;
								}
								Line++;
								L_len=0;
							}
							else if((L_len+1>=L_maxwords&&Line==maxline)||Line>maxline)//�޷�����
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
					case 2://�ɻس����˳����뷨 ���������ģ�
						pylen=strlen(py);
					    if((L_len+pylen>L_maxwords&&Line==maxline)||(Line>maxline))//λ������
						{
							putimage(barx1,bary1,image,0);
							break;
						}
						else if(L_len+pylen>L_maxwords&&Line<maxline)//�������� ����
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
					case 3://����ɾ��Ϊ0�Զ��˳����뷨  ������
						putimage(barx1,bary1,image,0);
					    break;
				}
				value=0;
				ST=-1;
			}
			else if(asc>31&&asc<127)//�ַ�����
			{
				continue;
				/*py[0]=asc;
				if(L_len+1<=L_maxwords&&Line<=maxline)//��������
				{
					*p=asc;
				}
				else if(Line+1<=maxline)//��������
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
DESCRIPTION: �������뷨����
INPUT:x,y,str,value,py
RETURN:1:������֣�2�������ĸ��3������ո�
************************************************************************/

int input_method(int x,int y,char *str,int value,char *py)
{
	FILE *fp=NULL,*oldfp=NULL;
	int fJudge=FAIL;
	char *p=py;
	int trigger=1;//����ʱ���������־
	char temphz[5][3]={{'\0','\0','\0'},{'\0','\0','\0'},
	                   {'\0','\0','\0'},{'\0','\0','\0'},
					   {'\0','\0','\0'}},temp[3];
	int fposition=0;
	int hznow=0,hznum=0;
	int asc,i;
	int PyStartx=x+8,PyStarty=y+4;
	int HzStartx=x+8,HzStarty=y+22;
	char *ABpath="pinyin\\";//����ƴ��������׼·��
	char pypath[45];					//����ƴ���������·��
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	strcpy(pypath,"pinyin\\");
	while(1)
	{
		if(trigger||kbhit())//��һ�ν����Զ����� �Ժ�������
		{
			mouse_hide();
			trigger=0;
			if(kbhit()) value=bioskey(0);
			asc=value&0xff;
			/*���ⰴ������*/
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
					if(fposition>=8)//�������ض�λ�ļ�ָ��ǰ�˸��ֽڣ��ĸ����֣�
					{
						fposition-=8;
					}
					break;
				case KEYDOWN:
					if(!feof(fp))//�������ض�λ�ļ�ָ���˸��ֽڣ��ĸ����֣�
					{
						fposition+=8;
					}
					break;
				case KEYLEFT://���ƶ�һ��
					if(hznow)
					{
						hznow--;
					}
					else if(fposition>=8)//��Ҫ��ҳ
					{
						fposition-=8;
						hznow=3;
					}
					break;
				case KEYRIGHT:
					if(hznow<hznum-1)//ͬ��
					{
						hznow++;
					}
					else if(!feof(fp))
					{
						fposition+=8;
						hznow=0;
					}
					break;
					/*�����ּ�ѡ�����뺺��*/
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
			/*�����ַ�����*/
			if(asc>31&&asc<127&&strlen(py)<=6&&asc!='['&&asc!=']')    //��Ч����ʱ��λ
			{
				*p=asc;
				p++;
				fposition=0;
				hznow=0;
			}
			pyFrm(x,y,x+200,y+40);
			setfillstyle(1,WHITE);
			settextstyle(1,0,2);
			outtextxy(PyStartx,PyStarty,py);        //ƴ������
		    strcat(pypath,py);
		    strcat(pypath,".txt");
		    if(fJudge) //����ǰ�ļ�ָ�뱣�� ͬʱ�ر���һ���ļ�  Ϊ���������ַ�׼��
			{
				if(oldfp)
				{
					fclose(oldfp);
				}
				oldfp=fp;
			}
		    if((fp=fopen(pypath,"r"))==NULL)//�����ַ�����  ������һ���ļ��������
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
		    		fread(temphz[i],2,1,fp);//����һ������
		    		if(feof(fp))//�����ļ�β
		    		{
		    			hznum=i;//������˴��ļ�β���һ�� ��Ҫ��һ  Ȼ���˴�����һ��Ч������
		    			break;
					}
				}
				if(!feof(fp))//δ�����ļ�β ȫ�Ժ���
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
				hz_puthzold(HzStartx+hznow*50+16,HzStarty,temphz[hznow],16,16,CYAN);//��ʾѡ�к���
			}
		}
		strcpy(pypath,ABpath);          //����·����ԭ�������٣�
		value=0;
	}
}

/************************************************************************
FUNCTION:itostr
DESCRIPTION: ���ֱ��
INPUT:a,s
RETURN:����s
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
DESCRIPTION: ���뷨С��
INPUT:x1,y1,x2,y2
RETURN:��
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
DESCRIPTION: �ַ����뷨
INPUT:x,y,s,color
RETURN:�ַ�����len
************************************************************************/

int xouttextxy(int x,int y,char *s,int color)//8x16�����ֿ�
{
	FILE *asc=NULL;
	int i,j,k;
	char *mat,*temp;
	int len;
	long offset;
	int mask;

	len=strlen(s);
	if(!len) return 0;//���ַ�����ִ�в���
	if((asc=fopen("ETC\\HZK\\ASC16","rb"))==NULL)
	{
		closegraph();
		printf("outtextxy can't open asc16!,xouttextxy");
		delay(3000);
		exit(1);
	}
	if((mat=(char *)malloc(16*sizeof(char)*len))==NULL)//��ŵ���
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
		offset=(long)16*s[i];//�����ַ����ļ�ƫ��
		fseek(asc,offset,SEEK_SET);
		fread(temp,sizeof(char),16,asc);//�������ַ��������mat
		temp+=16;
	}
	fclose(asc);
	for(i=0;i<len;i++)//ͨ���ŵ���ʾ�ַ�
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