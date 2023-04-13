/**
 * @file memo.c
 * @author wywgwt (2504133124@qq.com), Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "memo.h"

Memo *memo()
{
	static Memo m;
	return &m;
}

void *memo_addBlock(MemoBlock *a)
{
	MemoBlock *h = memo()->head;
	if (h == NULL)
	{
		memo()->head = a;
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

MemoBlock *memo_insertBlock(MemoBlock *p, MemoBlock *a)
{
	MemoBlock *q, *t;
	t = p->next;
	p->next = a;
	a->next = t;
	return (a);
}
// �ڵ�һ��������λ��֮�������Node����node�������ǵڶ������������ز����node�ĵ�ַ��
MemoBlock *memo_deleteBlock(MemoBlock *p)
{
	MemoBlock *head = memo()->head;
	MemoBlock *q;
	q = head;
	if(q == p){
		memo()->head = p->next;
		free(p);
		return (q->next);
	}
	while (q != NULL && (q->next) != p)
	{
		q = q->next;
	}
	q->next = p->next;
	free(p);
	return (q->next);
}
// ɾ���������ڵĽڵ㣬���ظýڵ��next��

MemoBlock *memo_newBlock(Memotype type, int checkBoxisChecked, char *content)
{
	MemoBlock *q, *t;
	q = (MemoBlock *)malloc(sizeof(MemoBlock));
	if (q == NULL)
	{
		printf("no enough memory");
		delay(5000);
		exit(1);
	}
	else
	{
		memset(q, 0, sizeof(MemoBlock));
		q->type = type;
		q->checkBoxisChecked = checkBoxisChecked;
		strcpy(q->content, content);
	}
	return q;
}
//�½�

MemoBlock *memo_preBlock(MemoBlock *p)
{
	MemoBlock *head = memo()->head;
	MemoBlock *q = head;
	while((q->next!=NULL)&&(q->next)!=p)
	{
		q=q->next;
	}
	return(q);
}

int memo_getBlockSum(){
	int s = 0;
	MemoBlock *p = memo()->head;
	while(p != NULL){
		p = p->next;
		s++;
	}
	return s;
}

int memo_getBlockNum(MemoBlock *mb){
	int s = 0;
	MemoBlock *p = memo()->head;
	while(p != NULL && p != mb){
		p = p->next;
		s++;
	}
	return s;
}