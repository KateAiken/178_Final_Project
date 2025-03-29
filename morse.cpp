#include "morse.h"
#include "bst.h"
#include "queue.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

Stack path = (Stack)malloc(sizeof(struct stack));

void getTextTerminal(char text[]) {

    printf("Enter Sentence: ");
    fgets(text, ARR_SIZE - 1, stdin);
    if (text[(strlen(text)) - 1] == '\n') {
        text[(strlen(text)) - 1] = END;
    }
}

void toNum(char sentance[], Queue *queue) {
    char word[ARR_SIZE] = {END};
    int word_int[ARR_SIZE] = {END};

    int k = 0;
    for (int i = 0, j = 0; i < ARR_SIZE && sentance[k] != END; i++, j++) {
        if (sentance[i] == NEWLINE || sentance[i] == 47) {
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
        int temp[4] = {END};
        int count = 0;
        for (int i = 0, j = 0; i < ARR_SIZE && word[i] != END; i++, j++) {
            if (word[i] != WORDEND) {
                temp[j] = word[i];
                Serial.println(temp[j]);
            } else {
                Serial.println("Search");
                pNode node = letterSearch(temp, 0, root);
                num[count] = node->letter;
                Serial.println("find");
                Serial.println(num[count]);
                count++;
                for (int k = 0; k < 4; k++) {
                    temp[k] = END;
                }
                j = -1;
            }
        }
    } else {
        for (int i = 0; i < ARR_SIZE && word[i + 1] != END; i++) {
            num[i] = toupper(word[i]);
        }
    }
}

pNode letterSearch(int code[], int depth, pNode current) {
    Serial.println(code[depth]);
    Serial.println(current->letter);
    if (code[depth] == DASH) {
        Serial.println("Dash");
        return letterSearch(code, depth + 1, current->dash);
    } else if (code[depth] == DOT) {
        Serial.println("Dot");
        return letterSearch(code, depth + 1, current->dot);
    } else {
        // Serial.println(current->letter);
        return current;
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

void toMorse(char code[], char word[], int received[]) {
    for (int i = 0; i < ARR_SIZE && received[i] != END; i++) {
        if (received[i] != END) {
            word[i] = (char)received[i];
        }
    }
    int pos = 0;
    path->top = -1;
    for (int i = 0; i < ARR_SIZE && received[i] != END; i++) {
        if (received[i] == SPACE)
            code[pos++] = SPACE;
        else if (codeSearch(root, received[i])) {
            int inc = path->top;
            for (int j = inc; j >= 0; j--) {
                code[j + pos] = pop();
            }
            pos += inc+1;
            path->top = -1;
        }
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

void push(int value) {
    path->stack[++(path->top)] = value;
}
int pop() {
    return path->stack[(path->top)--];
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