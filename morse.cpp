#include "morse.h"
#include "queue.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

void getTextTerminal(char text[]) {

    printf("Enter Sentence: ");
    fgets(text, ARR_SIZE - 1, stdin);
    if (text[(strlen(text)) - 1] == '\n') {
        text[(strlen(text)) - 1] = '\0';
    }
}

// int getTextSerial() {return 1;}

void toNum(char sentance[], Queue *queue) {
    char word[ARR_SIZE] = {END};
    int word_int[ARR_SIZE] = {END};

    int k = 0;
    for (int i = 0, j = 0; i < 100 && sentance[k] != END; i++, j++) {
        if (sentance[i] == 10 || sentance[i] == 47) {
            sentance[i] = END;
        }
        if (sentance[i] != SPACE && sentance[i] != END) {
            word[j] = sentance[i];

        } else {
            word[j] = WORDEND;
            translate(word, word_int);

            Enqueue(queue, CreateItem(word_int));
            print(word, word_int, ARR_SIZE);

            memset(word, END, sizeof(word));
            memset(word_int, END, sizeof(word_int));
            j = -1;
        }
        k = i;
    }
}

void translate(char word[], int num[]) {
    if (word[0] == DOT || word[0] == DASH) {
        int row = 0, colT = 0, colW = 0, colw = 0, letters = 0;
        for (row = 0; row < 26; row++) {
            for (colT = 1, colW = colw; colT < 6; colT++, colW++) {
                int numTrans = translation[row][colT];
                int numWord = word[colW];
                int numTrans2 = translation[row][colT + 1];
                int numWord2 = word[colW + 1];
                if (translation[row][colT] != word[colW]) {
                    break;
                }
                if (word[colW] == END) {
                    return;
                } else if ((word[colW] == WORDEND || word[colW] == END)) {
                    num[letters] = translation[row][0];
                    row = -1;
                    colw = colW + 1;
                    letters++;
                    break;
                }
            }
        }
    } else {
        for (int i = 0; i < ARR_SIZE && word[i + 1] != END; i++) {
            num[i] = toupper(word[i]);
        }
    }
}

void print(char arrChar[], int arrInt[], int length) {
    for (int i = 0; i < length; i++) {
        if (arrChar[i] == END) {
            break;
        }
        if (arrChar[i] == '0') {
            printf("  ");
        } else {
            printf("%c ", arrChar[i]);
        }
    }
    printf("\n");
    for (int i = 0; i < length; i++) {
        if (arrInt[i] == 0) {
            break;
        } else {
            printf("%d ", arrInt[i]);
        }
    }
    printf("\n");
}

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
                          {78, DASH, DASH, DOT, WORDEND, WORDEND},        // N
                          {79, DASH, DASH, DASH, WORDEND, WORDEND},       // O
                          {80, DOT, DASH, DASH, DOT, WORDEND},            // P
                          {81, DASH, DASH, DOT, DASH, WORDEND},           // Q
                          {82, DOT, DASH, DOT, WORDEND, WORDEND},         // R
                          {83, DOT, DOT, DOT, WORDEND, WORDEND},          // S
                          {84, DASH, WORDEND, WORDEND, WORDEND, WORDEND}, // T
                          {85, DOT, DOT, DASH, WORDEND, WORDEND},         // U
                          {86, DOT, DOT, DOT, DASH, WORDEND},             // V
                          {87, DOT, DASH, DASH, WORDEND, WORDEND},        // W
                          {88, DASH, DOT, DOT, DASH, WORDEND},            // Y
                          {89, DASH, DOT, DASH, DASH, WORDEND},           // X
                          {90, DASH, DASH, DOT, DOT, WORDEND}};           // Z
