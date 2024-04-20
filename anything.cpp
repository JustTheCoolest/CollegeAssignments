#include <pthread.h>
#include <iostream>

using namespace std;

void* thread1(void* a_ptr){
    int& a = *(static_cast<int*>(a_ptr));
    while(true){
        cout << a << " ";
    }
}

void thread2(int& a){
    while(true){
        ++a;
    }
}

int main(){
    int a = 0;
    pthread_t thread;
    pthread_create(&thread, nullptr, thread1, &a);
    thread2(a);
}