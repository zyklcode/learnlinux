#include "bitree.h"
#include <stdio.h>
#include <stdlib.h>

BiTree* bitree_create(void){
    return NULL;
}
void bitree_destroy(BiTree *root){
    if(root && *root){
        bitree_destroy(&((*root)->lchild));
        bitree_destroy(&((*root)->rchild));
        bitree_destroy(*root);
        root = NULL;
    }
}
void bitree_insert(BiTree *root, E val){
    if(*root){
        if((*root)->data == val){
            return;
        }else if((*root)->data > val){
            bitree_insert(&((*root)->lchild), val);
            return;
        }else{
            bitree_insert(&((*root)->rchild), val);
            return;
        }
    }
    *root = (BiTNode *)malloc(sizeof(BiTNode));
    (*root)->data = val;
    (*root)->status = VALID;
    (*root)->lchild = NULL;
    (*root)->rchild = NULL;
    return;
}



// 0:删除成功
// -1: 没有删除，原因是没有该数据
int bitree_delete(BiTree *root, E val){
    if(*root){
        if((*root)->data == val){
            (*root)->status = INVALID;
            return 0;
        }else if((*root)->data > val){
            return bitree_delete(&((*root)->lchild), val);
        }else{
            return bitree_delete(&((*root)->rchild), val);
        }
    }
    return -1;
}

void tree_displaybitnode(const BiTNode *node){
    printf("%d ", node->data);
}

void tree_preordertraverse(BiTree root){
    if(root){
        displayBiTNode(root);
        tree_preordertraverse(root->lchild);
        tree_preordertraverse(root->rchild);
    }
}

void tree_inordertraverse(BiTree root){
    if(root){
        tree_preordertraverse(root->lchild);
        displayBiTNode(root);
        tree_preordertraverse(root->rchild);
    }
}

void tree_inordertraverse(BiTree root){
    if(root){
        tree_preordertraverse(root->lchild);
        tree_preordertraverse(root->rchild);
        displayBiTNode(root);
    }
}

