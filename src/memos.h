#ifndef _MEMOS_H_
#define _MEMOS_H_

#include "memo.h"

typedef struct MemoNode{//����¼�Ľڵ�
    Memo content;
    MemoNode *next;
}MemoNode;

typedef struct{//���б���¼������¼������ṹ����¼��ͷ�����ܸ�����
    Memo *start;
    unsigned int count;
}Memos;


#endif