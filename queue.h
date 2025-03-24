#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "morse.h"    
//#include <Arduino.h> 
//#include <Wire.h>

#define EXIT_OK 0
#define EXIT_ERR -1
#define ARR_SIZE 50

// Node structure
typedef struct item {
    struct item *next;
    int word[ARR_SIZE];
} Item, *pItem;

// Queue structure
typedef struct queue {
    pItem front;
    pItem back;
    int count;
} Queue, *pQueue;

// Queue *q;

pQueue CreateQueue(void);

pItem CreateItem(int arr[]);

bool IsQEmpty(pQueue queue);

int Enqueue(pQueue queue, pItem item);

int Dequeue(pQueue queue, int arr[]);

int DequeueAll(pQueue queue);

void printQ(pQueue que);

#endif
