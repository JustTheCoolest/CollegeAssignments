#include "computer_api.cpp"
#include <iostream>
// #include "../../ReallyUseful/Cpp/StdioOperations.cpp"
// Flag: Implement modules in header files
using namespace std;

constexpr int number_of_types_of_resources = 4;

void add_processes(Computer &computer){
    int total_requested_resources[4][4] = {
        {3, 2, 1, 1},
        {1, 2, 0, 2},
        {3, 2, 1, 0},
        {2, 1, 0, 1}
    };
    Process *processes[4];
    for(int i=0; i<4; i++){
        processes[i] = computer.newProcess("P"+std::to_string(i), total_requested_resources[i]);
        cout << "Adding process " << processes[i]->name << " with total request ";
        for(int j=0; j<4; j++){
            cout << total_requested_resources[i][j] << " ";
        }
        cout << endl;
    }
    int requests[4][4] = {
        {2, 0, 1, 1},
        {1, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 1}
    };
    for(int i=0; i<4; i++){
        computer.request(processes[i], requests[i]);
        cout << "Need of process " << processes[i]->name << " is ";
        for(int j=0; j<4; j++){
            cout << processes[i]->need[j] << " ";
        }
        cout << endl;
    }
    cout << "Available resources are ";
    for(int i=0; i<4; i++){
        cout << computer.available_resources[i] << " ";
    }
    cout << endl;
}

int main(){
    int choice;
    cout << "1. Safe state detection\n2. Sequence detection\n3. Resource allocation problem in question\n";
    cin >> choice;
    switch(choice){
        case 1: {
            cout << "Enter number of types of resources: ";
            cin >> choice;
            const int number_of_types_of_resources = choice;
            int maximum_resources[number_of_types_of_resources];
            for(int i=0; i<number_of_types_of_resources; ++i){
                cout << "Enter maximum number of resources of type " << i+1 << ": ";
                cin >> maximum_resources[i];
            }
            Computer computer(number_of_types_of_resources, maximum_resources);
            int n;
            cout << "Enter number of processes: ";
            cin >> n;
            Process *processes[n];
            Process *process;
            bool flag = false;
            for(int i=0; i<n; ++i){
                int total_request[number_of_types_of_resources];
                cout << "Enter total request of process " << i+1 << ": " << endl;
                getInputs(number_of_types_of_resources, total_request);
                processes[i] = computer.newProcess("P"+std::to_string(i), total_request);
                cout << "Enter currently allocated resources of process " << i+1 << ": " << endl;
                int allocated[number_of_types_of_resources];
                getInputs(number_of_types_of_resources, allocated);
                switch(computer.request(processes[i], allocated)){
                    case -3:
                        cout << "Safety broken" << endl;
                        flag = true;
                        break;
                    case -2:
                        cout << "More than declared max was allocated to process" << endl;
                        flag = true;
                        break;
                    case -1:
                        cout << "More than system available was allocated to process" << endl;
                        flag = true;
                        break;
                }
                if(flag){
                    break;
                }
            }
            if(!flag){
                cout << "Safe" << endl;
            }
            break;
        }
        case 3: {
            int maximum_resources[number_of_types_of_resources] = {10, 6, 6, 4};
            Computer Doraemon(number_of_types_of_resources, maximum_resources);
            add_processes(Doraemon);
            cout << "Available resources at t0: ";
            printArray<int>(" ", number_of_types_of_resources, Doraemon.available_resources);
            cout << "Process running at t0: " << Doraemon.runStep()->name << endl;
            cout << "Available resources at t1: ";
            printArray<int>(" ", number_of_types_of_resources, Doraemon.available_resources);
            cout << "Requesting <1 1 0> for P0 at t1..." << endl;
            if(Doraemon.request(Doraemon.processes[0], new int[4]{1, 1, 0, 0})==0){
                cout << "Request granted" << endl;
            }
            else{
                cout << "Request not granted" << endl;
            }
            cout << "Safe sequence from t2 to end: ";
            Doraemon.findSafeSequence();
            // cout << "*" << Doraemon.processes[0]->name << endl;
            // cout << "*" << Doraemon.processes[1]->name << endl;
        }
    }
}