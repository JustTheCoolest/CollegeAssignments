#include <forward_list>
#include <iostream>

int first_fit_from_start(const int process, std::forward_list<int>& memory_list) {
    int index = -1;
    for (auto memory_hole : memory_list){
        ++index;
        if (memory_hole < process){
            continue;
        }
        memory_hole -= process;
        return index;
    }
    return -1;
}

// Task: Finish this using std::distance
// Task: Figure out restructuring instead of static variables, and then to standardise the interface as per changes
// int first_fit_from_previous(const int process, std::forward_list<int>& memory_list) {
//     static auto iterator = memory_list.begin();
//     static int index = 0;
//     auto end_point = iterator;
//     while(index = (index+1)%memory_list.size(), ++iterator, iterator != end_point){
//         if(iterator == memory_list.end()){
//             iterator = memory_list.begin();
//         }
//         if (*iterator < process){
//             continue;
//         }
//         *iterator -= process;
//         return index;
//     };
//     return -1;
// }

void allocate_processes(int (*allocate_process)(const int, std::forward_list<int>&), std::forward_list<int>& process_list, std::forward_list<int>& memory_list) {
    for(auto process : process_list){
        int index_allocated = allocate_process(process, memory_list);
        if (index_allocated == -1){
            std::cout << "Process " << process << " could not be allocated." << std::endl;
        } else {
            std::cout << "Process " << process << " allocated at " << index_allocated << std::endl;
        }
    }
}

int main() {
    std::forward_list<int> memory_list = {200, 400, 600, 500, 300, 250};
    std::forward_list<int> process_list = {357, 210, 468, 491};
    allocate_processes(first_fit_from_start, process_list, memory_list);
}
