/**
 * @file mouse.c
 * @author dengshuumin, Hibanaw Hu (hibanaw@qq.com)
 * @brief Mouse under DOS with no global variables.
 * @date 2023-02-26
 * @version 5.1
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "mouse.h"

/**
 * @brief Mouse "object".
 * 
 * @return Mouse* 
 */
Mouse *mouse(){
	static Mouse m;
	return &m;
}

/**
 * @brief Mouse init.
 * 
 */
void mouse_init()
{
	int retcode;
	int xmin,xmax,ymin,ymax,x_max=MAXWIDTH,y_max=MAXHEIGHT;
	union REGS regs;
	Mouse *m = mouse();
	int size=imagesize(0,0,12,19);
	m -> buffer=malloc(size);
	xmin=2;
	xmax=x_max-1;
	ymin=3;
	ymax=y_max-2;
	regs.x.ax=0;
	int86(51,&regs,&regs);
	retcode=regs.x.ax;
	if(retcode==0)
	{
		printf("Mouse or Mouse Driver Obsent,Please Install!");
		delay(5000);
	}
	else
	{
		regs.x.ax=7;
		regs.x.cx=xmin;
		regs.x.dx=xmax;
		int86(51,&regs,&regs);
		regs.x.ax=8;
		regs.x.cx=ymin;
		regs.x.dx=ymax;
		int86(51,&regs,&regs);
	}
	m->style = 0;
	m->posX=xmax/2;
	m->posY=ymax/2;
	m->_flag=1;
	_mouse_saveBackground(m->posX,m->posY);
}

/**
 * @brief Update mouse "object".
 * 
 */
void mouse_update()
{
	int xn,yn,buttonsn;
	Mouse *m = mouse();
	int x0=m->posX,y0=m->posY,buttons0=m->click;
	_mouse_read(&xn,&yn,&buttonsn);
	m->posX = xn;
	m->posY = yn;
	m->click = buttonsn;
	if(xn == x0 && yn == y0 && buttonsn == buttons0)
		return;
	_mouse_clrmous(x0,y0);
	_mouse_saveBackground(xn, yn);
	_mouse_drawmous(xn, yn);
	
}

void mouse_show(){
	Mouse *m = mouse();
	int x = m->posX, y = m->posY;
	_mouse_saveBackground(x, y);
	_mouse_drawmous(x, y);
}
void mouse_hide(){
	Mouse *m = mouse();
	int x = m->posX, y = m->posY;
	_mouse_clrmous(x, y);
}

/**
 * @brief Whether mouse is clicked in box.
 * 
 * @param x1 
 * @param y1 
 * @param x2 
 * @param y2 
 * @return int 1 if clicked in box; 2 if in box but not clicked; 0 if not in box.
 */
int mouse_isClickedInBox(int x1, int y1, int x2, int y2)
{
	int MouseX = mouse()->posX;
	int MouseY = mouse()->posY;
	int press = mouse()->click;
	//�ڿ��е�����򷵻�?1
	if(MouseX > x1 
	&&MouseX < x2
	&&MouseY > y1
	&&MouseY < y2
	&&press == 1)
	{
		return 1;
	}
	
	//�ڿ���δ������򷵻�?2
	else if(MouseX > x1 
	&&MouseX < x2
	&&MouseY > y1
	&&MouseY < y2
	&&press == 0)
	{
		return 2;
	}
	
	//�ڿ��е���Ҽ����򷵻�?3
	else if(MouseX > x1 
	&&MouseX < x2
	&&MouseY > y1
	&&MouseY < y2
	&&press == 2)
	{
		return 3;
	}
	else if(press){
		return -1;
	}
	else
	{
		
		return 0;
	}
}

/**
 * @brief Draw mouse at x, y.
 * 
 * @param x Position x.
 * @param y Position Y.
 * 
 * @private
 */
