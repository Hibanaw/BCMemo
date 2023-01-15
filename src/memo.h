#ifndef _MEMO_H_
#define _MEMO_H_

typedef enum{IMAGE, PARAGRAPH, CHECKBOX} Blocktype;

typedef struct{//����¼����Ϣ��
    Blocktype type;
    int checkBoxisChecked;
    char *content;
}MemoBlock;

typedef struct MemoBlockNode{//����¼��Ľڵ�
    MemoBlock content;
    MemoBlockNode *next;
}MemoBlockNode;

typedef struct{//����¼���壬Ϊ����¼�������ṹ����¼��ͷ�ڵ��������
    MemoBlock start;
    unsigned int count;
}Memo;

#endif