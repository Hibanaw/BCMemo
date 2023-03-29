#include "hzinput.h"

/************************************************************************
FUNCTION:hzinput
DESCRIPTION: �������뷨
INPUT:x1,x2,y1,y2,s(input string),len(string's maxlength),color(input box background color),color2(font color),size(font size)
RETURN:���ָ���len
IMPROVE:ֻ������Сд��ĸ,��������ֻ�Ӣ��
************************************************************************/

int hzinput(int x,int y, char *s)
{
	int i;
	int flag=0;
	int ST=-1;//���뷨���ط�ʽ��1.��SPACE���������뺺�� 2.��ENTER����������Ӣ�� 3.�˸�����ز�����
	char *image;
	int value=0;
	int asc;
	int barx1,barx2,bary1,bary2;
	char str[3]={'\0','\0','\0'};//һ������װ��
	char py[12]={'\0','\0','\0','\0','\0','\0','\0','\0',
	            '\0','\0','\0','\0'};//ƴ���ַ���(�����ַ���)s
	int color = _WHITE, color2 = _BLACK;
	int size = 16;
	int return_value = 0;
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	mouse_hide();
	while(bioskey(1))//������̻�����  ��ֹ������
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

		/*���뺺�����뷨*/
		asc=value&0xff;
		if(asc>=97&&asc<=122)
		{
			barx1=x;       //�������뷨λ��  �����������Ͻ��Ҳ������Ļ
			barx2=x+200;
			bary1=y;
			bary2=y+40;
			getimage(barx1,bary1,barx2,bary2,image);
			pyFrm(barx1,bary1,barx2,bary2);
			setfillstyle(1,color);
			ST=input_method(barx1,bary1,str,value,py);
			switch(ST)
			{
				case 1://�����ּ���ո���˳����뷨  ���뺺��
					strcpy(s, str);
					return_value = 2;
					break;
				case 2://�ɻس����˳����뷨 ���������ģ�
					strcpy(s, py);
					return_value = strlen(py);
					break;
				case 3://����ɾ��Ϊ0�Զ��˳����뷨  ������
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
	char *ABpath="etc\\pinyin\\";//����ƴ��������׼·��
	char pypath[45];					//����ƴ���������·��
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	strcpy(pypath,"etc\\pinyin\\");
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
DESCRIPTION: �ַ����뷨
INPUT:x,y,s,color
RETURN:�ַ�����len
************************************************************************/

int xouttextxy(int x,int y,char *s,int color)//8x16�����ֿ�
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