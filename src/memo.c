#include "memo.h"

Memo *memo()
{
	static Memo m;
	return &m;
}

MemoBlock *memoBlock_add(MemoBlock *a)
{
	MemoBlock *h = memo()->head;
	if (h == NULL)
	{
		h = a;
	}
	else
	{
		MemoBlock *p = h;
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = a;
		a->next = NULL;
	}
}

MemoBlock *memoBlock_insert(MemoBlock *p, MemoBlock *a)
{
	MemoBlock *q, *t;
	t = p->next;
	p->next = a;
	a->next = t;
	return (a);
}
// �ڵ�һ��������λ��֮�������Node����node�������ǵڶ������������ز����node�ĵ�ַ��
MemoBlock *memoBlock_delete(MemoBlock *p)
{
	MemoBlock *head = memo()->head;
	MemoBlock *q;
	q = head;
	while (q != NULL && (q->next) != p)
	{
		q = q->next;
	}
	q->next = q->next->next;
	free(p);
	return (q->next);
}
// ɾ���������ڵĽڵ㣬���ظýڵ��next��

MemoBlock *memoBlock_new(Memotype type, int checkBoxisChecked, char *content)
{
	MemoBlock *q, *t;
	q = (MemoBlock *)malloc(sizeof(MemoBlock));
	if (q == NULL)
	{
		printf("no enough memory");
		exit(1);
	}
	else
	{
		q->type = type;
		q->checkBoxisChecked = checkBoxisChecked;
		strcpy(q->content, content);
	}
	return (q);
}