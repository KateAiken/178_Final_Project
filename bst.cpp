// Include headerfiles 
#include "bst.h"
#include "morse.h"

// Include Libraries
#include <Arduino.h>
#include <stdio.h>

// Initialize Root Node
pNode root = NULL;

pNode createBST() { // Create and allocate root node
    pNode root = (pNode)malloc(sizeof(Node));
    root->letter = -1;
    root->dot = NULL;
    root->dash = NULL;
    buildBST(root, 0);
    fillBST(root);
    return root;
}

pNode buildBST(pNode current, int depth) { // Build empty BST 
    if (depth == DEPTH) { // Add nodes until depth is reached
        return current;
    }

    pNode tempDot = (pNode)malloc(sizeof(Node));
    pNode tempDash = (pNode)malloc(sizeof(Node));

    tempDot->letter = END;
    tempDot->dot = NULL;
    tempDot->dash = NULL;

    tempDash->letter = END;
    tempDash->dot = NULL;
    tempDash->dash = NULL;

    // Recursivly add the next node to the tree 
    current->dot = buildBST(tempDot, depth + 1);
    current->dash = buildBST(tempDash, depth + 1);

    return current;
}

void addNode(int row, int depth, pNode current) { // Fill in a node in the BST
    // Recursivly call the add function to asign the letter when it reaches the end of the code
    if (translation[row][depth + 1] == WORDEND) { // Check if the morse code is at its finished length
        current->letter = translation[row][0];
    } else if (translation[row][depth + 1] == DASH) { // Check if the code is a DASH
        addNode(row, depth + 1, current->dash);
    } else if (translation[row][depth + 1] == DOT) { // Check if the code is a DOT
        addNode(row, depth + 1, current->dot);
    }
}

void fillBST(pNode root) { // Traverse translation array and call add node to add each letter to tree
    for (int row = 0; row < 26; row++) {
        addNode(row, 0, root);
    }
}

pNode letterSearch(int code[], int depth, pNode current) { // Search BST for a letter based on morse code
    // Recursivly call function to search for letter based on the inputed code
    if (code[depth] == DASH) {
        return letterSearch(code, depth + 1, current->dash);
    } else if (code[depth] == DOT) {
        return letterSearch(code, depth + 1, current->dot);
    } else {
        return current;
    }
}

int codeSearch(pNode current, int target) { // Search BST to find morse code (path to letter)
    // Recursivly call function to search for letter while pushing and popping path in stack
    if (!current)
        return 0;
    if (current->letter == target)
        return 1;
    push(DOT);
    if (codeSearch(current->dot, target))
        return 1;
    pop();
    push(DASH);
    if (codeSearch(current->dash, target))
        return 1;
    pop();
    return 0;
}