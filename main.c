/*
Implementation of Efficient Shortest Remaining Time Round Robin (ESRR)
from paper on Efficient Process Scheduling Algorothm using RR and SRTF by Preet Sinha et al.

Circular Queue Implementation referenced from https://www.programiz.com/dsa/circular-queue
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct proc_struct {
    int id;
    int bst_time;
    int arr_time;
    int exe_time;
} Proc_Info;

typedef struct node_struct {
    Proc_Info proc_data;
    struct node_struct *next;
    struct node_struct *prev;
} Proc_Node;

/* TO-DOs

*/

void displayQueue(Proc_Node **);

void enQueueLL(Proc_Info proc, Proc_Node **queueHdPtr);

Proc_Node *deQueueLL(Proc_Node **queueHdPtr);

Proc_Node *deQueueFromLL(Proc_Node **prev, Proc_Node **curr);

void deQueueProcNoLL(int procNo, Proc_Node **queueHdPtr);

void insertSort(Proc_Node **);

bool isQueueEmpty(Proc_Node *);

void printMsg(char *);

int numProc;
Proc_Node *nextProc = NULL;

int main(void) {

    int execTime, arrTime, tQ;
    //Step 1:
    // First take input of no. of processes into n.
    printf("Please input the number of processes: ");
    scanf("%d", &numProc);

    //Setting up array to hold the number of jobs desired by user
    Proc_Info jobs[numProc];
    //Setting up the ready queue to contain jobs ready to executed
    Proc_Node *rQHead = NULL;

    //Take input of bst_time and arr_time and queue processes into job queue
    for (int i = 0; i < numProc; i++) {
        printf("Please input the execution time of process %d\n", i + 1);
        scanf("%d", &execTime);
        printf("Please input the arrival time of process %d\n", i + 1);
        scanf("%d", &arrTime);
        jobs[i].id = i + 1;
        jobs[i].bst_time = execTime;
        jobs[i].exe_time = execTime;
        jobs[i].arr_time = arrTime;
    }
    printf("Please input your desired time quantum: \n");
    scanf("%d", &tQ);

    int elapsedTime = 0;
    bool schRunning = true;

    for (int i = 0; i < sizeof(jobs) / sizeof(jobs[0]); i++) {
        if (jobs[i].arr_time <= elapsedTime) {
            // If exec_time is less than or equals to quantum
            if (jobs[i].exe_time <= tQ) {
                // If Ready queue is empty
                if (rQHead == NULL) {
                    // if CPU IDLE means no next process to be executed
                    if (nextProc == NULL) {
                        elapsedTime += jobs[i].exe_time;
                        jobs[i].exe_time -= jobs[i].exe_time;
                    } else {
                        enQueueLL(jobs[i], &rQHead);
                    }
                } else {
                    enQueueLL(jobs[i], &rQHead);
                }
            } else if (jobs[i].exe_time > tQ) {
                if (rQHead == NULL) {
                    if (nextProc == NULL) {
                        elapsedTime += tQ;
                        jobs[i].exe_time -= tQ;
                        enQueueLL(jobs[i], &rQHead);
                    } else {
                        enQueueLL(jobs[i], &rQHead);
                    }
                } else {
                    enQueueLL(jobs[i], &rQHead);
                }
            }
            insertSort(&rQHead);
            displayQueue(&rQHead);
            nextProc = rQHead;
        }
    }



    return 0;
}

