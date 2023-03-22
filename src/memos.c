#include "memos.h"
Memos *memos()
{
	static Memos m;
	return &m;
}
Memo *memo_insert(Memo *p, Memo *a)
{
	Memo *t;
	t = p->next;
	p->next = a;
	a->next = t;
	return (a);
}
Memo *memo_delete(Memo *p)
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
Memo *memo_makeTop(Memo *p)
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
	memo_insert(h, p);
	t = p->head;
	p->head = h->head;
	h->head = t;
	a = p->id;
	p->id = h->id;
	h->id = a;
	memos()->head = p;
}
