#ifndef _MEMO_H_
#define _MEMO_H_

typedef enum{IMAGE, PARAGRAPH, CHECKBOX} Blocktype;

typedef struct{
    Blocktype type;
    int checkBoxisChecked;
    char *content;
}MemoBlock;//����¼����Ϣ��

typedef struct{
    MemoBlock content;
    MemoBlockNode *next;
}MemoBlockNode;//����¼��Ľڵ�

typedef struct{
    MemoBlock start;
    unsigned int count;
}Memo;//����¼���壬Ϊ����¼�������ṹ����¼��ͷ�ڵ��������

#endif