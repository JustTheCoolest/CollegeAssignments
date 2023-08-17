#include <iostream>
#include <unistd.h>
using namespace std;

int main(){
    int pid = fork();
    if(pid==0){
        char *args[] = {"s.out", NULL};
        execv("s.out", args);
    }
    else if(pid>0){
        int n=10;
        int a=-1, b=+1;
        for(int i=0; i<n; ++i){
            b = a+b;
            a = b-a;
        }
        cout << "Fibonacci: " << b << endl;
    }
}