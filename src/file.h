/**
 * @file file.h
 * @author wywgwt (2504133124@qq.com)
 * @brief 
 * @date 2023-04-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __FILE_H__
#define __FILE_H__
#include<stdio.h>
#include<string.h>
#include"memos.h" 
#include"memo.h"

FILE **memofile_current();

void memofile_write(char* filePath, Memo *m);

void memofile_writeBlock(MemoBlock *p);

MemoBlock *memofile_readBlock();

Memo memofile_read(char *filePath);
 
#endif
