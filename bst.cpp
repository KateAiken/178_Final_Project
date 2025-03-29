#include "bst.h"
#include "morse.h"

#include <stdio.h>
#include <Arduino.h>

pNode root = NULL;

pNode createBST() {
    pNode root = (pNode)malloc(sizeof(Node));
    root->parent = NULL;
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

    tempDot->parent = current;
    tempDot->letter = END;
    tempDot->dot = NULL;
    tempDot->dash = NULL;

    tempDash->parent = current;
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

void traversal(pNode current) {
    if (current == NULL) {
        return;
    }
    traversal(current->dot);

    printf("%c\n", current->letter);
    Serial.print((char)current->letter);

    traversal(current->dash);
}

void fillBST(pNode root) {
    for (int row = 0; row < 26; row++) {
        addNode(row, 0, root);
    }
}
