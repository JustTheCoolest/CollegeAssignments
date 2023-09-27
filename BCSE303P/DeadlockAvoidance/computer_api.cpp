#include <string>
#include <iostream> // Flag: Move prints completely to interface
#include "../../ReallyUseful/Cpp/ArrayOperations.cpp"
#include "../../ReallyUseful/Cpp/StdioOperations.cpp"
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
    }
    void grant(int request[]){
        bool flag = true;
        for(int i=0; i<number_of_types_of_resources; ++i){
            need[i] -= request[i];
            if(need[i] != 0){
                flag = false;
            }
        }
        terminated = flag;
    }
    // void setNeed(int need[]){
    //     for(int i=0; i<number_of_types_of_resources; ++i){
    //         this->need[i] = need[i];
    //     }
    // }
    friend class Computer;
};

class Computer{
    private:
    int number_of_types_of_resources;
    int process_pointer = 0;
    public:
    int *available_resources; // Flag: Make these private
    Process *processes[100]; // Flag: Make this dynamic
    int request(Process *process, int request[]){
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
        process->grant(request);
        if(!isSafe()){
            // cout << "Process " << process->name << " is not safe" << endl;
            for(int i = 0; i < number_of_types_of_resources; ++i){
                available_resources[i] += request[i]; 
            }
            allMultiply<int>(number_of_types_of_resources, request, -1);
            process->grant(request);
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
    Process* newProcess(string name, int total_request[]){
        Process *process = new Process(number_of_types_of_resources, name, total_request, this);
        processes[process_pointer++] = process;
        // cout << "Number of processes: " << process_pointer << endl;
        return process;
    }
    bool isSafe(){
        int copy = process_pointer;
        while(--copy>-1){
            for(int i=0; i<number_of_types_of_resources; ++i){
                if(processes[copy]->need[i] > available_resources[i]){ 
                    return false;
                }
            }
        }
        return true;
    }
    Process *runStep(){
        int copy = process_pointer;
        // cout << "number of processes: " << copy << endl;
        while(--copy>-1){
            //cout << "Checking process " << processes[copy]->name << endl;
            if(!processes[copy]->terminated && request(processes[copy], processes[copy]->need) == 0){
                // cout << "Process " << processes[copy]->name << " terminated" << endl;
                for(int i=0; i<number_of_types_of_resources; ++i){
                    available_resources[i] += processes[copy]->total_request[i];
                }
                return processes[copy];
            }
        }
        return nullptr;
    }
    void findSafeSequence(){
        Process *process;
        while((process=runStep())!=nullptr){
            std::cout << process->name << " ";
            // for(int i=0; i<number_of_types_of_resources; ++i){
            //     cout << available_resources[i] << " "; 
            // }
            // cout << endl;
        }
        cout << endl;
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
    // Flag: Add a destructor to delete all processes
    ~Computer(){
        delete[] available_resources;
        freeArray<Process*>(process_pointer, processes);
    }
};