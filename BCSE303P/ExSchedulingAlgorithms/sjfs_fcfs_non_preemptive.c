#include <stdio.h>
#include <stddef.h>

struct process{
    int id;
    int start_time;
    int burst_time;
    int status;
} processes_to_simulate[] = {{0, 0, 5, 0}, {1, 0, 7, 0}, {2, 3, 1, 0}, {3, 3, 9, 0}};

const int number_of_processes = 4;

int clock_time = 0;

int compare(struct process *p1, struct process *p2, int clock_time){
    if(p1->burst_time < p2->burst_time){
        return -1;
    }
    else if(p1->burst_time > p2->burst_time){
        return +1;
    }
    else if(p1->start_time < p2->start_time){
        return -1;
    }
    else if(p1->start_time > p2->start_time){
        return +1;
    }
    return 0;
}

struct process *find_best(){
    struct process *best = NULL;
    unsigned int closest_uncompleted_process_start_time = 0;
    for(int i=0; i<number_of_processes; ++i){
        struct process *process_in_current_iteration = &processes_to_simulate[i];
        if(process_in_current_iteration->status == 1){
            continue;
        }
        if(best==NULL && process_in_current_iteration->start_time <= clock_time){
            int first_future_process = closest_uncompleted_process_start_time==0;
            int closer_future_process = process_in_current_iteration->start_time < closest_uncompleted_process_start_time;
            if(first_future_process || closer_future_process){
                closest_uncompleted_process_start_time = process_in_current_iteration->start_time;
            }
            best = process_in_current_iteration;
            continue;
        }
        if(process_in_current_iteration->burst_time < best->burst_time){
            best = process_in_current_iteration;
            continue;
        }
        int equally_long_burst_time = process_in_current_iteration->burst_time == best->burst_time;
        int arrived_earlier = process_in_current_iteration->start_time < best->start_time;
        if(equally_long_burst_time && arrived_earlier){
            best = process_in_current_iteration;
        }
    }
    if(best==NULL){
        if(closest_uncompleted_process_start_time==0){
            return NULL;
        }
        printf("Waiting for a process to arrive...\n");
        clock_time += closest_uncompleted_process_start_time;
        best = find_best();
    }
    return best;
}

void scheduler_simulator(){
    struct process *best = find_best();
    while(best != NULL){
        printf("Process %d started at %d\n", best->id, clock_time);
        clock_time += best->burst_time;
        printf("Process %d finished at %d\n", best->id, clock_time);
        best->status = 1;
        best = find_best();
    }
}

int main(){
    scheduler_simulator();
    printf("Simulation finished.\n");
}