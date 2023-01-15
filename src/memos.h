#ifndef _MEMOS_H_
#define _MEMOS_H_

#include "memo.h"

typedef struct MemoNode{//备忘录的节点
    Memo content;
    MemoNode *next;
}MemoNode;

typedef struct{//所有备忘录，备忘录的链表结构，记录了头结点和总个数。
    Memo *start;
    unsigned int count;
}Memos;


#endif