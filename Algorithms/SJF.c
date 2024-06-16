#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
} Process;

void calculate_average_waiting_time(Process processes[], int n, float *average_waiting_time) {
    int total_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
    }
    *average_waiting_time = (float)total_waiting_time / n;
}

void SJF(Process processes[], int n) {
    int completed = 0, current_time = 0, min_index;
    int *is_completed = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;
    }
    while (completed != n) {
        min_index = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && is_completed[i] == 0) {
                if (min_index == -1 || processes[i].burst_time < processes[min_index].burst_time) {
                    min_index = i;
                }
            }
        }
        if (min_index != -1) {
            processes[min_index].waiting_time = current_time - processes[min_index].arrival_time;
            current_time += processes[min_index].burst_time;
            processes[min_index].turnaround_time = processes[min_index].waiting_time + processes[min_index].burst_time;
            is_completed[min_index] = 1;
            completed++;
        } else {
            current_time++;
        }
    }
    free(is_completed);
}


void print_processes(Process processes[], int n) {
    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t\t%d\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].waiting_time,
               processes[i].turnaround_time);
    }
}

int main() {
    Process processes[] = {
        {1, 0, 10, 0, 0, 0},
        {2, 6, 8, 0, 0, 0},
        {3, 7, 4, 0, 0, 0},
        {4, 9, 5, 0, 0, 0},
    };
    int n = sizeof(processes) / sizeof(processes[0]);
    float average_waiting_time;

    printf("SJF Scheduling:\n");
    SJF(processes, n);
    print_processes(processes, n);
    calculate_average_waiting_time(processes, n, &average_waiting_time);
    printf("average : %.2f\n\n", average_waiting_time);

    return 0;
}