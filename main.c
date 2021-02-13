/*
Implementation of Efficient Shortest Remaining Time Round Robin (ESRR)
from paper on Efficient Process Scheduling Algorothm using RR and SRTF by Preet Sinha et al.

Circular Queue Implementation referenced from https://www.programiz.com/dsa/circular-queue
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct proc_struct{
  int id;
  int exec_time;
  int arr_time;
  int remexe_time;
  struct proc_struct *next;
} Proc_Info;

/* TO-DOs
- Continue Algorithm Development

Ideas from 13/2
- Have a pointer that keeps track of all processes
- Continue using current loop pointer
- Search for current looped process and remove it from pointer keeping track of process
*/

void displayQueue(Proc_Info **, int);
void enQueue(Proc_Info *, Proc_Info **);
Proc_Info *deQueue(Proc_Info **);
Proc_Info *deQueueFrom(Proc_Info **, Proc_Info **);
bool isQueueEmpty(Proc_Info *);
void printMsg(char *);

//Intialise head and tail to -1 as queue is empty
int head = -1, tail = -1;
int numProc;

int main(void){
  
  int execTime, arrTime, tQ;
  bool schComplete;
  //Step 1: 
  // First take input of no. of processes into n.
  printf("Please input the number of processes: ");
  scanf("%d", &numProc);

  //Setting up the job queue to contain all processes in system
  Proc_Info *jQHead = NULL;
  //Setting up the ready queue to contain jobs ready to executed
  Proc_Info *rQHead = NULL;
  //Take input of exec_time and arr_time and queue processes into job queue
  for (int i = 0; i < numProc; i++){
      printf("Please input the execution time of process %d\n", i+1);
      scanf("%d", &execTime);
      printf("Please input the arrival time of process %d\n", i+1);
      scanf("%d", &arrTime);
      printf("DEBUG: Arr time input: %d\n", arrTime);
      Proc_Info *newProc = (Proc_Info *)malloc(sizeof(Proc_Info));
      if (newProc == NULL){
          printf("Malloc failed\n");
          return -3;
      }
      newProc->id = i + 1;
      newProc->exec_time = execTime;
      newProc->arr_time = arrTime;
      newProc->remexe_time = 0;
      enQueue(newProc, &jQHead);      
  }
  printf("Please input your desired time quantum: \n");
  scanf("%d", &tQ);

  //Allocate CPU to head process
  Proc_Info *fProc = deQueue(&jQHead);
  enQueue(fProc, &rQHead); 
  printf("Job Queue\n");
  displayQueue(&jQHead, 0);

  // while (!schComplete){
      int elapsedTime = 2;
      //One pointer to manage to loop for comparison
      Proc_Info *tmpJbLpPtr = jQHead;
      //Another to manage processes in queue
      Proc_Info *tmpJbQPtr = jQHead;
      Proc_Info *prevJbNode = NULL;

      while (tmpJbLpPtr != NULL) {
        printf("Queue status\n");
        displayQueue(&tmpJbLpPtr, 0);
        printf("Processing Jobs %d\n", tmpJbLpPtr->id);
        printf("DEBUG 0: arr %d\n", tmpJbLpPtr->arr_time);
        printf("DEBUG 0.1: time %d\n", elapsedTime);
        if (tmpJbLpPtr->arr_time == elapsedTime) {
            printf("process arrives\n");
            if (isQueueEmpty(rQHead)){
                enQueue(tmpJbLpPtr, &rQHead);
                deQueue(&tmpJbQPtr);
            } else {
                Proc_Info *tmpRyPtr = rQHead;
                printf("Ready Queue Head %d\n", rQHead->id);
                printf("Ry Ptr: %d", tmpRyPtr->id);
                Proc_Info *prevRyNode = (Proc_Info *)calloc(1, sizeof(Proc_Info));
                while (tmpRyPtr != NULL){
                  if (tmpJbLpPtr->exec_time < tmpRyPtr->exec_time){
                      printf("Loop executes\n");

                      //Impt to malloc new memory space to save the process to prevent memory leak causing unexpected behaviour
                      Proc_Info *switchProc = (Proc_Info *)calloc(1, sizeof(Proc_Info));
                      printf("Got to here\n");
                      Proc_Info *remJobNode = deQueueFrom(&prevJbNode, &tmpJbLpPtr);
                      *switchProc = *remJobNode;

                      if (switchProc == NULL){
                          printf("Malloc Failed\n");
                      }

                      printf("Got to here\n");
                      printf("DEBUG: switchProc %d\n", switchProc->id);
                      if (jQHead->next == NULL){
                          printf("Null is next\n");
                      }
                      //Ready Queue only has one process
                      if (tmpRyPtr->next == NULL){
                          switchProc->next = tmpRyPtr;
                          rQHead = switchProc;
                          displayQueue(&tmpJbLpPtr, 0);
                      } else {
                          printf("Wello1\n");
                          //printf("prevNode Debug %d\n", prevRyNode->id);
                          //If at front of ready queue
                          if (prevRyNode == NULL){
                              switchProc->next = rQHead;
                              rQHead = switchProc;
                          } else {
                              prevRyNode->next = switchProc;
                              switchProc->next = tmpRyPtr;
                              printMsg("Wello 2");
                          }
                      }
                  }
                  printMsg("Got to here");
                  *prevRyNode = *tmpRyPtr;
                  tmpRyPtr = tmpRyPtr->next;
                }
                printMsg("Got to here");
                displayQueue(&rQHead, 1);
            }
        }
        printMsg("Got to here");
        displayQueue(&jQHead, 0);
        prevJbNode = tmpJbLpPtr;
        if (tmpJbLpPtr->next == NULL){
            printf("End of job queue\n");
        }
        if (tmpJbLpPtr->next != NULL){
            printf("Next values %d\n", (tmpJbLpPtr->next)->id);
        }
        tmpJbLpPtr = tmpJbLpPtr->next;
      }
      displayQueue(&rQHead, 1);
      displayQueue(&jQHead, 0);
  // }
  //     for (int i = 0; i < numProc; i++){
  //         if (jQueue[i].arr_time == elapsedTime){
  //             if (isQueueEmpty()) {
  //                 enQueue(jQueue[i], rQueue);
  //             } else {
  //                 for (int z = 0; z < numProc; z++){
  //                     if (jQueue[i].exec_time < rQueue[z].exec_time){
  //                         //Put the new process before comparing process in the ready queue 
  //                         if (z == 0 && tail == 0) {
  //                             jQueue[numProc - 1] = 
  //                         }
  //                     }
  //                 }
  //             }
  //         }
  //     }
  // }
  //Allocate CPU to head process
  // while (!schComplete) {
  //     // For all processes
  //     for (int z = 0; z < numProc; z++) {
  //       if (rQueue[z].status == 0){
  //           if (rQueue[z].arr_time == elapsedTime){
  //               rQueue[z].status = 1;
  //           }
  //       }
  //     }

  // }
  //Step2:
  //If(new process arrives)
    //If(no process exists in ready queue)
      //Allocate cpu to new process
    //Else
      //Compare exe_time of process with the existing processes from head to tail
    //If(exe_time is less)
      //Put the new process before comparing process in the ready queue
    //Else
      //insert in the queue at (++tail) position.
    //Endif
    //Endif
  //Endif
  //If (process exists)
    //If(remexe_time<=TQ)
      //Allocate CPU to head process for remexe_time
      //Remove the process from ready queue
    //Else
      //Allocate for the TQ time interval
    //Endif
  //Endif
  //Repeat this block till all the process get executed.
  //Step3:
  //If (new process added)
    //Input exe_time and repeat step2
  //Endif
  return 0;
}

