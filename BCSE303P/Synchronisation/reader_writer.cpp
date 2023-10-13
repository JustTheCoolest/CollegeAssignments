constexpr unsigned int N = 10;
constexpr unsigned int M = 5;

#include <iostream>
//extern "C"{
    #include <pthread.h>
    #include <semaphore.h>
//}
using namespace std;
#define PROCESS_LOCAL 0

// Task: Keep track of return values for semaphore and pthread functions

int X = 0;

sem_t reader_counter_mutex, data_mutex;
unsigned int reader_counter = 0;

void pthread_join(int n, pthread_t* threads, void** return_values){
    for(unsigned int i=0; i<n; ++i){
        void** return_value_pointer = nullptr;
        if(return_values){
            return_value_pointer = &return_values[i];
        }
        pthread_join(threads[i], return_value_pointer);
        // cout << "Joined thread " << threads[i] << endl;
    }
}

void* create_readers(void* parameter){
    unsigned int N = *((unsigned int*)parameter);
    pthread_t readers[N];
    for(unsigned int i=0; i<N; ++i){
        pthread_create(&readers[i], nullptr, [](void* parameter)->void*{
            sem_wait(&reader_counter_mutex);
            ++reader_counter;
            if(reader_counter==1){
                sem_wait(&data_mutex);
            }
            sem_post(&reader_counter_mutex);
            cout << "Reader " << pthread_self() << " says X value: " << X << endl;
            sem_wait(&reader_counter_mutex);
            --reader_counter;
            if(reader_counter==0){
                sem_post(&data_mutex);
            }
            sem_post(&reader_counter_mutex);
            return nullptr;
        }, nullptr);
    }
    pthread_join(N, readers, nullptr);
    return nullptr;
}

void* create_writers(void* parameter){
    unsigned int M = *((unsigned int*)parameter);
    pthread_t writers[M];
    for(uint i=0; i<M; ++i){
        pthread_create(&writers[i], nullptr, [](void* parameter)->void*{
            sem_wait(&data_mutex);
            ++X;
            cout << "Writer " << pthread_self() << " wrote X value to: " << X << endl;
            sem_post(&data_mutex);
            return nullptr;
        }, nullptr);
    }
    pthread_join(M, writers, nullptr);
    return nullptr;
}

int main(){
    pthread_t reader_creator, writer_creator;
    sem_init(&reader_counter_mutex, PROCESS_LOCAL, 1);
    sem_init(&data_mutex, PROCESS_LOCAL, 1);
    pthread_create(&reader_creator, nullptr, create_readers, (void*)&N);
    pthread_create(&writer_creator, nullptr, create_writers, (void*)&M);
    pthread_join(reader_creator, nullptr);
    pthread_join(writer_creator, nullptr);
}