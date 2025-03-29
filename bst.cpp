#include "bst.h"
#include "morse.h"

#include <Arduino.h>
#include <stdio.h>

pNode root = NULL;

pNode createBST() {
    pNode root = (pNode)malloc(sizeof(Node));
    root->letter = -1;
    root->dot = NULL;
    root->dash = NULL;
    buildBST(root, 0);
    fillBST(root);
    return root;
}

pNode buildBST(pNode current, int depth) {
    if (depth == DEPTH) {
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

    current->dot = buildBST(tempDot, depth + 1);
    current->dash = buildBST(tempDash, depth + 1);

    return current;
}

void addNode(int row, int depth, pNode current) {
    if (translation[row][depth + 1] == WORDEND) {
        current->letter = translation[row][0];
    } else if (translation[row][depth + 1] == DASH) {
        addNode(row, depth + 1, current->dash);
    } else if (translation[row][depth + 1] == DOT) {
        addNode(row, depth + 1, current->dot);
    }
}

void fillBST(pNode root) {
    for (int row = 0; row < 26; row++) {
        addNode(row, 0, root);
    }
}

pNode letterSearch(int code[], int depth, pNode current) {
    if (code[depth] == DASH) {
        return letterSearch(code, depth + 1, current->dash);
    } else if (code[depth] == DOT) {
        return letterSearch(code, depth + 1, current->dot);
    } else {
        return current;
    }
}

int codeSearch(pNode current, int target) {
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