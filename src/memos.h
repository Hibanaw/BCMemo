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
Memo *memos_insertMemo(Memo *p, Memo *a);
Memo *memos_deleteMemo(Memo *p);
Memo *memos_makeTopMemo(Memo *p);
#endif
