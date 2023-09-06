#include <stdio.h>
#include <assert.h>
#include <math.h>
using namespace std;

struct process{
    unsigned int id;
    unsigned int start_time;
    unsigned int burst_time;
    unsigned int remaining_time;
    unsigned int priority;
};

class RoundRobinReadyProcesses{
    const unsigned int time_quantum;
    LinkedCircle<process*> dataTraverser();
    RoundRobinReadyProcesses(const unsigned int time_quantum): time_quantum(time_quantum){}
    void catchNewProcesses(){
        for 
        dataTraverser.addInFront();
    }
    process* nextInRound(){
        return dataTraverser.next();
    }
    void terminatePreviousProcess(){
        dataTraverser.removePrevious();
    }
} round_robin_ready_processes;

process* nextInRound(
        unsigned clock_time, 
        const unsigned time_quantum,
        const unsigned number_of_processses, 
        process* const processes[]
    ){
    static LinkedCircle<process*> dataTraverser();
    if(dataTraverser.peekPrevious()->remaining_time<=0){
        dataTraverser.removePrevious();
    }
    unsigned previous_clock_time = clock_time - time_quantum;
    for(; clock_time > previous_clock_time; --clock_time){
        for(int i=0; i<number_of_processses; ++i){
            process* process_at_iteration = processes[i];
            if(process_at_iteration->start_time == clock_time){
                dataTraverser.addInFront();
            }
        }
    }
    return dataTraverser.next();
}

int updatedCheckpoint(int nearest_new_process_entry_time, struct process const * const process_in_current_iteration, int const clock_time){
    int process_in_future = process_in_current_iteration->start_time > clock_time;
    int younger_process = process_in_current_iteration->start_time < nearest_new_process_entry_time;
    if(process_in_future && younger_process){ // When process enters ready queue, the scheduler checks to see if preemption is needed.
        nearest_new_process_entry_time = process_in_current_iteration->start_time;
    }
    return nearest_new_process_entry_time;
}

void test_updatedCheckpoint(){
    struct process processes_to_simulate[] = {{1, 0, 15, 15, 3}, {2, 2, 2, 2, 1}, {3, 4, 5, 5, 4}, {4, 7, 1, 1, 5}, {5, 2, 7, 7, 2}};
    const int number_of_processes = 5;
    int clock_time = 0;
    unsigned int closest_uncompleted_process_start_time = numeric_limits<unsigned int>::max();
    // Assertions
    int indices[] = {3, 2, 1, 0, 4};
    int results[] = {7, 4, 2, 2, 2};
    for(int i=0; i<number_of_processes; ++i){
        int index = indices[i];
        int result = results[i];
        closest_uncompleted_process_start_time = updatedCheckpoint(
            closest_uncompleted_process_start_time, 
            &processes_to_simulate[index], 
            clock_time
        );
        assert(closest_uncompleted_process_start_time == result);
    }
}

unsigned int rankShort(struct process const * const process_given){
    return process_given->remaining_time;
}

unsigned int rankPriority(struct process const * const process_given){
    return process_given->priority;
}

struct process *find_best_by_ranking(
        unsigned int rank(struct process const * const),
        int const number_of_processes, 
        struct process const processes_to_simulate[], 
        int &clock_time, 
        unsigned int &closest_uncompleted_process_start_time
    ){
    struct process const *best = NULL;
    closest_uncompleted_process_start_time = numeric_limits<unsigned int>::max();
    for(int i=0; i<number_of_processes; ++i){
        struct process const * const process_in_current_iteration = &processes_to_simulate[i];
        closest_uncompleted_process_start_time = updatedCheckpoint(
            closest_uncompleted_process_start_time, 
            process_in_current_iteration, 
            clock_time
        );
        if(process_in_current_iteration->remaining_time == 0 || process_in_current_iteration->start_time > clock_time){
            continue;
        }
        if(best==NULL && process_in_current_iteration->start_time <= clock_time){
            best = process_in_current_iteration;
            continue;
        }
        if (rank(process_in_current_iteration) < rank(best)) {
            best = process_in_current_iteration;
            continue;
        }
        int equally_ranked = rank(process_in_current_iteration) == rank(best);
        int arrived_earlier = process_in_current_iteration->start_time < best->start_time;
        if (equally_ranked && arrived_earlier) {
            best = process_in_current_iteration;
        }
    }
    if(best==NULL){
        if(closest_uncompleted_process_start_time==numeric_limits<unsigned int>::max()){
            return NULL;
        }
        printf("Waiting for a process to arrive...\n");
        clock_time += closest_uncompleted_process_start_time;
        best = find_best_by_ranking(
            rank,
            number_of_processes, 
            processes_to_simulate, 
            clock_time, 
            closest_uncompleted_process_start_time
        );
    }
    return (struct process *)best;
}

