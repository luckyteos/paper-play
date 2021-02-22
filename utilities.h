//
// Created by jmteo on 21/2/2021.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct proc_struct {
    int id;
    int bst_time;
    int arr_time;
    int exe_time;
    // -1 - new, 0 - Arrived
    int status;
    bool expired;
} Proc_Info;

typedef struct node_struct {
    Proc_Info proc_data;
    struct node_struct *next;
    struct node_struct *prev;
} Proc_Node;

void displayQueue(Proc_Node **);

void enQueueLL(Proc_Info proc, Proc_Node **queueHdPtr);

Proc_Node *deQueueLL(Proc_Node **queueHdPtr);

Proc_Node *deQueueFromLL(Proc_Node **prev, Proc_Node **curr);

void deQueueProcNoLL(int procNo, Proc_Node **queueHdPtr);

bool procNodeExists(Proc_Node **, int);

void removeProcessNo(Proc_Node **, int);

void insertSort(Proc_Node **);

bool allProcArr(Proc_Info[], int);

bool isQueueEmpty(Proc_Node *);

void printMsg(char *);


