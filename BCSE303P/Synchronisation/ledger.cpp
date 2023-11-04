#include <pthread.h>
#include <iostream>
#include <semaphore.h>
using namespace std;

#define PROCESS_LOCAL 0

sem_t mutex, reader_counter_mutex;
int reader_counter = 0;

int stock_book[100];
int cursor;

void init(){
    for(cursor=0; cursor<50; ++cursor){
        stock_book[cursor] = cursor*5+2;
    }
}

void write(int value){
    sem_wait(&mutex);
    stock_book[cursor++] = value;
    sem_post(&mutex);
}

int read(int index){
    sem_wait(&reader_counter_mutex);
    ++reader_counter;
    if(reader_counter==1){
        sem_wait(&mutex);
    }
    sem_post(&reader_counter_mutex);
    int value = stock_book[index];
    sem_wait(&reader_counter_mutex);
    --reader_counter;
    if(reader_counter==0){
        sem_post(&mutex);
    }
    sem_post(&reader_counter_mutex);
    return value;
}

void* p1(void* parameter){
    write(+345);
    cout << "P1 wrote 345" << endl;
    cout << "P1 read " << read(4) << endl;
    return nullptr;
}

void* p2(void* parameter){
    read(7);
    cout << "P2 read " << read(7) << endl;
    return nullptr;
}

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

int main(){
    pthread_t people[2];
    init();
    sem_init(&mutex, PROCESS_LOCAL, 1);
    sem_init(&reader_counter_mutex, PROCESS_LOCAL, 1);
    pthread_create(&people[0], nullptr, p1, nullptr);
    pthread_create(&people[1], nullptr, p2, nullptr);
    pthread_join(2, people, nullptr);
}