#ifndef _mouse_h_
#define _mouse_h_
int mouse_press(int x1, int y1, int x2, int y2);//如果在框中点击，则返回1；在框中未点击，则返回2；不在框中则返回0
void mouse(int,int);//设计鼠标
void mouseinit(void);//初始化
//void mou_pos(int*,int*,int*);//更改鼠标位置
void mread(int *,int *,int*);//改坐标不画
void save_bk_mou(int x,int y);//存鼠标背景
void clrmous(int x,int y);//清除鼠标
void drawmous(int x,int y);//画鼠标
void newmouse(int *nx,int *ny,int *nbuttons);   //更新鼠标

extern int MouseX;
extern int MouseY;
extern int MouseS;
extern int press;
extern union REGS regs;
#endif
