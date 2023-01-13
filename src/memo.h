/*
 * @Author: Hibanaw Hu hibanaw@qq.com
 * @Date: 2023-01-12 10:14:00
 * @LastEditors: Hibanaw Hu hibanaw@qq.com
 * @LastEditTime: 2023-01-12 14:03:21
 * @FilePath: \memo\src\memo.h
 * @Description: 
 * 
 * Copyright (c) 2023 by Hibanaw Hu hibanaw@qq.com, All Rights Reserved. 
 */
#ifndef _MEMO_H_
#define _MEMO_H_

typedef enum{IMAGE, PARAGRAPH, CHECKBOX} Blocktype;

typedef struct{//����¼����Ϣ��
    Blocktype type;
    int checkBoxisChecked;
    char *content;
}MemoBlock;

typedef struct MemoBlockNode{//����¼��Ľڵ�
    MemoBlock content;
    MemoBlockNode *next;
}MemoBlockNode;

typedef struct{//����¼���壬Ϊ����¼�������ṹ����¼��ͷ�ڵ��������
    MemoBlock start;
    unsigned int count;
}Memo;

#endif