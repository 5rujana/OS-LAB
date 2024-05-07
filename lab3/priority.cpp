//priority scheduling
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

// Structure to represent a process
struct Process
{
    int id;                 // Process ID
    int arrival_time;       // Arrival time of the process
    int burst_time;         // Burst time of the process
    int priority;           // Priority of the process
    int completion_time;    // Time at which the process completes execution
    int turnaround_time;    // Turnaround time of the process
    int waiting_time;       // Waiting time of the process
    int remaining_time;     // Remaining time to complete the process
    bool completed;         // Flag to indicate if the process has completed
};

int main()
{
    int n, total_time = 0, highest = 0;
    float avg_waiting_time = 0, avg_turnaround_time = 0;

    // Get the number of processes from the user
    cout << "Enter the number of processes: ";
    cin >> n;

    // Create a vector to store the processes
    vector<Process> processes(n);

    // Input arrival time, burst time, and priority for each process
    for (int i = 0; i < n; i++)
    {
        cout << "Enter arrival time, burst time, and priority for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time >> processes[i].priority;
        processes[i].id = i + 1;
        processes[i].completed = false;
        total_time += processes[i].burst_time;
    }

    int current_time = 0, completed_processes = 0;

    // Process scheduling loop
    while (completed_processes < n)
    {
        int max_priority = -1;

        // Find the process with the highest priority among the arrived processes
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= current_time && processes[i].priority > max_priority && !processes[i].completed)
            {
                highest = i;
                max_priority = processes[i].priority;
            }
        }

        // Update completion time and remaining time for the selected process
        if (processes[highest].burst_time == processes[highest].remaining_time)
            processes[highest].completion_time = current_time;

        processes[highest].remaining_time--;
        current_time++;

        // Mark the process as completed if it has finished executing
        if (processes[highest].remaining_time == 0)
        {
            processes[highest].completed = true;
            completed_processes++;
            processes[highest].turnaround_time = current_time - processes[highest].arrival_time;
            processes[highest].waiting_time = processes[highest].turnaround_time - processes[highest].burst_time;
            avg_waiting_time += processes[highest].waiting_time;
            avg_turnaround_time += processes[highest].turnaround_time;
        }
    }

    // Calculate average waiting time and average turnaround time
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    cout << "Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++)
    {
        cout << processes[i].id << "\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" << processes[i].priority << "\t\t" << processes[i].completion_time << "\t\t" << processes[i].turnaround_time << "\t\t" << processes[i].waiting_time << endl;
    }
    cout << "Average Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
    return 0;
}