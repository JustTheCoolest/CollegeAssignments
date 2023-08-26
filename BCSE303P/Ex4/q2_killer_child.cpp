#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;

int sum_of_first_n_integers(int n){
    return (n*(n+1))/2;
}

int main(){
    int f = fork();
    if(f == 0){
        int computed_result = sum_of_first_n_integers(100);
        kill(getppid(), SIGSTOP);
        sleep(1);
        cout << "Child: " << computed_result << endl;
    }
    else if(f > 0){
        sleep(100000);
    }
    else{
        cout << "Error in fork" << endl;
    }
}