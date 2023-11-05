#include <forward_list>
#include <iostream>

int first_fit_from_start(const int process, std::forward_list<int>& memory_list) {
    int index = -1;
    for (auto memory_hole = memory_list.begin(); memory_hole != memory_list.end(); ++memory_hole){
        ++index;
        if (*memory_hole < process){
            continue;
        }
        *memory_hole -= process;
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

void printList(std::forward_list<int>& list){
    for (auto element : list){
        std::cout << element << " ";
    }
}

void allocate_processes(int (*allocate_process)(const int, std::forward_list<int>&), std::forward_list<int>& process_list, std::forward_list<int>& memory_list) {
    std::cout << "Memory List: ";
    printList(memory_list);
    std::cout << std::endl;
    std::cout << "Process List: ";
    printList(process_list);
    std::cout << std::endl;
    for(auto process : process_list){
        int index_allocated = allocate_process(process, memory_list);
        if (index_allocated == -1){
            std::cout << "Process of size " << process << " could not be allocated." << std::endl;
        } else {
            std::cout << "Process of size " << process << " allocated at position " << index_allocated+1 << std::endl;
        }
        printList(memory_list);
        std::cout << std::endl;
    }
}

int main() {
    std::forward_list<int> memory_list = {200, 400, 600, 500, 300, 250};
    std::forward_list<int> process_list = {357, 210, 468, 491};
    allocate_processes(first_fit_from_start, process_list, memory_list);
}
