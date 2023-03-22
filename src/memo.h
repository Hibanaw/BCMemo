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
} MemoBlock; // ����¼����Ϣ��

typedef struct Memo
{
    MemoBlock *head;
    struct Memo *next;
    int id;
} Memo; // ����¼�Ľڵ�

Memo *memo();

MemoBlock *memoBlock_add(MemoBlock *a);

MemoBlock *memoBlock_insert(MemoBlock *p, MemoBlock *a);

// �ڵ�һ��������λ��֮�������Node����node�������ǵڶ������������ز����node�ĵ�ַ��
MemoBlock *memoBlock_delete(MemoBlock *p);

// ɾ���������ڵĽڵ㣬���ظýڵ��next��

MemoBlock *memoBlock_new(Memotype type, int checkBoxisChecked, char *content);

#endif
