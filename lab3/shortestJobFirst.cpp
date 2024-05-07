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
    int remaining_time;     // Remaining time to complete the process
    int completion_time;    // Time at which the process completes execution
    int turnaround_time;    // Turnaround time of the process
    int waiting_time;       // Waiting time of the process
    bool completed;         // Flag to indicate if the process has completed
};

int main()
{
    int n, total_time = 0, shortest = 0;
    float avg_waiting_time = 0, avg_turnaround_time = 0;

    // Get the number of processes from the user
    cout << "Enter the number of processes: ";
    cin >> n;

    // Create a vector to store the processes
    vector<Process> processes(n);

    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++)
    {
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].id = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completed = false;
        total_time += processes[i].burst_time;
    }

    int current_time = 0, completed_processes = 0;

    // Process scheduling loop
    while (completed_processes < n)
    {
        int min_remaining_time = total_time + 1;

        // Find the process with the shortest remaining time among the arrived processes
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time < min_remaining_time && !processes[i].completed)
            {
                shortest = i;
                min_remaining_time = processes[i].remaining_time;
            }
        }

        // Update completion time and remaining time for the selected process
        if (processes[shortest].remaining_time == processes[shortest].burst_time)
            processes[shortest].completion_time = current_time;

        processes[shortest].remaining_time--;
        current_time++;

        // If the process completes execution, calculate its turnaround time and waiting time
        if (processes[shortest].remaining_time == 0)
        {
            processes[shortest].completed = true;
            processes[shortest].turnaround_time = current_time - processes[shortest].arrival_time;
            processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].burst_time;
            avg_waiting_time += processes[shortest].waiting_time;
            avg_turnaround_time += processes[shortest].turnaround_time;
            completed_processes++;
        }
    }

    // Calculate average waiting time and average turnaround time
    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    // Display process details
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++)
    {
        cout << processes[i].id << "\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" << processes[i].completion_time << "\t\t" << processes[i].turnaround_time << "\t\t" << processes[i].waiting_time << endl;
    }

    return 0;
}
