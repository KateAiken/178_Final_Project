/*******************************************************
morse.ccp

Encodes and Decondes the Morse code
********************************************************/

// Include headerfiles 
#include "morse.h"
#include "bst.h"
#include "queue.h"

// Include Libraries
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Allocate memory to stack
Stack path = (Stack)malloc(sizeof(struct stack));

void toNum(char sentance[], Queue *queue) { // Function that seperates input into words and creates sendable array
    char word[ARR_SIZE] = {END};
    int word_int[ARR_SIZE] = {END};

    int k = 0;
    for (int i = 0, j = 0; i < ARR_SIZE && sentance[k] != END; i++, j++) {
        if (sentance[i] == NEWLINE || sentance[i] == 47) {
            sentance[i] = END;
        }
        if (sentance[i] != SPACE && sentance[i] != END) { // Adds letter to word array if it is not the end of a word or sentance
            word[j] = sentance[i];

        } else { // Translates and adds word to the queue
            word[j] = WORDEND;
            translate(word, word_int);
            Enqueue(queue, CreateItem(word_int));
            memset(word, END, sizeof(word));
            memset(word_int, END, sizeof(word_int));
            j = -1;
        }
        k = i;
    }
}

void translate(char word[], int num[]) { // Translates one word in text or morse to decimal values
    if (word[0] == DOT || word[0] == DASH) { // Checks if input is text or morse code
        int temp[4] = {END};
        int count = 0;
        for (int i = 0, j = 0; i < ARR_SIZE && word[i] != END; i++, j++) { // sorts through word
            if (word[i] != WORDEND) { // checks if word[i] is the end of a letter
                temp[j] = word[i];
            } else { // Once word is in temp searches BST for the letter the code is associated with
                pNode node = letterSearch(temp, 0, root);
                num[count] = node->letter;
                count++;
                for (int k = 0; k < 4; k++) {
                    temp[k] = END;
                }
                j = -1;
            }
        }
    } else { // Assigns each letter to its decimal number
        for (int i = 0; i < ARR_SIZE && word[i + 1] != END; i++) {
            num[i] = (int)toupper(word[i]);
        }
    }
}

void toMorse(char code[], char word[], int received[]) { // Translates deci array to morse code and text
    for (int i = 0; i < ARR_SIZE && received[i] != END; i++) { // Traverses reviced array to assign to new array as a char 
        if (received[i] != END) {
            word[i] = (char)received[i];
        }
    }
    int pos = 0;
    path->top = -1;
    for (int i = 0; i < ARR_SIZE && received[i] != END; i++) { // Traverses recived array to assing to new array in morse code
        if (received[i] == SPACE)  // Check if the current value is a space
            code[pos++] = SPACE;
        else if (codeSearch(root, received[i])) { // Search BST for the path to the letter of interest
            int inc = path->top;
            for (int j = inc; j >= 0; j--) { // Traverse stack to find path or morse code 
                code[j + pos] = pop();
            }
            pos += inc + 1;
            path->top = -1;
        }
    }
}

void push(int value) { // Pushes values onto stack
    path->stack[++(path->top)] = value;
}

int pop() { // Pops values from stack
    return path->stack[(path->top)--];
}

// Array of morse code definition
int translation[26][6] = {{65, DOT, DASH, WORDEND, WORDEND, WORDEND},     // A
                          {66, DASH, DOT, DOT, DOT, WORDEND},             // B
                          {67, DASH, DOT, DASH, DOT, WORDEND},            // C
                          {68, DASH, DOT, DOT, WORDEND, WORDEND},         // D
                          {69, DOT, WORDEND, WORDEND, WORDEND, WORDEND},  // E
                          {70, DOT, DOT, DASH, DOT, WORDEND},             // F
                          {71, DASH, DASH, DOT, WORDEND, WORDEND},        // G
                          {72, DOT, DOT, DOT, DOT, WORDEND},              // H
                          {73, DOT, DOT, WORDEND, WORDEND, WORDEND},      // I
                          {74, DOT, DASH, DASH, DASH, WORDEND},           // J
                          {75, DASH, DOT, DASH, WORDEND, WORDEND},        // K
                          {76, DOT, DASH, DOT, DOT, WORDEND},             // L
                          {77, DASH, DASH, WORDEND, WORDEND, WORDEND},    // M
                          {78, DASH, DOT, WORDEND, WORDEND, WORDEND},     // N
                          {79, DASH, DASH, DASH, WORDEND, WORDEND},       // O
                          {80, DOT, DASH, DASH, DOT, WORDEND},            // P
                          {81, DASH, DASH, DOT, DASH, WORDEND},           // Q
                          {82, DOT, DASH, DOT, WORDEND, WORDEND},         // R
                          {83, DOT, DOT, DOT, WORDEND, WORDEND},          // S
                          {84, DASH, WORDEND, WORDEND, WORDEND, WORDEND}, // T
                          {85, DOT, DOT, DASH, WORDEND, WORDEND},         // U
                          {86, DOT, DOT, DOT, DASH, WORDEND},             // V
                          {87, DOT, DASH, DASH, WORDEND, WORDEND},        // W
                          {88, DASH, DOT, DOT, DASH, WORDEND},            // X
                          {89, DASH, DOT, DASH, DASH, WORDEND},           // Y
                          {90, DASH, DASH, DOT, DOT, WORDEND}};           // Z