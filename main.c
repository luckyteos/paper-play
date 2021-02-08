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
} Proc_Info;


bool isQueueFull(int);
bool isQueueEmpty();
void enQueue(int, int, int, int, Proc_Info*);
Proc_Info deQueue(int, Proc_Info*);
void displayQueue(int, Proc_Info*);

/* TO-DOs
- Continue Algorithm Development
*/

//Intialise head and tail to -1 as queue is empty
int head = -1, tail = -1;

int main(void){
  int numProc;
  //Step 1: 
  // First take input of no. of processes into n.
  printf("Please input the number of processes: ");
  scanf("%d", &numProc);

  //Setting up the queue based on the number of processes required
  Proc_Info pQueue[numProc];
  //Take input of exec_time and arr_time
  //Allocate CPU to head process
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
  enQueue(1, 20, 0, numProc, pQueue);
  enQueue(2, 12, 1, numProc, pQueue);
  enQueue(3, 8, 2, numProc, pQueue);
  enQueue(4, 10, 2, numProc, pQueue);
  enQueue(5, 2, 4, numProc, pQueue);
  deQueue(numProc, pQueue);
  enQueue(6, 7, 7, numProc, pQueue);
  displayQueue(numProc, pQueue);
  deQueue(numProc, pQueue);
  displayQueue(numProc, pQueue);
  enQueue(6, 7, 7, numProc, pQueue);
  displayQueue(numProc, pQueue);
  return 0;
}

bool isQueueFull(int numProc){
   if ((head == tail + 1) || (head == 0 && tail == numProc - 1)){
      return true;
   }
   return false;
}

bool isQueueEmpty(){
  if (head == -1) {
    return true;
  }
  return false;
}

//Adds a process into the queue
void enQueue(int id, int exec_time, int arr_time, int numProc, Proc_Info *pQueue){
  if (!isQueueFull(numProc)){
      //If its a new 
      if (head == -1){
        head = 0;
      }
      tail = (tail + 1) % numProc;
      pQueue[tail].id = id;
      pQueue[tail].exec_time = exec_time;
      pQueue[tail].arr_time = arr_time;
  }
}

//Removes a process from the queue and return it
Proc_Info deQueue(int numProc, Proc_Info *pQueue){
  Proc_Info el;
  if (!isQueueEmpty()){
      el = pQueue[head];
      if (head == tail){
          head = -1;
          tail = -1;
      } else {
          head = (head + 1) % numProc;
      }
  }
  return el;
}

void displayQueue(int numProc, Proc_Info *pQueue){
    int i;
    if (isQueueEmpty()){
      printf("Queue is empty :(");
    } else {
      printf("Queue Contents\n");
      for (i = head; i != tail; i = (i + 1) % numProc){
          printf("%d[%d]", pQueue[i].id, i);
          if (i == head){
             printf("%s", "(H) > ");
          } else {
             printf(" > ");
          }
      }
      //To print the last element in queue or tail
      printf("%d[%d](T)\n", pQueue[i].id, tail);
    }
}

