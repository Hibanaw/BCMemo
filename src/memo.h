/**
 * @file memo.h
 * @author wywgwt (2504133124@qq.com)
 * @brief 
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _MEMO_H_
#define _MEMO_H_

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    PARAGRAPH,
    IMAGE,
    CHECKBOX
} Memotype;

typedef struct MemoBlock
{
    Memotype type;
    int checkBoxisChecked;
    char content[310];
    struct MemoBlock *next;
    char lastEditUser[20];
} MemoBlock; // 备忘录的信息块

typedef struct Memo
{
    MemoBlock *head;
    struct Memo *next;
    int id;
} Memo; // 备忘录的节点

Memo *memo();

void *memo_addBlock(MemoBlock *a);

MemoBlock *memo_insertBlock(MemoBlock *p, MemoBlock *a);

// 在第一个参数的位置之后插入新Node，新node的内容是第二个参数，返回插入的node的地址。
MemoBlock *memo_deleteBlock(MemoBlock *p);

// 删除参数所在的节点，返回该节点的next。

MemoBlock *memo_newBlock(Memotype type, int checkBoxisChecked, char *content);

MemoBlock *memo_preBlock(MemoBlock *p);

int memo_getBlockSum();

int memo_getBlockNum(MemoBlock *mb);
#endif
