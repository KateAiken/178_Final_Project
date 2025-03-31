/*******************************************************
morse.h

Header File for morse.ccp
********************************************************/

// Header file initialization 
#ifndef MORSE_H_
#define MORSE_H_

// Include Libraries
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Include headerfiles 
#include "bst.h"
#include "queue.h"

//Global Variable Definition
#define DASH 45
#define DOT 46
#define SPACE 32
#define END 0
#define WORDEND 48
#define NEWLINE 10
#define ARR_SIZE 50

// Include structures
struct queue;
struct node;
typedef node *pNode;

// Stack Structure Initialization
typedef struct stack {
    int top;
    int stack[4];
} *Stack;

// Declare external array
extern int translation[26][6];

// Function Decleration
void toNum(char sentance[], queue *queue);

void translate(char word[], int num[]);

void toMorse(char code[], char word[], int received[]);

void push(int value);

int pop();

// Close Header File
#endif