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

int listenerLogin(Textbox *bu, Textbox *bp, Mouse *m){
    newmouse(m);
	int k = listenerKey();
    if(isESCAPE(k)){
        return -1;
    }
    int s = listenerButton(100, 100, *m);
    if(s = 1){
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
int listenerButton(int x, int y, Mouse m, char* text, int width, int height){
	
	
	return 0;
}

/**
 * @brief �ı����������
 * 
 * @param b �ı�������
 * @return int 1��ʾ���ӣ�-1��ʾ�˸�
 */
int listenerTextbox(Textbox *b){
    int k;
    char c;
    k = listenerKey();
	if(k == BACKSPACEKEY){
        return -1;
    }
    c = bk2ascii(k);
    if(c >= 'a' && c <='z' || c >= 'A' && c <= 'Z'){
        char *s = b->str;
        int l = strlen(s);
        s[l] = c;
        s[l+1] = 0;
        return 1;
    }
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