#include"listener.h"

/**
 * @brief Home����
 * 
 * @return int 1Ϊ��½��-1Ϊ�˳�
 */
int listenerHome(Mouse *m){
    //���
    newmouse(m);
    //����
    int k = listenerKey();
    //ͨ��
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
 * @brief ���ư�ť������
 * 
 * @param x ������
 * @param y ������
 * @param text �������
 * @param sizex ���
 * @param sizey �߶�
 * @return int �Ƿ񱻰��£�0Ϊ��1Ϊ��
 */
int listenerButton(Button *b, Mouse m){
    Button ob = *b, nb = *b;
    if(
        m.posX > ob.posX && m.posX < ob.posX+ob.width\
        && m.posY > ob.posY && m.posY < ob.posY+ob.height
    ){//��귶Χ�ڰ�ť��
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
 * @brief �ı����������
 * 
 * @param b �ı�������
 * @return int 1��ʾ���ӣ�-1��ʾ�˸�
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
 * @brief ���̼���
 * 
 * @return int ���µ�bioskey(0)ֵ
 */
int listenerKey(){
    int k = 0;
    if(bioskey(1)){
        k = bioskey(0);
    }
    return k;
}