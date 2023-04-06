/**
 * @file file.c
 * @author wywgwt (2504133124@qq.com)
 * @brief 
 * @date 2023-04-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _WRITE_H_
#define _WRITE_H_
#include<stdio.h>
#include<string.h>
#include"memos.h" 
#include"memo.h"
FILE **memofile_current(){
	static FILE *f;
	return &f;
}

void memofile_write(char* filePath, Memo *m){
	FILE **fp = memofile_current();
	if ((*fp=fopen(filePath,"w"))==NULL)
	{
	  printf("the file can not be open!");
	  getch();
	  exit(1);
	}
	MemoBlock *h=m->head;
	MemoBlock *p;
	p=h;
	if(h==NULL)
	{
		printf("error!");
		getch();
		exit(1);
	}
	else{
		while((p->next)!=NULL)
		{
			memofile_writeBlock(p);
			p=p->next;
		}
	}
	fclose(*fp);
}

void memofile_writeBlock(MemoBlock *p)
{
	FILE **fp = memofile_current();
	if(p->type==IMAGE)
	{
		fprintf(*fp,"%s %c %s\n",p->lastEditUser,'I',p->content);
	}
	if(p->type==PARAGRAPH)
	{
		fprintf(*fp, "%s %c %s\n",p->lastEditUser,'p',p->content);
	}
	if(p->content==CHECKBOX)
	{
		fputc('C',*fp);
		fprintf(*fp,"%d",p->checkBoxisChecked);
		fprintf(*fp,"%s %c %d %s\n",p->lastEditUser,'C',p->checkBoxChecked,p->content);
	}
}
void memofile_readBlock(MemoBlock *p)
{
	FILE **fp=memofile_current();
	if(feof(*fp)) return;
	p=(MemoBlock *)malloc(sizeof(MemoBlock)); 
	char t = fgetc(*fp);
	switch(t)
	{
	case 'I':
		fscanf(*fp,"%s %c ",&(p->lastEditUser), &(p->type));
		fgets(p->content,500,*fp);
		break;
	case 'P':
		p->type=PARAGRAPH;
		fgets(p->content,500,*fp);
		fscanf(*fp,"%s %c",&(p->lastEditUser),&(p->type));
		fgets(p->content,500,*fp);
		break;
	case 'C':
		fscanf(*fp,"%s %c %d",&(p->lastEditUser),&(p->checkBoxisChecked),&(p->type));
		fgets(p->content,500,*fp);
		break;
	default:
	break;
    }
 } 
 
 void memofile_read(Memo *m,char *filePath)
 {
 	FILE **fp=memofile_current();
 	if ((*fp=fopen(filePath,"r"))==NULL)
	{
	  printf("the file can not be open!");
	  getch();
	  exit(1);
	  
	}
	MemoBlock *h=m->head;
	MemoBlock *p=h;
	while(1)
	{
		if(p==NULL)
		{ 
			break;
		}
		else
		{
			memofile_readBlock(p);
			p=p->next;
		}
	}
	fclose(*fp);
 }
#endif
