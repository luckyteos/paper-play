/*
Implementation of Efficient Shortest Remaining Time Round Robin (ESRR)
from paper on Efficient Process Scheduling Algorothm using RR and SRTF by Preet
Sinha et al.
*/
#include "utilities.h"
#include <time.h>

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
    //Start the system clock
    clock_t begin = clock();

    //arrInxCt holds the length of the gantt chart array
    int arrInxCt = 0;
    double execTime, arrTime;
    double tQ;

    //For Use with printing out the gantt chart
    double ganttArr[200];
    // Step 1:
    // First take input of no. of processes into n.
    printf("Please input the number of processes: ");
    scanf("%d", &numProc);

    // Setting up array to hold the number of jobs desired by user
    Proc_Info jobs[numProc];
    // Setting up the ready queue to contain jobs ready to executed
    Proc_Node *rQHead = NULL;

	// Take input of bst_time and arr_time and queue processes into job queue
	for (int i = 0; i < numProc; i++) {
        printf("Please input the execution time of process %d\n", i + 1);
        scanf("%lf", &execTime);
        printf("Please input the arrival time of process %d\n", i + 1);
        scanf("%lf", &arrTime);
        jobs[i].id = i + 1;
        jobs[i].bst_time = execTime;
        jobs[i].exe_time = execTime;
        jobs[i].arr_time = arrTime;
        // Set initial status of process to -1, meaning process has not arrived
        // yet
        jobs[i].status = -1;
        // Set initial completion time of process to -10, meaning process has
        // not completed yet
        jobs[i].comp_time = -10;
    }
    printf("Please input your desired time quantum: \n");
    scanf("%lf", &tQ);

    // Initiliase elapsedTime to track CPU Time
    double elapsedTime = 0;
    // Initialise schRunning to tell if scheduler should run
    bool schRunning = true;
    // Intiliase procAlloc to track if process has been allocated to the CPU
    bool procAlloc = false;

    while (schRunning) {
        for (int i = 0; i < sizeof(jobs) / sizeof(jobs[0]); i++) {
            // If Process has not arrived yet
            if (jobs[i].status == -1) {
                if (jobs[i].arr_time <= elapsedTime) {
					// Set status = 0, indicating process has arrived
					jobs[i].status = 0;
					// If exec_time is less than or equals to quantum
					if (jobs[i].exe_time <= tQ) {
						// If Ready queue is empty
						if (rQHead == NULL) {
							// if CPU IDLE means no next process to be executed
							if (nextProc == NULL) {
                                //Increment CPU time
                                elapsedTime += jobs[i].exe_time;
                                printf("DEBUG: Elapsed Time %f\n", elapsedTime);

                                //Just some code to help with printing gantt chart
                                ganttArr[arrInxCt] = jobs[i].id;
                                ganttArr[arrInxCt + 1] = jobs[i].exe_time;
                                ganttArr[arrInxCt + 2] = elapsedTime;
                                arrInxCt += 3;

                                //Update exec_time of process
                                jobs[i].exe_time -= jobs[i].exe_time;
                                //Update completion time of process
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
                                    printf("DEBUG: Elapsed Time %f\n", elapsedTime);

                                    //Just some code to help with printing gantt chart
                                    ganttArr[arrInxCt] = jobs[i].id;
                                    ganttArr[arrInxCt + 1] = tQ;
                                    ganttArr[arrInxCt + 2] = elapsedTime;
                                    arrInxCt += 3;

                                    jobs[i].exe_time -= tQ;
                                } else if (jobs[i].exe_time < tQ) {
                                    elapsedTime += jobs[i].exe_time;

                                    //Just some code to help with printing gantt chart
                                    ganttArr[arrInxCt] = jobs[i].id;
                                    ganttArr[arrInxCt + 1] = jobs[i].exe_time;
                                    ganttArr[arrInxCt + 2] = elapsedTime;
                                    arrInxCt += 3;

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
					//Set next process as first process in ready queue
					nextProc = rQHead;
				}
			}
		}

		// Initialise remProc to track whether nextProc should be removed
		bool remProc = false;
		// Intialise temp pointer to track the process to be removed from ready
		// queue
		Proc_Node *temp = NULL;

		if (procAlloc) {
			if (rQHead != NULL) {
				// If Ready Queue still has elements but next_process is NULL
				// then set next_process to head
				if (nextProc == NULL) {
					nextProc = rQHead;
				}
				// Allocate CPU to next_process in queue, up to time quantum
				if (nextProc->proc_data.exe_time < tQ) {
                    procAlloc = true;
                    elapsedTime += nextProc->proc_data.exe_time;

                    //Just some code to help with printing gantt chart
                    ganttArr[arrInxCt] = nextProc->proc_data.id;
                    ganttArr[arrInxCt + 1] = nextProc->proc_data.exe_time;
                    ganttArr[arrInxCt + 2] = elapsedTime;
                    arrInxCt += 3;

                    nextProc->proc_data.exe_time -= nextProc->proc_data.exe_time;
                } else if (nextProc->proc_data.exe_time >= tQ) {
                    procAlloc = true;
                    elapsedTime += tQ;

                    //Just some code to help with printing gantt chart
                    ganttArr[arrInxCt] = nextProc->proc_data.id;
                    ganttArr[arrInxCt + 1] = tQ;
                    ganttArr[arrInxCt + 2] = elapsedTime;
                    arrInxCt += 3;

                    nextProc->proc_data.exe_time -= tQ;
                }

				// If Process has completed execution
				if (nextProc->proc_data.exe_time <= 0) {
					// Set completion time of process
					nextProc->proc_data.comp_time = elapsedTime;
					temp = nextProc;
					// Assigning back to the process array
					jobs[nextProc->proc_data.id - 1] = nextProc->proc_data;
					remProc = true;
				}
				// Set the next_process to be executed
				nextProc = nextProc->next;

                // Remove process if it is flagged
                if (remProc) {
                    remProc = false;
                    deQueueProcNoLL(temp->proc_data.id, &rQHead);
                }
            } else {
                schRunning = false;
            }
        }
        displayQueue(&rQHead);
        printf("Current CPU time %f\n", elapsedTime);
    }

	printf("Final Times\n");

	// Initialise variables for process turnaround time, waiting times, and
	// average turnaround and waiting times calculation
	double taTime = 0, waitTime = 0, taSum = 0, waitSum = 0;

	// Print processes, their turnaround and waiting times
	for (int z = 0; z < sizeof(jobs) / sizeof(jobs[0]); z++) {
		printf("Process %d\n", jobs[z].id);
		taTime = jobs[z].comp_time - jobs[z].arr_time;
		printf("Turnaround time %.2f\n", taTime);
        waitTime = taTime - jobs[z].bst_time;
        printf("Waiting time %.2f\n", waitTime);
        taSum += taTime;
        waitSum += waitTime;
    }

    // Print average turnaround and waiting times for all processes
    printf("Average Turnaround Time %.2f\n", taSum / numProc);
    printf("Average Waiting Time %.2f\n", waitSum / numProc);

    //To print out the gantt chart, mostly for report and debugging purposes
    printGantt(ganttArr, arrInxCt);

    //Calculate total time taken for program execution
    clock_t end = clock();
    double progTime = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("Program Exec Time: %f\n", progTime);
    return 0;
}
