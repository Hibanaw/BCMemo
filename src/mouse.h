#ifndef _mouse_h_
#define _mouse_h_
int mouse_press(int x1, int y1, int x2, int y2);//�����???�е�����򷵻�1���ڿ���??������򷵻�2������???����??0
void mouse(int,int);//��???��??
void mouseinit(void);//��???��
//void mou_pos(int*,int*,int*);//�������λ��
void mread(int *,int *,int*);//�����겻??
void save_bk_mou(int x,int y);//����걳??
void clrmous(int x,int y);//������
void drawmous(int x,int y);//����??
void newmouse(int *nx,int *ny,int *nbuttons);   //�������

extern int MouseX;
extern int MouseY;
extern int MouseS;
extern int press;
extern union REGS regs;
#endif
