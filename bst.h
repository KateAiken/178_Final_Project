#ifndef BST_H_
#define BST_H_

#include "morse.h"

#define DEPTH 4


typedef struct node {
    int letter;
    struct node *dot;
    struct node *dash;
    struct node *parent;
}Node, *pNode;


extern pNode root;

pNode buildBST(pNode root, int depth);

void fillBST();

#endif