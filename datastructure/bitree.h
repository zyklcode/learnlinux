#ifndef __BITREE_H
#define __BITREE_H

typedef int E;

enum Status{
    VALID,
    INVALID
};

typedef struct BiTNode{
    struct BiTNode *lchild;
    struct BiTNode *rchild;
    enum Status status;
    E data;
    /* data */
}BiTNode, *BiTree;

BiTree* bitree_create(void);
void bitree_destroy(BiTree *root);
void bitree_insert(BiTree *root, E val);
void bitree_delete(BiTree *root, E val);

void tree_preordertraverse(BiTree root);








#endif