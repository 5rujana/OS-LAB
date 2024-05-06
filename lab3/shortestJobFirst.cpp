#include<bits/stdc++.h>
using namespace std;

struct Process {
    int processId;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
};

int main() {
    int n, totalWaitingTime = 0, totalTurnaroundTime = 0;

    cout<<"Enter number of processes: ";
    cin>>n;

    // Declare an array of processes
    struct Process processes[n];

    cout<<"Enter Burst Time:"<<endl;

    // User Input Burst Time and alloting Process Id.
    for (int i = 0; i < n; i++) {
        cout<<"P"<<i+1<<" : ";
        cin>>processes[i].burstTime;
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

    // Calculation of Turn Around Time 
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].burstTime + processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;

    }

    // printing the data.
    cout<<"P\tBurstTime\tPriority\tWaitingTime\tTurnAroundTime\n";
    for(int i = 0;i<n;i++){
        cout<<"P"<<processes[i].processId<<"\t\t"<<processes[i].burstTime<<"\t\t"<<processes[i].waitingTime<<"\t\t"<<processes[i].turnaroundTime<<endl;

    }

    float avgWaitingTime = (float)totalWaitingTime / n;
    float avgTurnaroundTime = (float)totalTurnaroundTime / n;

    cout<<"Average Waiting Time= " <<avgWaitingTime<<endl;
    cout<<"Average Turnaround Time= "<< avgTurnaroundTime<<endl;

    return 0;
}
