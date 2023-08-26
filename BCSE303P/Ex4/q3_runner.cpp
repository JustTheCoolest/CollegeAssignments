#include <iostream>
#include <unistd.h>
using namespace std;

int main(){
    while(1){
        cout << getpid() << endl;
        sleep(1);
    }
}