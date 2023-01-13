/*
 * @Author: Hibanaw Hu hibanaw@qq.com
 * @Date: 2023-01-12 10:04:13
 * @LastEditors: Hibanaw Hu hibanaw@qq.com
 * @LastEditTime: 2023-01-12 13:31:19
 * @FilePath: \memo\src\memos.h
 * @Description: 
 * 
 * Copyright (c) 2023 by Hibanaw Hu hibanaw@qq.com, All Rights Reserved. 
 */
#ifndef _MEMOS_H_
#define _MEMOS_H_

#include "memo.h"

typedef struct MemoNode{//����¼�Ľڵ�
    Memo content;
    MemoNode *next;
}MemoNode;

typedef struct{//���б���¼������¼������ṹ����¼��ͷ�����ܸ�����
    Memo *start;
    unsigned int count;
}Memos;


#endif