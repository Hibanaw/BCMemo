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
} MemoBlock; // ����¼����Ϣ��

typedef struct Memo
{
    MemoBlock *head;
    struct Memo *next;
    int id;
} Memo; // ����¼�Ľڵ�

Memo *memo();

void *memo_addBlock(MemoBlock *a);

MemoBlock *memo_insertBlock(MemoBlock *p, MemoBlock *a);

// �ڵ�һ��������λ��֮�������Node����node�������ǵڶ������������ز����node�ĵ�ַ��
MemoBlock *memo_deleteBlock(MemoBlock *p);

// ɾ���������ڵĽڵ㣬���ظýڵ��next��

MemoBlock *memo_newBlock(Memotype type, int checkBoxisChecked, char *content);

MemoBlock *memo_preBlock(MemoBlock *p);

int memo_getBlockSum();

int memo_getBlockNum(MemoBlock *mb);
#endif
