#include"event.h"

/**
 * @brief Home����
 * 
 * @return int 1Ϊ��½��-1Ϊ�˳�
 */
int homeEvent(Mouse *m){
    //���
    mread(&m->posX, &m->posY, &m->click);
    //����
    int k = keyEvent();
    //ͨ��
	if(m->click || k && !isESCAPE(k)) return 1;
	if(isESCAPE(k)) return -1;
    return 0;
}

int loginEvent(Textbox *bu, Textbox *bp, Button *b, Mouse *m){
    newmouse(m);
	int k = keyEvent();
    if(isESCAPE(k)){
        return -1;
    }
	int s = buttonEvent(b, *m);
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
int buttonEvent(Button *b, Mouse *m){
    Button ob = *b, nb = *b;
    if(
        m->posX > ob.posX && m->posX < ob.posX+ob.width\
        && m->posY > ob.posY && m->posY < ob.posY+ob.height
    ){
        if(m->click){
            nb.status = 2;
        }
        else{
            if(m->release){
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


int textboxEvent(Textbox *b, Mouse *m){
    if(
        m->posX > b->posX && m->posX < b->posX+b->width\
        && m->posY > b->posY && m->posY < b->posY+b->height
    ){
        m->style = TEXTMOUSE;
    }
    char lt[101];
    char *t = b->text;
    strcpy(lt, t);
    int len = strlen(t);
    int color = _GRAY;
    if(b->isFocused){
        long lf = b->flickerChangeTime;
        long nt = 1 * 10 / CLK_TCK;
        if(nt - lf > 6){
            b->flicker = !b->flicker;
            b->flickerChangeTime = nt;
        }
        int k;
        char c;
        k = keyEvent();
        if(k == BACKSPACEKEY){
            if(t[len-1] < 128u){//ascii alphabet
                t[len-1] = 0;
            }
            else{//gb2312 chinese character
                t[len-1] = t[len-2] = 0;
            }
        }
        c = bk2ascii(k);
        if(c >= 'a' && c <='z' || c >= 'A' && c <= 'Z'){
            t[len] = c;
            t[len+1] = 0;
            return 1;
        }
        
        if(b->flicker){
            strcat(t, "|");
        }
        setcolor(_BLACK);
        if(strcmp(lt, t))
            putimage(b->posX, b->posY, b->buffer, COPY_PUT);
            settextjustify(LEFT_TEXT,TOP_TEXT);          //�󲿶��룬��������
			settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
	        outtextxy(b->posX, b->posY, b->text);
    }
    
    return 0;
}

/**
 * @brief �����¼�
 * 
 * @return int ���µ�bioskey(0)ֵ
 */
int keyEvent(){
    int k = 0;
    if(bioskey(1)){
        k = bioskey(0);
    }
    return k;
}