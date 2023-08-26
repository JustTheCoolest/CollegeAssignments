#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main(int num_args, char *args[]){
    int process_to_kill = atoi(args[1]);
    cout << "Killing process " << process_to_kill << endl;
    kill(process_to_kill, SIGSTOP);
}