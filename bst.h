/*******************************************************
bst.h

header file for bst.ccp
********************************************************/

// Header file initialization 
#ifndef BST_H_
#define BST_H_

// Include Libraries
#include <stdio.h>

// Include headerfiles 
#include "morse.h"

// Global Variable Definition
#define DEPTH 4

// Define BST Node Structure
typedef struct node {
    int letter;
    struct node *dash;
    struct node *dot;
} Node, *pNode;

// Declare external node 
extern pNode root;

// Function Decleration
pNode createBST();

pNode buildBST(pNode current, int depth);

void addNode(int row, int depth, pNode current);

void fillBST(pNode root);

pNode letterSearch(int code[], int depth, pNode current);

int codeSearch(pNode current, int target);

// Close Header File
#endif