#include "bst.h"
#include "morse.h"

pNode root;

// before call
// root->parent = NULL;
// root->letter = -1;
// pNode tempDot = (pNode)malloc(sizeof(Node));
// pNode tempDash = (pNode)malloc(sizeof(Node));

pNode buildBST(pNode root, int depth) {
    if (depth != 4) {
        pNode tempDot = (pNode)malloc(sizeof(Node));
        pNode tempDash = (pNode)malloc(sizeof(Node));

        tempDot->parent = root;
        tempDot->dot = buildBST(tempDot, depth+1);
        tempDot->dash = buildBST(tempDot, depth+1);
        tempDash->parent = root;
        tempDash->dash = buildBST(tempDash, depth+1);
        tempDash->dot = buildBST(tempDash, depth+1);
    }
    else{
        return root;
    }
}

void fillBST(){
    for(int i; i < 26; i++){
        
    }
}
