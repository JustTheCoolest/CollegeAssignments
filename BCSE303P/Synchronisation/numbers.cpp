#include <pthread.h>
#include <iostream>
#include <semaphore.h>
#include <unistd.h>
#include <chrono>

#define PROCESS_LOCAL 0

using namespace std;

struct thread_parameters{
    sem_t *semaphore;
    sem_t *chance;
};

int I = 0, N;

// Improvment: Perhaps sem_execute(function)
// Note : Might need extern "C" for C++ compiler, no error in g++ though
void* thread1(void *parameters){
    sem_t *semaphore = ((struct thread_parameters*)parameters)->semaphore;
    sem_t *chance = ((struct thread_parameters*)parameters)->chance;
    int sem_value;
    while(true){
        do{
            sem_getvalue(chance, &sem_value);
        }while(sem_value==1);
        if(I>=N){
            break;
        }
        sem_wait(semaphore);
        cout << ++I << " ";
        sem_post(chance);
        sem_post(semaphore);
    }
    return nullptr;
}

void thread2(sem_t *chance, sem_t *semaphore){
    int sem_value;
    while(true){
        do{
            sem_getvalue(chance, &sem_value);
        }while(sem_value==0);
        if(I>=N){
            break;
        }
        sem_wait(semaphore);
        cout << ++I << " ";
        sem_trywait(chance);
        sem_post(semaphore);
    }
}

void thread_init(sem_t *chance, sem_t *semaphore, pthread_t *thread){
    struct thread_parameters parameters;
    parameters.semaphore = semaphore;
    parameters.chance = chance;
    pthread_create(thread, nullptr, thread1, (void*)&parameters);
}

// Task: Check return values for semaphore and pthread functions
int main(int argc, char *argv[]){
    cin >> N;
    sem_t semaphore, chance;
    sem_init(&semaphore, PROCESS_LOCAL, 1);
    sem_init(&chance, PROCESS_LOCAL, 0);
    pthread_t thread;
    thread_init(&chance, &semaphore, &thread);
    thread2(&chance, &semaphore);\
    cout << endl;
}