#include <stdio.h>

struct Process {
    int processId;
    int burstTime;
    int priority;
    int waitingTime;
    int turnaroundTime;
};

int main() {
    int n, totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Declare an array of processes
    struct Process processes[n];

    printf("Enter Burst Time and Priority:\n");

    // User Input Burst Time, Priority, and alloting Process Id.
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d %d", &processes[i].burstTime, &processes[i].priority);
        processes[i].processId = i + 1;
    }

    // Sorting processes according to their Priority using Selection Sort
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (processes[j].priority < processes[minIndex].priority) {
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
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
        totalWaitingTime += processes[i].waitingTime;
    }

    printf("P\tBurstTime\tPriority\tWaitingTime\tTurnAroundTime\n");

    // Calculation of Turn Around Time and printing the data.
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].burstTime + processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processId,
               processes[i].burstTime, processes[i].priority, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    float avgWaitingTime = (float)totalWaitingTime / n;
    float avgTurnaroundTime = (float)totalTurnaroundTime / n;

    printf("Average Waiting Time= %f\n", avgWaitingTime);
    printf("Average Turnaround Time= %f\n", avgTurnaroundTime);

    return 0;
}
