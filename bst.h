#ifndef BST_H_
#define BST_H_

#include <stdio.h>
#include <Arduino.h>

#include "morse.h"

#define DEPTH 4


typedef struct node {
    int letter;
    struct node *dash;
    struct node *dot;
    struct node *parent;
}Node, *pNode;


extern pNode root;

pNode createBST();

pNode buildBST(pNode current, int depth);

void addNode(int row, int depth,  pNode current);

void traversal(pNode current);

void fillBST(pNode root);

#endif