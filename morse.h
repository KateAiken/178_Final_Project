#ifndef MORSE_H_
#define MORSE_H_

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "bst.h"
#include "queue.h"

#define DASH 45
#define DOT 46
#define SPACE 32
#define END 0
#define WORDEND 48
#define NEWLINE 10
#define ARR_SIZE 25

struct queue;
struct node;
typedef node *pNode;

typedef struct stack {
    int top;
    int stack[4];
} *Stack;

extern int translation[26][6];

void toNum(char sentance[], queue *queue);

void translate(char word[], int num[]);

void toMorse(char code[], char word[], int received[]);

void push(int value);

int pop();

#endif