#include <string>
#include <iostream> // Flag: Move prints completely to interface
#include "../../ReallyUseful/Cpp/ArrayOperations.cpp"
#include "../../ReallyUseful/Cpp/IOStreamOperations.cpp"
using namespace std;

class Computer;
class Process;

class Process{
    private:
    // Flag: Make these const
    int number_of_types_of_resources;
    int *total_request; 
    Computer *computer;
    public:
    string name; // Flag: Make these private
    bool terminated = 0;
    int *need;
    Process(int number_of_types_of_resources, string name, int total_request[], Computer *computer):
        // Flag: Make this private
        name(name), computer(computer), number_of_types_of_resources(number_of_types_of_resources)
    {
        this->total_request = new int[number_of_types_of_resources];
        this->need = new int[number_of_types_of_resources];
        for(int i=0; i<number_of_types_of_resources; ++i){
            this->total_request[i] = total_request[i];
            need[i] = total_request[i];
        }
        // cout << "Creating process " << name << " with total request ";
        // printArray<int>(" ", number_of_types_of_resources, total_request);
        showNeed();
    }
    Process(Computer *new_computer, Process &original){
        number_of_types_of_resources = original.number_of_types_of_resources;
        total_request = new int[number_of_types_of_resources];
        copyArray<int>(number_of_types_of_resources, total_request, original.total_request);
        computer = new_computer;
        name = original.name;
        terminated = original.terminated;
        need = new int[number_of_types_of_resources];
        copyArray<int>(number_of_types_of_resources, need, original.need);
    }
    void grant(int request[], bool print_flag = true){
        bool flag = true;
        for(int i=0; i<number_of_types_of_resources; ++i){
            need[i] -= request[i];
            if(need[i] != 0){
                flag = false;
            }
        }
        terminated = flag;
        if(print_flag) showNeed();
    }
    // void setNeed(int need[]){
    //     for(int i=0; i<number_of_types_of_resources; ++i){
    //         this->need[i] = need[i];
    //     }
    // }
    void showNeed(){
        cout << "Need of process " << name << " is ";
        printArray<int>(" ", number_of_types_of_resources, need);
    }
    friend class Computer;
};

class BankersAlgorithm{
    public:
    Process **findSafeSequence(int number_of_processses, Process *processes[],  Process* result[] = nullptr,  bool filter_flag = false){
        // Task: Improve performance by using stacks instead of recursion
        // Task: Instead of iterating through all processes, sorting them beforehand will make it easier to identify safe sequence and to accomodate changes
        if(number_of_processses == 0){
            return result;
        }
        if(filter_flag){
            filterArray<Process*>(number_of_processses, processes, [](Process *process){return !process->terminated;});
        }
        if(result == nullptr){
            result = new Process*[number_of_processses];
        }
        Process* remaining_processes[number_of_processses-1];
        copyArray<Process*>(number_of_processses-1, remaining_processes, processes+1);
        for(int i=0; i<number_of_processses; ++i){
            Process* return_value = findSafeSequence(number_of_processses-1, processes, result+1, true);
            if(findSafeSequence())
            remaining_processes[i] = processes[i];
        }
    }
};

class Computer{
    private:
    int number_of_types_of_resources;
    int process_pointer = 0;
    public:
    int *available_resources; // Flag: Make these private
    Process *processes[100]; // Flag: Make this dynamic
    int request(Process *process, int request[], bool print_flag = true){
        // Better UX (?): Call request from process class and then request to computer from there, while not creating circular dependency issues
        for(int i = 0; i < number_of_types_of_resources; ++i){
            if(request[i] > available_resources[i]){ 
                return -1;
            }
            else if(request[i] > process->need[i]){
                return -2;
            }
        }
        for(int i = 0; i < number_of_types_of_resources; ++i){
            available_resources[i] -= request[i]; 
        }
        // cout << "Process " << process->name << " requested ";
        // for(int i = 0; i < number_of_types_of_resources; ++i){
        //     cout << available_resources[i] << " ";
        // }
        process->grant(request, print_flag);
        // if(!isSafe()){
        if(true){ // TRAP: Re-enable
            // cout << "Process " << process->name << " is not safe" << endl;
            // for(int i = 0; i < number_of_types_of_resources; ++i){
            //     available_resources[i] += request[i]; 
            // }
            // addEach<int>(number_of_types_of_resources, available_resources, request);
            // multiplyEach<int>(number_of_types_of_resources, request, -1);
            // process->grant(request);
            return -3;
        }
        return 0;
    }
    Computer(int number_of_types_of_resources, int total_resources[]): number_of_types_of_resources(number_of_types_of_resources){ 
        cout << "Creating computer with resources: ";
        available_resources = new int[number_of_types_of_resources];
        for(int i=0; i<number_of_types_of_resources; ++i){
            this->available_resources[i] = total_resources[i]; 
            cout << available_resources[i] << " ";
        }
        cout << endl;
    }
    Computer(Computer &original){
        number_of_types_of_resources = original.number_of_types_of_resources;
        available_resources = new int[number_of_types_of_resources];
        copyArray<int>(number_of_types_of_resources, available_resources, original.available_resources);
        process_pointer = original.process_pointer;
        for(int i=0; i<process_pointer; ++i){
            processes[i] = new Process(this, *original.processes[i]);
        }
    }
    Process* newProcess(string name, int total_request[]){
        Process *process = new Process(number_of_types_of_resources, name, total_request, this);
        processes[process_pointer++] = process;
        // cout << "Number of processes: " << process_pointer << endl;
        return process;
    }
    bool isSafe(){
        Computer ghost = *this;
        ghost.findSafeSequence(false);
        // findSafeSequence(false);
        // return ghost.isFree();
        return true;
    }
    Process *runStep(bool print_flag = true){
        int copy = process_pointer;
        // cout << "number of processes: " << copy << endl;
        while(--copy>-1){
            //cout << "Checking process " << processes[copy]->name << endl;
            if(!processes[copy]->terminated && request(processes[copy], processes[copy]->need, print_flag) == 0){
                // cout << "Process " << processes[copy]->name << " terminated" << endl;
                for(int i=0; i<number_of_types_of_resources; ++i){
                    available_resources[i] += processes[copy]->total_request[i];
                }
                return processes[copy];
            }
        }
        return nullptr;
    }
    void findSafeSequence(bool print_flag = true){
        // Task: Return instead of printing
        Process *process;
        while((process=runStep(print_flag))!=nullptr){
            if(print_flag) std::cout << process->name << " ";
            // for(int i=0; i<number_of_types_of_resources; ++i){
            //     cout << available_resources[i] << " "; 
            // }
            // cout << endl;
        }
        if(print_flag) cout << endl;
    }
    bool isFree(){
        for(int i=0; i<process_pointer; ++i){
            if(!processes[i]->terminated){
                return false;
            }
        }
        return true;
    }
    friend class Process;
    // Flag: Add a destructor to delete all pointers
    ~Computer(){
        // delete[] available_resources;
        // freeArray<Process*>(process_pointer, processes);
    }
};