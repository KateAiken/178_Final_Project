/*******************************************************
queue.h

Header File for queue.ccp
********************************************************/

// Header file initialization 
#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

// Include headerfiles 
#include "morse.h"

// Global Variable Definition
#define EXIT_OK 0
#define EXIT_ERR -1
#define ARR_SIZE 50

// Define Queue Item Structure
typedef struct item {
    struct item *next;
    int word[ARR_SIZE];
} Item, *pItem;

// Define Queue Structure
typedef struct queue {
    pItem front;
    pItem back;
    int count;
} Queue, *pQueue;

// Declare external queue
extern pQueue q;

// Function Decleration
pQueue CreateQueue(void);

pItem CreateItem(int arr[]);

int IsQEmpty(pQueue queue);

int Enqueue(pQueue queue, pItem item);

int DequeueAll(pQueue queue);

void printQ(pQueue que);

// Close Header File
#endif