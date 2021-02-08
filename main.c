/*
Implementation of Efficient Shortest Remaining Time Round Robin (ESRR)
from paper on Efficient Process Scheduling Algorothm using RR and SRTF by Preet Sinha et al.
*/
#include <stdlib.h>
#include <stdio.h>

/* TO-DOs
- Research on circular buffer array implementation
*/

int main(void){
  /* 
  Take input of exec_time and arr_time
  Allocate CPU to front process
  Step2:
  If(new process arrives)
    If(no process exists in ready queue)
      Allocate cpu to new process
    Else
      Compare exe_time of process with the existing processes from front to rear
    If(exe_time is less)
      Put the new process before comparing process in the ready queue
    Else
      insert in the queue at (++rear) position.
    Endif
    Endif
  Endif
  If (process exists)
    If(remexe_time<=TQ)
      Allocate CPU to front process for remexe_time
      Remove the process from ready queue
    Else
      Allocate for the TQ time interval
    Endif
  Endif
  Repeat this block till all the process get executed.
  Step3:
  If (new process added)
    Input exe_time and repeat step2
  Endif
*/
  return 0;
}

