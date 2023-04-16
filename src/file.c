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
	FILE *fp;
	MemoBlock *p;
	if ((fp=fopen(filePath,"wb"))==NULL)
	{
	  printf("the file can not be open!");
	  getch();
	  exit(1);
	}
	p=m->head;
	if(p==NULL)
	{
		printf("error!");
		getch();
		exit(1);
	}
	else{
		fwrite(m, 1, sizeof(Memo), fp);
		while(p!=NULL)
		{
			fwrite(p, sizeof(MemoBlock), 1, fp);
			p=p->next;
		}
	}
	fflush(fp);
	fclose(fp);
}

MemoBlock *memofile_readBlock()
{
	FILE **fp=memofile_current();
	char t;
	MemoBlock *p;
	p=(MemoBlock *)malloc(sizeof(MemoBlock));
	fread(p, sizeof(MemoBlock), 1, *fp);
	if(feof(*fp)){
		free(p);
		return NULL;
	}
	return p;
 } 
 
Memo memofile_read(char *filePath)
{
	FILE **fp = memofile_current();
	Memo m;
	MemoBlock *p;
	memset(&m, 0, sizeof(m));
 	if ((*fp=fopen(filePath,"rb"))==NULL)
	{
		return m;
	}
	fread(&m, sizeof(Memo), 1, *fp);
	m.head = p = memofile_readBlock();
	while(p)
	{
		p->next = memofile_readBlock();
		p = p->next;
	}
	fclose(*fp);
	return m;
}