#include <iostream>
#include <vector>
#include <algorithm>
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
    bool completed;
};

int main() {
    int n, total_time = 0, shortest = 0;
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
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completed = false;
        total_time += processes[i].burst_time;
    }

    // Initialize variables for simulation
    int current_time = 0, completed_processes = 0;

    // Simulation loop
    while (completed_processes < n) {
        int min_remaining_time = total_time + 1;
        for (int i = 0; i < n; i++) {
            // Find the process with the shortest remaining time
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time < min_remaining_time && !processes[i].completed) {
                shortest = i;
                min_remaining_time = processes[i].remaining_time;
            }
        }

        // Update completion time, remaining time, and current time
        if (processes[shortest].remaining_time == processes[shortest].burst_time)
            processes[shortest].completion_time = current_time;

        processes[shortest].remaining_time--;
        current_time++;

        // Mark process as completed if it has finished executing
        if (processes[shortest].remaining_time == 0) {
            processes[shortest].completed = true;
            completed_processes++;
        }
    }

    // Calculate and print turnaround time and waiting time for each process
    cout << "\n\nProcess\t\tTurnaround Time\t\tWaiting Time\n\n";
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        avg_turnaround_time += processes[i].turnaround_time;
        avg_waiting_time += processes[i].waiting_time;
        cout << "P" << processes[i].id << "\t\t" << processes[i].turnaround_time << "\t\t\t" << processes[i].waiting_time << endl;
    }

    // Calculate and print average turnaround time and average waiting time
    avg_turnaround_time /= n;
    avg_waiting_time /= n;
    cout << "\nAverage Turnaround Time: " << avg_turnaround_time << endl;
    cout << "Average Waiting Time: " << avg_waiting_time << endl;

    return 0;
}
