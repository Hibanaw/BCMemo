/**
 * @file file.h
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
FILE **memofile_current();

void memofile_write(char* filePath, Memo *m);

void memofile_writeBlock(MemoBlock *p);

void memofile_readBlock(MemoBlock *p);

 void memofile_read(Memo *m,char *filePath);
 
#endif
