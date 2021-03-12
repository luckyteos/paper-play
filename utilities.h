//
// Created by jmteo on 21/2/2021.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct proc_struct {
    int id;
    double bst_time;
    double arr_time;
    double exe_time;
    // -1 - new, 0 - Arrived
    int status;
    double comp_time;
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

bool isQueueEmpty(Proc_Node *);

void printGantt(double [], int);

void printMsg(char *);


