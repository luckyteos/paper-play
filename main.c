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
        jobs[i].comp_time = -10;
    }
    printf("Please input your desired time quantum: \n");
    scanf("%d", &tQ);

    int elapsedTime = 0;
    bool schRunning = true;
    bool procAlloc = false;

    while (schRunning) {
        for (int i = 0; i < sizeof(jobs) / sizeof(jobs[0]); i++) {
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
                                printf("DEBUG: Elapsed Time %d\n", elapsedTime);
                                jobs[i].exe_time -= jobs[i].exe_time;
                                jobs[i].comp_time = elapsedTime;
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
                                if (jobs[i].exe_time >= tQ) {
                                    elapsedTime += tQ;
                                    printf("DEBUG: Elapsed Time %d\n", elapsedTime);
                                    jobs[i].exe_time -= tQ;
                                } else if (jobs[i].exe_time < tQ) {
                                    elapsedTime += jobs[i].exe_time;
                                    jobs[i].exe_time -= jobs[i].exe_time;
                                }

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
                    printMsg("Reached Here");
                    displayQueue(&rQHead);
                    nextProc = rQHead;
                }
            }
        }

        bool remProc = false;
        Proc_Node *temp = NULL;

        if (procAlloc) {
            if (rQHead != NULL) {
                //If Ready Queue still has elements but next_process is NULL then set next_process to head
                if (nextProc == NULL) {
                    nextProc = rQHead;
                }
                if (nextProc->proc_data.exe_time < tQ) {
                    procAlloc = true;
                    elapsedTime += nextProc->proc_data.exe_time;
                    nextProc->proc_data.exe_time -= nextProc->proc_data.exe_time;
                } else if (nextProc->proc_data.exe_time >= tQ) {
                    procAlloc = true;
                    elapsedTime += tQ;
                    nextProc->proc_data.exe_time -= tQ;
                }

                if (nextProc->proc_data.exe_time <= 0) {
                    nextProc->proc_data.comp_time = elapsedTime;
                    temp = nextProc;
                    //Assigning back to the process array
                    jobs[nextProc->proc_data.id - 1] = nextProc->proc_data;
                    remProc = true;
                }
                nextProc = nextProc->next;
                if (remProc) {
                    remProc = false;
                    deQueueProcNoLL(temp->proc_data.id, &rQHead);
                }
            } else {
                schRunning = false;
            }
        }
        printf("Current CPU time %d\n", elapsedTime);

    }

    printf("Final Times\n");

    double taTime = 0, waitTime = 0, taSum = 0, waitSum = 0;


    for (int z = 0; z < sizeof(jobs) / sizeof(jobs[0]); z++) {
        printf("Process %d\n", jobs[z].id);
        taTime = jobs[z].comp_time - jobs[z].arr_time;
        printf("Turnaround time %.2f\n", taTime);
        waitTime = taTime - jobs[z].bst_time;
        printf("Waiting time %.2f\n", waitTime);
        taSum += taTime;
        waitSum += waitTime;
    }

    printf("Average Turnaround Time %.2f\n", taSum / numProc);
    printf("Average Waiting Time %.2f\n", waitSum / numProc);
    return 0;
}

