/**
 * @file mfile.c
 * @author wywgwt (2504133124@qq.com), Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "memos.h"
Memos *memos()
{
	static Memos m;
	return &m;
}

void *memos_add(Memo *a){
	Memo *h = memos()->head;
	if (h == NULL)
	{
		memos()->head = a;
	}
	else
	{
		Memo *p = h;
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = a;
		a->next = NULL;
	}
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
	memos()->head = p;
}

void memos_reset(){
	Memos *m = memos();
	Memo *p = m->head;
	while(p->next!=NULL){
		Memo *pn = p->next->next;
		free(p->next);
		p->next = pn;
	}
	memset(m, 0, sizeof(Memos));
	return;
}

Memos *memos_getList(char *uid){
	Memos *ms = memos();
	struct ffblk ffblk;
	int done;
	memos_reset();
	// 查找第一个匹配的文件
	done = findfirst("data\\*.mem", &ffblk, 0);
	while (!done)
	{
		FILE *fp;
		Memo *m = malloc(sizeof(Memo));
		char path[100];
		char name[10];
		char *dot = strchr(ffblk.ff_name, '.');	
		strncpy(name, ffblk.ff_name, dot - ffblk.ff_name);
		name[dot - ffblk.ff_name] = '\0';
		sprintf(path, "data\\%s",ffblk.ff_name);
		if(auth_check(name, uid) == 1){
			fp = fopen(path, "rb");
			if(fp == NULL) continue;
			fread(m, sizeof(Memo), 1, fp);
			fclose(fp);
			strcpy(m->fileName, name);
			memos_add(m);
		}
		done = findnext(&ffblk);
	}

	return ms;
}
Memo *memos_preMemo(Memo *p){
	Memo *head = memos()->head;
	Memo *q = head;
	while((q->next!=NULL)&&(q->next)!=p)
	{
		q=q->next;
	}
	return(q);
}
int memos_getSum(){
	int s = 0;
	Memo *p = memos()->head;
	while(p != NULL){
		p = p->next;
		s++;
	}
	return s;
}

int memos_getNum(Memo *mb){
	int s = 0;
	Memo *p = memos()->head;
	while(p != NULL && p != mb){
		p = p->next;
		s++;
	}
	return s;
}