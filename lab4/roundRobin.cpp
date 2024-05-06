#include <iostream>
using namespace std;

// Structure to represent a process
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

int main() {
    int n, time_quantum;
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    
    // Input the number of processes
    cout << "Enter the number of processes: ";
    cin >> n;
    
    // Create an array of processes
    Process processes[n];
    for (int i = 0; i < n; i++) {
        // Input arrival time and burst time for each process
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].id = i + 1;
    }
    
    // Input the time quantum for round robin
    cout << "Enter the time quantum: ";
    cin >> time_quantum;
    
    int remaining_processes = n;
    int current_time = 0;
    int i = 0;
    
    // Output table headers
    cout << "\n\nProcess\t\tBurst Time\t\tTurnaround Time\t\tWaiting Time\n\n";
    while (remaining_processes > 0) {
        if (processes[i].remaining_time > 0) {
            // Execute the process for the time quantum
            if (processes[i].remaining_time <= time_quantum) {
                current_time += processes[i].remaining_time;
                processes[i].remaining_time = 0;
            } else {
                current_time += time_quantum;
                processes[i].remaining_time -= time_quantum;
            }

            // If process is completed, calculate turnaround and waiting time
            if (processes[i].remaining_time == 0) {
                remaining_processes--;
                processes[i].completion_time = current_time;
                processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                
                // Output process details
                cout << "P[" << processes[i].id << "]\t\t" << processes[i].burst_time << "\t\t" 
                     << processes[i].turnaround_time << "\t\t" << processes[i].waiting_time << endl;
                
                // Update average waiting and turnaround time
                avg_waiting_time += processes[i].waiting_time;
                avg_turnaround_time += processes[i].turnaround_time;
            }
        }
        // Move to the next process in a circular manner
        i = (i + 1) % n;
    }
    
    // Calculate and output average waiting and turnaround time
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    
    cout << "Average waiting time: " << avg_waiting_time << endl;
    cout << "Average turnaround time: " << avg_turnaround_time << endl;

    return 0;
}
