#ifndef MORSE_H_
#define MORSE_H_ 

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "queue.h"

#define DASH 45
#define DOT 46
#define SPACE 32
#define END 0
#define WORDEND 48
#define ARR_SIZE 50

struct queue;

extern int translation[26][6];

void getTextTerminal(char text[]);

void toNum(char sentance[], queue *queue);

void translate(char word[], int num[]);

void print(char arrChar[], int arrInt[], int length);

void toMorse(char code[] , char word[], int received[]);

#endif