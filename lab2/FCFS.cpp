//first come first serve
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent a process
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    bool completed;
};

int main() {
    int n, total_time = 0;
    float avg_waiting_time = 0, avg_turnaround_time = 0;

    // Input the number of processes
    cout << "Enter the number of processes: ";
    cin >> n;

    // Create a vector of processes
    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        // Input arrival time and burst time for each process
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].id = i + 1;
        processes[i].completed = false;
        total_time += processes[i].burst_time;
    }

    // Initialize variables for simulation
    int current_time = 0, completed_processes = 0;

    // Simulation loop
    while (completed_processes < n) {
        int next_process = -1;
        for (int i = 0; i < n; i++) {
            // Find the next process that has arrived and not completed
            if (processes[i].arrival_time <= current_time && !processes[i].completed) {
                next_process = i;
                break;
            }
        }

        if (next_process == -1) {
            // If no process is available, move time forward
            current_time++;
        } else {
            // Execute the next process
            processes[next_process].burst_time--;
            current_time++;

            // Update completion time and mark process as completed
            if (processes[next_process].burst_time == 0) {
                processes[next_process].completion_time = current_time;
                processes[next_process].completed = true;
                completed_processes++;
            }
        }
    }

    // Calculate turnaround time and waiting time for each process
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        avg_turnaround_time += processes[i].turnaround_time;
        avg_waiting_time += processes[i].waiting_time;
    }

    // Calculate average turnaround time and waiting time
    avg_turnaround_time /= n;
    avg_waiting_time /= n;

    // Output the results
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" << processes[i].completion_time << "\t\t" << processes[i].turnaround_time << "\t\t" << processes[i].waiting_time << endl;
    }
    cout << "Average Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
    return 0;
}