void _mouse_draw(int x,int y)
{
	switch(mouse()->style)
	{
		case 1:                                  //�������?
		{
            setcolor(_WHITE);
            setlinestyle(0,0,1);
            line(x-1,y+9,x-1,y+8);
            line(x,y+7,x,y+11);
            line(x+1,y+6,x+1,y+13);
            line(x+2,y+8,x+2,y+14);
            line(x+3,y-1,x+3,y+15);
            arc(x+4,y-1,0,180,1);
            line(x+4,y-2,x+4,y+15);
            line(x+5,y-1,x+5,y+16);
            arc(x+6,y+3,0,180,1);
            line(x+6,y+2,x+6,y+16);
            line(x+7,y+3,x+7,y+17);
            arc(x+8,y+5,0,180,1);
            line(x+8,y+4,x+8,y+17);
            line(x+9,y+5,x+9,y+16);
            arc(x+10,y+7,0,180,1);
            line(x+10,y+6,x+10,y+16);
            line(x+11,y+7,x+11,y+13);

            setcolor(_DARKGRAY);
            line(x-1,y+9,x-1,y+8);
            line(x-1,y+8,x+1,y+6);
            line(x+1,y+6,x+3,y+10);
            line(x+3,y+10,x+3,y-1);
            arc(x+4,y-1,0,180,1);
            line(x+5,y-1,x+5,y+5);
            arc(x+6,y+3,0,180,1);
            line(x+7,y+3,x+7,y+7);
            arc(x+8,y+5,0,180,1);
            line(x+9,y+5,x+9,y+9);
            arc(x+10,y+7,0,180,1);
            line(x+11,y+7,x+11,y+13);
            arc(x+7,y+13,-90,0,4);
            line(x+7,y+17,x+3,y+15);
            line(x+3,y+15,x+1,y+13);
            line(x+1,y+13,x-1,y+9);
		}
			break;
		case 2:                        //���?
		{
			setcolor(_DARKGRAY);
			setlinestyle(0,0,1);
			line(x+1,y-1,x+9,y-1);
			line(x+1,y+15,x+9,y+15);
			line(x+5,y-1,x+5,y+15);
		}
			break;
		case 3:                        //ʮ��
		{
			setcolor(_WHITE);
			setlinestyle(0,0,1);
			line(x-1,y+7,x+11,y+7);
			line(x+5,y-1,x+5,y+15);
		}
			break;
		default:              //Ĭ�����?
		{
			setlinestyle(0,0,1);
			setcolor(_WHITE);
			line(x,y,x,y+13);
			line(x+1,y+1,x+1,y+12);
			line(x+2,y+2,x+2,y+11);
			line(x+3,y+3,x+3,y+10);
			line(x+4,y+4,x+4,y+12);
			line(x+5,y+5,x+5,y+9);
			line(x+5,y+11,x+5,y+14);
			line(x+6,y+6,x+6,y+9);
			line(x+6,y+13,x+6,y+15);
			line(x+7,y+7,x+7,y+9);
			line(x+8,y+8,x+8,y+9);
			line(x+9,y+9,x+9,y+9);
			setcolor(_DARKGRAY);
			line(x-1,y-1,x-1,y+14);
			line(x-1,y+14,x+3,y+11);
			line(x+3,y+11,x+3,y+12);
			line(x+3,y+12,x+4,y+13);
			line(x+4,y+13,x+4,y+14);
			line(x+4,y+14,x+7,y+17);
			line(x+7,y+17,x+7,y+13);
			line(x+7,y+13,x+6,y+12);
			line(x+6,y+12,x+6,y+11);
			line(x+6,y+11,x+5,y+10);
			line(x+5,y+10,x+11,y+10);
			line(x+11,y+10,x-1,y-2);
		}
		break;
	}
}


/**
 * @brief Read mouse status though DOS interruption.
 * 
 * @param nx Mouse position x.
 * @param ny Mouse position y.
 * @param nbuttons Mouse button status.
 * 
 * @private
 */
void _mouse_read(int *nx,int *ny,int *nbuttons)
{
	union REGS regs;
	regs.x.ax=3;
	int86(51,&regs,&regs);
	*nx = regs.x.cx;
	*ny = regs.x.dx;
	*nbuttons = regs.x.bx;
}

/**
 * @brief Save mouse background.
 * 
 * @param nx Position x.
 * @param ny Position Y.
 * 
 * @private
 */
void _mouse_saveBackground(int nx,int ny)
{
	void *buffer = mouse()->buffer;
	getimage(nx-1,ny-2,MIN(nx+11, MAXWIDTH-1),MIN(ny+17, MAXHEIGHT-1),buffer);
}

/**
 * @brief Clear mouse.
 * 
 * @param nx 
 * @param ny 
 * 
 */
void _mouse_clrmous(int nx, int ny)//������
{
	Mouse *m = mouse();
	if(m->_flag==1)
	{
		setwritemode(XOR_PUT); 
		_mouse_draw(nx,ny);
		putimage(nx-1,ny-2,m->buffer,COPY_PUT);
		m->_flag=0;
		setwritemode(COPY_PUT);
	}
}

/**
 * @brief Draw mouse.
 * 
 * @param nx 
 * @param ny 
 * 
 */
void _mouse_drawmous(int nx, int ny)
{
	Mouse *m = mouse();
	if(m->_flag==0)
	{
		setwritemode(COPY_PUT);
	    _mouse_draw(nx,ny);
		m->_flag=1;
	}
}


