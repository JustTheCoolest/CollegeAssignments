#include <pthread.h>
#include <iostream>
#include <semaphore.h>
#include <unistd.h>
#include <chrono>

#define PROCESS_LOCAL 0

using namespace std;

struct thread_parameters{
    sem_t *semaphore;
};

void something(int thread_id){
    cout << "Thread " << thread_id << " starts at " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
    sleep(1);
    cout << "Thread " << thread_id << " ends at " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
}

// Improvment: Perhaps sem_execute(function)
// Note : Might need extern "C" for C++ compiler, no error in g++ though
void* thread1(void *parameters){
    sem_t *semaphore = ((struct thread_parameters*)parameters)->semaphore;
    while(true){
        sem_wait(semaphore);
        something(1);
        sem_post(semaphore);
        sleep(0.5);
    }
}

void thread2(sem_t *semaphore){
    while(true){
        sem_wait(semaphore);
        something(2);
        sem_post(semaphore);
        sleep(0.5);
    }
}

void thread_init(sem_t *semaphore, pthread_t *thread){
    struct thread_parameters parameters;
    parameters.semaphore = semaphore;
    pthread_create(thread, nullptr, thread1, (void*)&parameters);
}

int main(){
    sem_t semaphore;
    sem_init(&semaphore, PROCESS_LOCAL, 1);
    pthread_t thread;
    thread_init(&semaphore, &thread);
    thread2(&semaphore);
}