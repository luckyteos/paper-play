//
// Created by jmteo on 21/2/2021.
//

#include "utilities.h"

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

//Removes a process, given its id, from a specified queue
void removeProcessNo(Proc_Node **queueHdPtr, int procId) {
    Proc_Node *temp = *queueHdPtr;
    Proc_Node *remProc = NULL;

    while (temp != NULL) {
        if (temp->proc_data.id == procId) {
            remProc = temp;
            //If element to be removed is the only element in the queue or at the back of the queue
            if (temp->next == NULL) {
                //If element to be removed is at the back of the queue
                if (temp->prev != NULL) {
                    temp->prev->next = NULL;
                    temp->prev = NULL;
                } else { //If element to be removed is the only element in queue
                    *queueHdPtr = NULL;
                }
            } else if (temp->next != NULL) {
                // If element is not at front of the queue
                if (temp->prev != NULL) {
                    temp->prev->next = temp->next;
                } else {
                    *queueHdPtr = temp->next;
                }
                temp->next->prev = temp->prev;
            }
        }
        temp = temp->next;
    }

    if (remProc != NULL) {
        printf("Rem proc id %d\n", remProc->proc_data.id);
        free(remProc);
    }
}

//Given a process number, find it in the queue and remove its associated node
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

    printf("DEBUG: Removed Process %d\n", remNode->proc_data.id);
    free(remNode);
}

bool procNodeExists(Proc_Node **queueHdPtr, int procId) {
    Proc_Node *temp = *queueHdPtr;

    while (temp != NULL) {
        if (temp->proc_data.id == procId) {
            return true;
        }
        temp = temp->next;
    }

    return false;
}

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

//Insert a new node into the queue, in ascending order
void sortedInsert(Proc_Node **queueHdPtr, Proc_Node *newNode) {
    Proc_Node *current;

    //If queue is empty then no need to sort
    if (isQueueEmpty(*queueHdPtr)) {
        *queueHdPtr = newNode;
	  //If execution time of the first element in queue is more than or equal to the node to be added
    } else if ((*queueHdPtr)->proc_data.exe_time >= newNode->proc_data.exe_time) {
		//Put the node to be added before the first element in queue
        newNode->next = *queueHdPtr;
        newNode->next->prev = newNode;
		//Update the first element in the queue to newNode
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

//Traverse the ready queue, sort the processes by exec time, then return the sorted ready queue
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