//Adds a process to the back of a linked list
void enQueueLL(Proc_Info proc, Proc_Node **queueHdPtr) {
    printf("DEBUG2: Arr time %d\n", proc.arr_time);

    Proc_Node *newNode = (Proc_Node *) malloc(sizeof(Proc_Node));

    newNode->proc_data = proc;
    newNode->next = NULL;

    if (isQueueEmpty(*queueHdPtr)) {
        newNode->prev = NULL;
        *queueHdPtr = newNode;
    } else {
        //Defining a temporary pointer variable to hold head
        Proc_Node *temp = *queueHdPtr;

        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

//Removes a process from the front of a linked list
Proc_Node *deQueueLL(Proc_Node **queueHdPtr) {
    Proc_Node *oldHead = *queueHdPtr;
    *queueHdPtr = (*queueHdPtr)->next;
    if (*queueHdPtr != NULL) {
        (*queueHdPtr)->prev = NULL;
    }
    oldHead->next = NULL;
    return oldHead;
}

//Remove a process from back of linked list
Proc_Node *deQueueFromBack(Proc_Node **queueHdPtr) {
    Proc_Node *last = *queueHdPtr;

    while (last->next != NULL) {
        last = last->next;
    }

    if (!isQueueEmpty(*queueHdPtr)) {
        if ((*queueHdPtr)->next == NULL) {
            last = deQueueLL(queueHdPtr);
        } else if ((*queueHdPtr)->next != NULL) {
            last->prev->next = NULL;
            last->prev = NULL;
        }
    }

    return last;
}

Proc_Node *deQueueFromLL(Proc_Node **prev, Proc_Node **curr) {
    Proc_Node *remProc;
    //Deference double pointers getting  actual pointers to previous and current nodes
    if ((*curr)->next != NULL) {
        (*prev)->next = (*curr)->next;
        remProc = *curr;
    } else {
        remProc = deQueueLL(curr);
    }
    return remProc;
}

void deQueueProcNoLL(int procNo, Proc_Node **queueHdPtr) {
    Proc_Node *temp = *queueHdPtr;
    Proc_Node *prevNode = NULL;
    Proc_Node *remNode = NULL;

    while (temp != NULL) {
        if (temp->proc_data.id == procNo) {
            remNode = temp;
            if (prevNode == NULL) {
                *queueHdPtr = (*queueHdPtr)->next;
            } else if (prevNode != NULL) {
                prevNode->next = temp->next;
            }
        }
        prevNode = temp;
        temp = temp->next;
    }

    printf("%d\n", remNode->proc_data.id);
    //free(remNode);
}

//Proc_Node *remProcFrom()

bool isQueueEmpty(Proc_Node *queueHdPtr) {
    if (queueHdPtr == NULL) {
        return true;
    }
    return false;
}

//Loops through and prints the contents of a linked list
void displayQueue(Proc_Node **queueHdPtr) {
    Proc_Node *temp = *queueHdPtr;

    if (isQueueEmpty(temp)) {
        printf("No processes in %s queue\n", "Ready");
    } else {
        printf("Processes in %s queue: \n", "Ready");
    }

    while (temp != NULL) {
        if (temp->next != NULL) {
            printf("%d => ", temp->proc_data.id);
        } else if (temp->next == NULL) {
            printf("%d", temp->proc_data.id);
        }
        temp = temp->next;
    }
    printf("\n");
}

void sortedInsert(Proc_Node **queueHdPtr, Proc_Node *newNode) {
    Proc_Node *current;

    //If queue is empty then no need to sort
    if (isQueueEmpty(*queueHdPtr)) {
        *queueHdPtr = newNode;
    } else if ((*queueHdPtr)->proc_data.exe_time >= newNode->proc_data.exe_time) {
        newNode->next = *queueHdPtr;
        newNode->next->prev = newNode;
        *queueHdPtr = newNode;
    } else {
        current = *queueHdPtr;

        //Locate position of node before where new node should be inserted
        // Eg. if in ready queue there are processes with exec time 1 => 4 => 9
        // and we want to insert a process with exec time 2
        // Then current will be process with exec time one since the loop condition fails
        // as exec time of 4 is not less than 2
        while (current->next != NULL && current->next->proc_data.exe_time < newNode->proc_data.exe_time) {
            current = current->next;
        }

        //Do the necessary linking
        newNode->next = current->next;

        //If new node is not inserted to tail of list
        if (current->next != NULL) {
            newNode->next->prev = newNode;
        }

        //More linking
        current->next = newNode;
        newNode->prev = current;
    }
}

void insertSort(Proc_Node **queueHdPtr) {
    Proc_Node *temp = *queueHdPtr;
    Proc_Node *sortHead = NULL;

    while (temp != NULL) {
        //Save the next pointer first
        Proc_Node *next = temp->next;

        //Removing links from temp so it can be used as a node for insertion
        temp->prev = NULL;
        temp->next = NULL;

        sortedInsert(&sortHead, temp);

        //Set to continue loop traversal
        temp = next;
    }

    //Update queue head to point to sorted queue
    *queueHdPtr = sortHead;
}

void printMsg(char *msg) {
    printf("%s\n", msg);
}