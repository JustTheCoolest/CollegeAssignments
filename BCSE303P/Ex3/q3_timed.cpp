#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

bool thing(int x, int y){
    int a = fork();
    if(a==0){
        sleep(x); 
        cout << "Child " << y << " terminating" << endl;\
        exit(0);
    }
    else if(a<-1){
        cout << "Process creation failed" << endl;
        return false;
    }
    else{
        return true;
    }
    return false;
}

int main(){
    if(thing(5, 1)) if(thing(3, 2)) thing(1, 3);
    for(int i=0; i<3; ++i)
        wait(NULL);
    cout << "Parent exiting" << endl;
}