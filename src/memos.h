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
void *memos_add(Memo *a);
Memo *memos_insertMemo(Memo *p, Memo *a);
Memo *memos_deleteMemo(Memo *p);
Memo *memos_makeTopMemo(Memo *p);
void memos_reset();
Memos *memos_getList(char *uid);

Memo *memos_preMemo(Memo *p);
int memos_getSum();
int memos_getNum(Memo *mb);

#include "auth.h"
#include <dir.h>
#endif
