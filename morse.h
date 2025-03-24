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

#endif

/*
int translation[26][5] = {{65, DOT, DASH, WORDEND, WORDEND},       // A
                          1{66, DASH, DOT, DOT, DOT},   // B
                          2 {67, DASH, DOT, DASH, DOT},  // C
                          3{68, DASH, DOT, DOT, WORDEND},     // D
                          4{69, DOT, WORDEND, WORDEND, WORDEND},          // E
                          5{70, DOT, DOT, DASH, DOT},   // F
                          6{71, DASH, DASH, DOT, WORDEND},    // G
                          7{72, DOT, DOT, DOT, DOT},    // H
                          8{73, DOT, DOT, WORDEND, WORDEND},        // I
                          9{74, DOT, DASH, DASH, DASH}, // J
                         10{75, DASH, DOT, DASH, WORDEND},    // K
                         11{76, DOT, DASH, DOT, DOT},   // L
                         12{77, DASH, DASH, WORDEND, WORDEND},      // M
                         13{78, DASH, DASH, DOT, WORDEND},    // N
                         14{79, DASH, DASH, DASH, WORDEND},   // O
                         15{80, DOT, DASH, DASH, DOT},  // P
                         16{81, DASH, DASH, DOT, DASH}, // Q
                         17{82, DOT, DASH, DOT, WORDEND},     // R
                         18{83, DOT, DOT, DOT, WORDEND},      // S
                         19{84, DASH, WORDEND, WORDEND, WORDEND},         // T
                         20{85, DOT, DOT, DASH, WORDEND},     // U
                          {86, DOT, DOT, DOT, DASH},   // V
                          {87, DOT, DASH, DASH, WORDEND},    // W
                          {88, DASH, DOT, DOT, DASH},  // Y
                          {89, DASH, DOT, DASH, DASH}, // X
                          {90, DASH, DASH, DOT, DOT}}; // Z
*/