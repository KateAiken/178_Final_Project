#include "queue.h"

#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>

pQueue q = NULL;

pQueue CreateQueue(void) {
    pQueue pnew = (pQueue)malloc(sizeof(struct queue));
    if (pnew != NULL) {
        pnew->front = NULL;
        pnew->back = NULL;
        pnew->count = 0;
    }
    return pnew;
}

pItem CreateItem(int arr[]) {
    pItem pnew = (pItem)malloc(sizeof(Item));
    if (pnew != NULL) {
        for (int i = 0; i < ARR_SIZE; i++) {
            pnew->word[i] = arr[i];
        }
        pnew->next = NULL;
    } else {
    }
    return pnew;
}

int IsQEmpty(pQueue queue) { return queue->count == 0; }

int Enqueue(pQueue queue, pItem item) {
    if (IsQEmpty(queue)) {
        queue->back = item;
        queue->front = item;
    } else {
        queue->back->next = item;
        queue->back = item;
    }

    queue->count++;
    return EXIT_OK;
}

int DequeueAll(pQueue queue) {
    pItem current = queue->front;
    while (current != NULL) {
        pItem temp = current;
        current = current->next;
        free(temp);
    }

    queue->front = NULL;
    queue->back = NULL;
    queue->count = 0;
    return EXIT_OK;
}

void printQ(pQueue queue) {
    pItem temp = queue->front;
    int counter = 0;

    while (counter < queue->count && temp != NULL) {
        for (int i = 0; i < ARR_SIZE; i++) {
            if (temp->word[i] != END) {
                printf("%d ", temp->word[i]);
                Serial.print(temp->word[i]);
            } else {
                break;
            }
        }
        printf(" <-- ");
        Serial.print(" <-- ");
        temp = temp->next;
        counter++;
    }
    printf("END\n");
    Serial.println("END");
}