//Adds a process to the back of a linked list
void enQueue(Proc_Info *proc, Proc_Info **queueHdPtr){
  printf("DEBUG2: Arr time %d", proc->arr_time);
  if (*queueHdPtr == NULL){
    proc->next = *queueHdPtr;
    *queueHdPtr = proc;
  } else if (*queueHdPtr != NULL){
     //Defining a temporary pointer variable to hold head
    Proc_Info *temp = *queueHdPtr;
    proc->next = NULL;
          
    while (temp->next != NULL){
        temp = temp->next;
    }
        temp->next = proc;
  }
}

//Removes a process from the front of a linked list
Proc_Info *deQueue(Proc_Info **queueHdPtr){
  Proc_Info *oldHead = *queueHdPtr;
  *queueHdPtr = (*queueHdPtr)->next;
  return oldHead;
}

Proc_Info *deQueueFrom(Proc_Info ** prev, Proc_Info ** curr){
  Proc_Info *remProc;
  //Deference double pointers getting  actual pointers to previous and current nodes
  if ((*curr)->next != NULL){
      (*prev)->next = (*curr)->next;
      remProc = *curr;
  } else {
      remProc = deQueue(curr);
  }
  return remProc;
}

//Proc_Info *remProcFrom()

bool isQueueEmpty(Proc_Info *queueHdPtr){
    if (queueHdPtr == NULL) {
      return true;
    }
    return false;
}

//Loops through and prints the contents of a linked list
void displayQueue(Proc_Info **queueHdPtr, int type){
    Proc_Info *temp = *queueHdPtr;
    if (temp == NULL){
      printf("No processes in queue\n");
    } else {
      if (type == 0) {
          printf("Processes in job queue: \n");
      } else if (type == 1){
          printf("Processes in ready queue: \n");
      }
    }

    while (temp != NULL){
      printf("%d => ", temp->id);
      temp = temp->next;
    }
    printf("\n");
    printMsg("Testing 123");
}

void printMsg(char * msg){
  printf("%s", msg);
}