// void test_find_best_psjf(){
//     int number_of_processes = 5;
//     struct process processes_to_simulate[] = {{1, 0, 15, 15, 3}, {2, 2, 2, 2, 1}, {3, 4, 5, 5, 4}, {4, 7, 1, 1, 5}, {5, 3, 7, 7, 2}};
//     int clock_time = 0;
//     unsigned int closest_uncompleted_process_start_time = 0;
//     struct process *best = find_best_by_ranking(
//         number_of_processes, 
//         processes_to_simulate, 
//         clock_time, 
//         closest_uncompleted_process_start_time
//     );
//     assert(best->id == 1);
//     clock_time += 5;
//     best = find_best_by_ranking(
//         number_of_processes, 
//         processes_to_simulate, 
//         clock_time, 
//         closest_uncompleted_process_start_time
//     );
//     assert(closest_uncompleted_process_start_time == 7);
// }

struct process* findShortest(
        int number_of_processes,
        struct process processes[],
        int &clock_time,
        unsigned int &nearest_new_process_entry_time
){
    return find_best_by_ranking(
        rankShort, 
        number_of_processes, 
        processes, 
        clock_time, 
        nearest_new_process_entry_time
    );
}

struct process* findPrior(
        int number_of_processes,
        struct process processes[],
        int &clock_time,
        unsigned int &nearest_new_process_entry_time
){
    return find_best_by_ranking(
        rankPriority, 
        number_of_processes, 
        processes, 
        clock_time, 
        nearest_new_process_entry_time
    );
}

process* findNextInRound(
    int number_of_processes,
    struct process processes[],
    int &clock_time,
    unsigned int &nearest_new_process_entry_time
){

}

void scheduler_driver(
        process* scheduler(int, struct process*, int&, unsigned int &), 
        int number_of_processes, 
        struct process processes_to_simulate[]
    ){
    int clock_time = 0;
    unsigned int closest_uncompleted_process_start_time;
    struct process *best;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    while(true){
        best = scheduler(
            number_of_processes, 
            processes_to_simulate,
            clock_time, 
            closest_uncompleted_process_start_time
        );
        if(best==NULL){
            break;
        }
        printf("Process %d started at %d\n", best->id, clock_time);
        int time_to_execute = min(best->remaining_time, closest_uncompleted_process_start_time - clock_time);
        clock_time += time_to_execute;
        best->remaining_time -= time_to_execute;
        if(best->remaining_time == 0){
            int turnaround_time = clock_time - best->start_time;
            int waiting_time = turnaround_time - best->burst_time;
            total_turnaround_time += turnaround_time;
            total_waiting_time += waiting_time;
            printf("Process %d finished at %d\n", best->id, clock_time);
        }
        else{
            printf("Process %d preempted at %d\n", best->id, clock_time);
        }
    }
    printf("Average turnaround time: %f\n", (float)total_turnaround_time/number_of_processes);
    printf("Average waiting time: %f\n", (float)total_waiting_time/number_of_processes);
}

void tests(){
    const int number_of_processes = 5;
    struct process processes_to_simulate[number_of_processes] = {{1, 0, 15, 15, 3}, {2, 2, 2, 2, 1}, {3, 4, 5, 5, 4}, {4, 7, 1, 1, 5}, {5, 3, 7, 7, 2}};
    scheduler_driver(findShortest, number_of_processes, processes_to_simulate);
    /* Answers (Not verified):
    Average turnaround time: 10.600000
    Average waiting time: 4.600000
    */
}

int main(){
    test_updatedCheckpoint();
    //test_find_best_psjf();
    //tests();
    for(int i=0; i<2; ++i){
        const int number_of_processes = 5;
        struct process processes_to_simulate[number_of_processes] = {
            {1, 0, 15, 15, 3}, {2, 2, 2, 2, 1}, {3, 4, 5, 5, 4}, {4, 7, 1, 1, 5}, {5, 3, 14, 14, 2}
        };
        switch(i){
            case 0:
            printf("Preemptive Shortest Job First Scheduler\n");
            scheduler_driver(findShortest, number_of_processes, processes_to_simulate);
            break;
            case 1:
            printf("Preemptive Priory first:\n");
            scheduler_driver(findPrior, number_of_processes, processes_to_simulate);
            break;
        }
        printf("\n");
    }
}