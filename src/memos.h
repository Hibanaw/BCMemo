#ifndef _MEMOS_H_
#define _MEMOS_H_

#include "memo.h"

typedef struct{
    Memo content;
    MemoNode *next;
}MemoNode;//����¼�Ľڵ�

typedef struct{
    Memo *start;
    unsigned int count;
}Memos;//���б���¼������¼������ṹ����¼��ͷ�����ܸ�����


#endif