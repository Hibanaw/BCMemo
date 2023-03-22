#ifndef _MEMO_H_
#define _MEMO_H_

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    IMAGE,
    PARAGRAPH,
    CHECKBOX
} Memotype;

typedef struct MemoBlock
{
    Memotype type;
    int checkBoxisChecked;
    char content[500];
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

MemoBlock *memoBlock_add(MemoBlock *a);

MemoBlock *memoBlock_insert(MemoBlock *p, MemoBlock *a);

// 在第一个参数的位置之后插入新Node，新node的内容是第二个参数，返回插入的node的地址。
MemoBlock *memoBlock_delete(MemoBlock *p);

// 删除参数所在的节点，返回该节点的next。

MemoBlock *memoBlock_new(Memotype type, int checkBoxisChecked, char *content);

#endif
