#ifndef MORSE_H_
#define MORSE_H_ 

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <Arduino.h>


#include "queue.h"
#include "bst.h"

#define DASH 45
#define DOT 46
#define SPACE 32
#define END 0
#define WORDEND 48
#define NEWLINE 10
#define ARR_SIZE 25

struct queue;
struct node;
typedef node* pNode;

typedef struct stack{
    int top;
    int stack[4];
} *Stack;

extern int translation[26][6];

void getTextTerminal(char text[]);

void toNum(char sentance[], queue *queue);

void translate(char word[], int num[]);

pNode letterSearch(int code[], int depth, pNode current);

void print(char arrChar[], int arrInt[], int length);

void toMorse(char code[] , char word[], int received[]);

int codeSearch(pNode current, int target);

void push(int value);

int pop();

#endif

// void toMorse(char code[], char word[], int received[]) {
//     for (int i = 0; i < ARR_SIZE && received[i] != -1; i++) {
//         if (received[i] != END) {
//             word[i] = (char)received[i];
//         }
//     }
//     int pos = 0;
//     for (int i = 0; i < ARR_SIZE && received[i] != -1; i++) {
//         if (received[i] == SPACE) {
//             code[pos++] = SPACE;
//         }
//         for (int j = 0; j <= 26; j++) {
//             if (received[i] == translation[j][0]) {
//                 for (int k = 1; k < 6 && translation[j][k] != WORDEND; k++) {
//                     code[pos++] = translation[j][k];
//                 }
//             }
//         }
//     }
// }

// void translate(char word[], int num[]) {
//     if (word[0] == DOT || word[0] == DASH) {
//         int row = 0, colT = 0, colW = 0, colw = 0, letters = 0;
//         for (row = 0; row < 26; row++) {
//             for (colT = 1, colW = colw; colT < 6; colT++, colW++) {
//                 int numTrans = translation[row][colT];
//                 int numWord = word[colW];
//                 int numTrans2 = translation[row][colT + 1];
//                 int numWord2 = word[colW + 1];
//                 if (translation[row][colT] != word[colW]) {
//                     break;
//                 }
//                 if (word[colW] == END) {
//                     return;
//                 } else if ((word[colW] == WORDEND || word[colW] == END)) {
//                     num[letters] = translation[row][0];
//                     row = -1;
//                     colw = colW + 1;
//                     letters++;
//                     break;
//                 }
//             }
//         }
//     } else {
//         for (int i = 0; i < ARR_SIZE && word[i + 1] != END; i++) {
//             num[i] = toupper(word[i]);
//         }
//     }
// }