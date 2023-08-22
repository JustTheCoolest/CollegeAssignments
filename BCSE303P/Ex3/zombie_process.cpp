// #include <iostream>
// #include <dirent.h>
// #include <cstring>
// #include <unistd.h>
// #include <iostream>
// #include <sys/wait.h>
// using namespace std;

// int count_child_processes(pid_t pid) {
//     int count = 0;
//     DIR *directory;
//     struct dirent *entry;
//     char path[19];
//     sprintf(path, "/proc/%d/task", pid);

//     directory = opendir(path);
//     if (directory == NULL) {
//         cerr << "Could not open directory" << endl;
//         exit(EXIT_FAILURE);
//     }
    
//     while ((entry = readdir(directory)) != NULL) {
//         if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
//             ++count;
//         }
//         cout << entry->d_name << endl;
//     }
//     closedir(directory);

//     // Subtract 1 from the count to exclude the main thread, which is not a child process
//     return count - 1;
// }

// int main(){
//     int a = fork();
//     cout << a << endl;
//     if(a==0){
//         sleep(5); 
//         cout << "Child terminating" << endl;
//         exit(0);
//     }
//     else if(a<-1){
//         cout << "Process creation failed" << endl;
//         return false;
//     }
//     else{
//         pid_t pid = getpid();
//         cout << "Number of child processes, before child terminates, as per parent: " << count_child_processes(pid) << endl;
//         sleep(10);
//         cout << "Number of child processes, after child terminates, as per parent: " << count_child_processes(pid) << endl;
//         waitpid(a, NULL, 0);
//         cout << "Number of child processes, after child terminates, after parent executes waitpid, as per parent: " << count_child_processes(pid) << endl;
//     }
// }

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

void display(int array[], int size){
    if(size==0){
        cout << "No child processes" << endl;
        return;
    }
    for(int i=0; i<size; i++){
        cout << array[i] << endl;
    }
}

void child_stuff(int a){
    if(a==0){
        sleep(5); 
        cout << "Child terminating" << std::endl;
        exit(0);
    }
    else if(a<0){
        cout << "Process creation failed" << std::endl;
        exit(1);
    }
}

int main(){
    int number_of_child_processes = 0;
    int child_processes[100];
    int a = fork();
    child_processes[number_of_child_processes++] = a;

    child_stuff(a);

    cout << "Children from parent process view before child termination: " << endl;
    display(child_processes, number_of_child_processes);
    sleep(10);
    cout << "Children from parent process view after child termination: " << endl;
    display(child_processes, number_of_child_processes);
    cout << "Hence, we created a zombie process" << endl;
    waitpid(child_processes[--number_of_child_processes], NULL, 0);
    cout << "Children from parent process view after child termination and waitpid: " << endl;
    display(child_processes, number_of_child_processes);

    child_processes[number_of_child_processes++] = fork();

    child_stuff(child_processes[number_of_child_processes-1]);

    cout << "Children from parent process view after forking: " << endl;
    display(child_processes, number_of_child_processes);

    cout << "Parent terminating, making child an orphan" << endl;
}