#ifndef _MEMO_H_
#define _MEMO_H_

typedef enum{IMAGE, PARAGRAPH, CHECKBOX} Blocktype;

typedef struct{
    Blocktype type;
    int checkBoxisChecked;
    char *content;
}MemoBlock;//备忘录的信息块

typedef struct{
    MemoBlock content;
    MemoBlockNode *next;
}MemoBlockNode;//备忘录块的节点

typedef struct{
    MemoBlock start;
    unsigned int count;
}Memo;//备忘录本体，为备忘录块的链表结构，记录了头节点和总数量

#endif