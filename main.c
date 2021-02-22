/*
Implementation of Efficient Shortest Remaining Time Round Robin (ESRR)
from paper on Efficient Process Scheduling Algorothm using RR and SRTF by Preet Sinha et al.

Circular Queue Implementation referenced from https://www.programiz.com/dsa/circular-queue
*/
#include "utilities.h"

/* TO-DOs
    Idea behind Algorithm
	Let all processes arrive first [Execute for loop]
	Then run the bottom loop the execute next process
	Let remaining processes arrive
	Then run bottom loop again to execute remaining processes
*/

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
        jobs[i].status = -1;
    }
    printf("Please input your desired time quantum: \n");
    scanf("%d", &tQ);

    int elapsedTime = 0;
    bool schRunning = true;
    bool procAlloc = false;

    while (schRunning) {
        for (int i = 0; i < sizeof(jobs) / sizeof(jobs[0]); i++) {
            procAlloc = false;
            if (jobs[i].status == -1) {
                if (jobs[i].arr_time <= elapsedTime) {
                    jobs[i].status = 0;
                    // If exec_time is less than or equals to quantum
                    if (jobs[i].exe_time <= tQ) {
                        // If Ready queue is empty
                        if (rQHead == NULL) {
                            // if CPU IDLE means no next process to be executed
                            if (nextProc == NULL) {
                                elapsedTime += jobs[i].exe_time;
                                jobs[i].exe_time -= jobs[i].exe_time;
                                procAlloc = true;
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
                                procAlloc = true;
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
        }

        bool remProc = false;
        Proc_Node *temp = NULL;

        printf("Next proc id %d\n", nextProc->proc_data.id);
        if (procNodeExists(&rQHead, nextProc->proc_data.id)) {
            elapsedTime += tQ;
            nextProc->proc_data.exe_time -= tQ;
            procAlloc = true;

            if (nextProc->proc_data.exe_time <= 0) {
                temp = nextProc;
                remProc = true;
            }

            nextProc = nextProc->next;

            if (nextProc == NULL) {
                printMsg("Next Proc is NULL");
            }

            if (remProc) {
                if (temp == NULL) {
                    printMsg("Temp is null");
                } else {
                    printf("Temp proc id %d\n", temp->proc_data.id);
                }
                removeProcessNo(&rQHead, temp->proc_data.id);
                displayQueue(&rQHead);
            }
        }


        if (isQueueEmpty(rQHead)) {
            procAlloc = false;
            schRunning = false;
        }

    }
    return 0;
}

