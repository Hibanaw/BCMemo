#ifndef _MEMOS_H_
#define _MEMOS_H_

#include "memo.h"

typedef struct{
    Memo content;
    MemoNode *next;
}MemoNode;//备忘录的节点

typedef struct{
    Memo *start;
    unsigned int count;
}Memos;//所有备忘录，备忘录的链表结构，记录了头结点和总个数。


#endif