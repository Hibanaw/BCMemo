#ifndef _MEMO_H_
#define _MEMO_H_

typedef enum{IMAGE, PARAGRAPH, CHECKBOX} Blocktype;

typedef struct{//备忘录的信息块
    Blocktype type;
    int checkBoxisChecked;
    char *content;
}MemoBlock;

typedef struct MemoBlockNode{//备忘录块的节点
    MemoBlock content;
    MemoBlockNode *next;
}MemoBlockNode;

typedef struct{//备忘录本体，为备忘录块的链表结构，记录了头节点和总数量
    MemoBlock start;
    unsigned int count;
}Memo;

#endif