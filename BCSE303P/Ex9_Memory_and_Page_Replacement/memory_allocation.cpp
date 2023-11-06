#include <forward_list>
#include <list>
#include <iterator>
#include <algorithm>
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

void best_fit(const int process, int memory_list[], const int n) {
    std::sort(memory_list, memory_list+n);
    int index = -1;
    for (int i = 0; i < n; ++i){
        if (memory_list[i] < process){
            continue;
        }
        memory_list[i] -= process;
        index = i;
        break;
    }
    if (index == -1){
        std::cout << "Process of size " << process << " could not be allocated." << std::endl;
    } else {
        std::cout << "Process of size " << process << " allocated to hole of size " << memory_list[index] << std::endl;
    }
}

void printList(const std::forward_list<int>& list){
    for (auto element : list){
        std::cout << element << " ";
    }
}

// Task: Use functors instead of auto
void allocate_processes(auto allocate_process, auto process_list, auto memory_list) {
    std::cout << "Memory List: ";
    printList(memory_list);
    std::cout << std::endl;
    std::cout << "Process List: ";
    printList(process_list);
    std::cout << std::endl;
    for(auto process : process_list){
        int index_allocated = allocate_process(process);
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
    {
        std::cout << "First Fit" << std::endl;
        std::forward_list<int> memory_list = {200, 400, 600, 500, 300, 250};
        std::forward_list<int> process_list = {357, 210, 468, 491};
        allocate_processes(
            [&memory_list](const int process){return first_fit_from_start(process, memory_list);}, 
            process_list, 
            memory_list
        );
        std::cout << std::endl;
    }
    { // Best Fit
        std::cout << "Best Fit" << std::endl;
        // Change of mind: Finish assignment on time with simple code
        int memory_list[] = {200, 400, 600, 500, 300, 250};
        int process_list[] = {357, 210, 468, 491};
        // std::list<int> sequence_list;
        // proxySort(memory_list, sequence_list);
        for(auto process : process_list){
            best_fit(process, memory_list, 6);
        }
        std::cout << std::endl;
    }
    { // Worst Fit
        std:: cout << "Worst Fit" << std::endl;
        int memory_list[] = {200, 400, 600, 500, 300, 250};
        int process_list[] = {357, 210, 468, 491};
        for(auto process : process_list){
            std::sort(memory_list, memory_list+6, std::greater<int>());
            if(memory_list[0] < process){
                std::cout << "Process of size " << process << " could not be allocated." << std::endl;
            } else {
                std::cout << "Process of size " << process << " allocated to hole of size " << memory_list[0] << std::endl;
                memory_list[0] -= process;
            }
        }
        std::cout << std::endl;
    }
}
