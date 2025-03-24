#include "morse.h"
#include "queue.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    Queue *q = CreateQueue();
    // char input[] = {'H', 'i', SPACE, 'B', 'y', 'e', 10};
    // char input[] = {'.', '.', '.', '0', '-', '-', '-', '0','.', '.', '.', SPACE, '-', '-', '-','\0'};
    // char input[] = {'.', '-', '0', '-', '.', '.', '.', SPACE, '.', '-', '\0'};
    // char input[] = {'.','-','0','.','-', SPACE, '.', '-', '\0'};

    //...0---0... ---
    //....0.. -...0-.--0.

    char input[ARR_SIZE] = {0};
    getTextTerminal(input);
    toNum(input, q);

    printf("\nQueue \n");
    printQ(q);
    return 0;
}
/*
gcc -o output main.cpp morse.cpp queue.cpp
./output
 */