#include <stdio.h>

struct Process {
    int processId;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
};

int main() {
    int n, totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Declare an array of processes
    struct Process processes[n];

    printf("Enter Burst Time:\n");

    // User Input Burst Time and alloting Process Id.
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].processId = i + 1;
    }


    // Sorting processes according to their Burst Time using Selection Sort
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (processes[j].burstTime < processes[minIndex].burstTime) {
                minIndex = j;
            }
        }

        // Swap the processes
        struct Process temp = processes[i];
        processes[i] = processes[minIndex];
        processes[minIndex] = temp;
    }

    processes[0].waitingTime = 0;

    // Calculation of Waiting Times
    for (int i = 1; i < n; i++) {
        processes[i].waitingTime = 0;
        for (int j = 0; j < i; j++) {
            processes[i].waitingTime += processes[j].burstTime;
        }
        totalWaitingTime += processes[i].waitingTime;
    }

    printf("P\t\tBurstTime\tWaitingTime\tTurnAroundTime\n");

    // Calculation of Turn Around Time and printing the data.
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].burstTime + processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
        printf("P%d\t\t%d\t\t%d\t\t%d\n", processes[i].processId,
               processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    float avgWaitingTime = (float)totalWaitingTime / n;
    float avgTurnaroundTime = (float)totalTurnaroundTime / n;

    printf("Average Waiting Time= %f\n", avgWaitingTime);
    printf("Average Turnaround Time= %f\n", avgTurnaroundTime);

    return 0;
}
