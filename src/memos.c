#include "memos.h"
Memos *memos()
{
	static Memos m;
	return &m;
}
Memo *memos_insertMemo(Memo *p, Memo *a)
{
	Memo *t;
	t = p->next;
	p->next = a;
	a->next = t;
	return (a);
}
Memo *memos_deleteMemo(Memo *p)
{
	Memo *h = memos()->head;
	Memo *q = h;
	while (q != NULL && (q->next) != p)
	{
		q = q->next;
	}
	q->next = q->next->next;
	free(p);
	return (q->next);
}
Memo *memos_makeTopMemo(Memo *p)
{
	MemoBlock *t;
	int a;
	Memo *h = memos()->head;
	Memo *q;
	q = h;
	//	h = p;
	//	h->next = q;
	while (q != NULL && (q->next) != p)
	{
		q = q->next;
	}
	q->next = q->next->next;
	q = h;
	memos_insertMemo(h, p);
	t = p->head;
	p->head = h->head;
	h->head = t;
	a = p->id;
	p->id = h->id;
	h->id = a;
	memos()->head = p;
}
