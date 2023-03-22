#ifndef _MEMOS_H_
#define _MEMOS_H_
#include <stdio.h>
#include "memo.h"
typedef struct
{
    Memo *head;
    unsigned int count;
} Memos; // ���б���¼������¼������ṹ����¼��ͷ�����ܸ�����
Memos *memos();
Memo *memo_insert(Memo *p, Memo *a);
Memo *memo_delete(Memo *p);
Memo *memo_makeTop(Memo *p);
#endif
