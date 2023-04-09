/**
 * @file file.c
 * @author wywgwt (2504133124@qq.com), Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "file.h"

FILE **memofile_current(){
	static FILE *f;
	return &f;
}

void memofile_write(char* filePath, Memo *m){
	FILE **fp = memofile_current();
	MemoBlock *h=m->head;
	MemoBlock *p;
	if ((*fp=fopen(filePath,"wb"))==NULL)
	{
	  printf("the file can not be open!");
	  getch();
	  exit(1);
	}
	p=h;
	if(h==NULL)
	{
		printf("error!");
		getch();
		exit(1);
	}
	else{
		while(p!=NULL)
		{
			memofile_writeBlock(p);
			p=p->next;
		}
	}
	fclose(*fp);
}

void memofile_writeBlock(MemoBlock *p)
{
	FILE *fp = *memofile_current();
	fwrite(p, sizeof(MemoBlock), 1, fp);
}
MemoBlock *memofile_readBlock()
{
	FILE *fp=*memofile_current();
	char t;
	MemoBlock *p;
	if(feof(fp)){
		return NULL;
	}
	p=(MemoBlock *)malloc(sizeof(MemoBlock));
	fread(p, sizeof(MemoBlock), 1, fp);
	return p;
 } 
 
Memo memofile_read(char *filePath)
{
	FILE **fp = memofile_current();
	Memo m;
	MemoBlock *p;

 	if ((*fp=fopen(filePath,"rb"))==NULL)
	{
		*fp = fopen(filePath, "wb");
		fclose(fp);
		*fp=fopen(filePath,"rb");
	}
	m.head = p = memofile_readBlock();
	while(p)
	{
		p->next = memofile_readBlock();
		p = p->next;
	}
	fclose(*fp);
	return m;
}