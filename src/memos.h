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
Memo *memos_insertMemo(Memo *p, Memo *a);
Memo *memos_deleteMemo(Memo *p);
Memo *memos_makeTopMemo(Memo *p);
#endif
