#include"listener.h"

/**
 * @brief Home监听
 * 
 * @return int 1为登陆，-1为退出
 */
int listenerHome(Mouse *m){
    //鼠标
    newmouse(m);
    //键盘
    int k = listenerKey();
    //通信
	if(m->click || k && !isESCAPE(k)) return 1;
	if(isESCAPE(k)) return -1;
    return 0;
}

int listenerLogin(Textbox *bu, Textbox *bp, Button *b, Mouse *m){
    newmouse(m);
	int k = listenerKey();
    if(isESCAPE(k)){
        return -1;
    }
    int s = listenerButton(b, *m);
	if(s == 1){
        return 1;
    }
    return 0;
}


/**
 * @brief 绘制按钮并互动
 * 
 * @param x 横坐标
 * @param y 纵坐标
 * @param text 填充内容
 * @param sizex 宽度
 * @param sizey 高度
 * @return int 是否被按下，0为否1为真
 */
int listenerButton(Button *b, Mouse m){
    Button ob = *b, nb = *b;
    if(
        m.posX > ob.posX && m.posX < ob.posX+ob.width\
        && m.posY > ob.posY && m.posY < ob.posY+ob.height
    ){//鼠标范围在按钮上
        if(m.click){
            nb.status = 2;
        }
        else{
            if(m.release){
                return 1;
            }
            else{
                nb.status = 0;
            }
        }
    }
    if(ob.status != nb.status){
        drawButton(nb);
        *b = nb;
    }
	return 0;
}

/**
 * @brief 文本栏输入监听
 * 
 * @param b 文本栏内容
 * @return int 1表示增加，-1表示退格
 */
int listenerTextbox(Textbox *b){
    long lf = b->flickerChangeTime;
    long nt = clock() * 10 / CLK_TCK;
    if(nt - lf > 6){
        b->flicker != b->flicker;
        b->flickerChangeTime = nt;
    }
    int k;
    char c;
    k = listenerKey();
	if(k == BACKSPACEKEY){
        return -1;
    }
    c = bk2ascii(k);
    if(c >= 'a' && c <='z' || c >= 'A' && c <= 'Z'){
        char *s = b->text;
        int l = strlen(s);
        s[l] = c;
        s[l+1] = 0;
        return 1;
    }
    char rstr[101];
    strcpy(rstr, b->text);
    if(b->flicker){
        strcat(rstr, "|");
    }
    outtext(b->posX, b->posY, b->text);
    return 0;
}

/**
 * @brief 键盘监听
 * 
 * @return int 按下的bioskey(0)值
 */
int listenerKey(){
    int k = 0;
    if(bioskey(1)){
        k = bioskey(0);
    }
    return k;
}