#include "computer_api.cpp"
#include <iostream>
using namespace std;

// constexpr int number_of_types_of_resources = 4;

// void add_processes(Computer<number_of_types_of_resources> &computer){
//     int total_requested_resources[4][4] = {
//         {3, 2, 1, 1},
//         {1, 2, 0, 2},
//         {3, 2, 1, 0},
//         {2, 1, 0, 1}
//     };
//     Process<number_of_types_of_resources> *processes[4];
//     for(int i=0; i<4; i++){
//         processes[i] = computer.newProcess("P"+std::to_string(i), total_requested_resources[i]);
//         cout << "Adding process " << processes[i]->name << " with total request ";
//         for(int j=0; j<4; j++){
//             cout << total_requested_resources[i][j] << " ";
//         }
//         cout << endl;
//     }
//     int requests[4][4] = {
//         {2, 0, 1, 1},
//         {1, 1, 0, 0},
//         {1, 0, 1, 0},
//         {0, 1, 0, 1}
//     };
//     for(int i=0; i<4; i++){
//         processes[i]->request(requests[i]);
//         cout << "Need of process " << processes[i]->name << " is ";
//         for(int j=0; j<4; j++){
//             cout << processes[i]->need[j] << " ";
//         }
//         cout << endl;
//     }
//     cout << "Available resources are ";
//     for(int i=0; i<4; i++){
//         cout << computer.available_resources[i] << " ";
//     }
//     cout << endl;
// }

// int Xmain(){
//     int maximum_resources[number_of_types_of_resources] = {10, 6, 6, 4};
//     Computer<number_of_types_of_resources> Doraemon(maximum_resources);
//     add_processes(Doraemon);
//     Process <number_of_types_of_resources> *process;
//     cout << "Safe sequence is: ";
//     while((process=Doraemon.runStep())!=nullptr){
//         std::cout << process->name << " ";
//         for(int i=0; i<number_of_types_of_resources; ++i){
//             // cout << Doraemon.available_resources[i] << " "; 
//         }
//         // cout << endl;
//     }
//     cout << endl;
//     // cout << "*" << Doraemon.processes[0]->name << endl;
//     // cout << "*" << Doraemon.processes[1]->name << endl;
// }

int main(){
    int choice;
    cout << "1. Safe state detection\n2. Sequence detection\n3. Resource allocation problem in question";
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

        }
    }
}