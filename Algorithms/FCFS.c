#include <stdio.h>

#define NUM_PROCESSES 4

typedef struct
{

    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
} Process;

void FCFS(Process processes[], int num_processes){

    for(int i=0;i<num_processes;i++){
        for(int j=0; j < num_processes -i-1 ;j++){
            if(processes[j].arrival_time > processes[j+1].arrival_time){
                Process temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
        }
    }



};

void calculate_waiting_time(Process processes[], int num_processes){

    //processes[0].waiting_time = 0;

    for (int i = 0; i < num_processes; i++) {
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

    }

}

void calculate_turnaround_time(Process processes[], int num_processes){

    processes[0].completion_time = processes[0].burst_time;
    
    for(int i=1; i< num_processes ; i++){

            if(processes[i-1].completion_time > processes[i].arrival_time){
            
            processes[i].completion_time = processes[i-1].completion_time + processes[i].burst_time;
            }
            else{
            processes[i].completion_time = processes[i].arrival_time + processes[i].burst_time;
            }
    }

    for(int i=0; i< num_processes; i++){
                processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
    }



}

void print_processes(Process processes[], int num_processes){

    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(int i=0; i < num_processes ; i++){
        printf("%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n",
            processes[i].pid,
            processes[i].arrival_time,
            processes[i].burst_time,
            processes[i].waiting_time,
            processes[i].turnaround_time);
    }

}

double calculate_average_waiting_time(Process processes[], int num_processes){

    double total_waiting_time=0;
    double average_waiting_time = 0 ;
    for(int i=0; i< num_processes ; i++){
        total_waiting_time += processes[i].waiting_time;
    }

    average_waiting_time = total_waiting_time/num_processes;
    //printf("total wait : %d",total_waiting_time);
    printf("average : %.2f",average_waiting_time);

    return average_waiting_time;

}


int main(){
    Process processes[NUM_PROCESSES] = {
        {1, 0, 10, 0, 0, 0},
        {2, 6, 8, 0, 0, 0},
        {3, 7, 4, 0, 0, 0},
        {4, 9, 5, 0, 0, 0},

   // pid,arrival_time ,burst_time, waiting_time, turnaround_time
    };

    printf("/////////////////////// \n FCFS Scheduling:\n");
    FCFS(processes, NUM_PROCESSES);
    calculate_turnaround_time(processes, NUM_PROCESSES);
    calculate_waiting_time(processes, NUM_PROCESSES);
    print_processes(processes, NUM_PROCESSES);
    calculate_average_waiting_time(processes,NUM_PROCESSES);

    return 0;
}