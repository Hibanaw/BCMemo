#ifndef _MEMOS_H_
#define _MEMOS_H_
#include <stdio.h>
#include "memo.h"
typedef struct
{
    Memo *head;
    unsigned int count;
} Memos; // 所有备忘录，备忘录的链表结构，记录了头结点和总个数。
Memos *memos();
Memo *memo_insert(Memo *p, Memo *a);
Memo *memo_delete(Memo *p);
Memo *memo_makeTop(Memo *p);
#endif
