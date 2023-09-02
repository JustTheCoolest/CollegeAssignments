#include <stdio.h>
#include <pthread.h>
#include <string>
#include <iostream>
#include <unistd.h>

using namespace std;

struct thread_data{
    int start;
    int end;
};

void* calculate_sum(void *arg) {
    thread_data *data = (thread_data *) arg;
    int start = data->start;
    int end = data->end;
    int sum = 0;
    for(int i = start; i<end; ++i){
        //sleep(0.0001);
        sum += i;
    }
    int *result = new int;
    *result = sum;
    return (void *) result;
}

void* calculate_sum_driver(int n){
    long long sum = 0;
    pthread_t threads[4];
    thread_data data[4];
    for(int i = 0; i < 4; ++i){
        data[i].start = i * n / 4;
        data[i].end = (i + 1) * n / 4;
        pthread_create(&threads[i], NULL, *calculate_sum, (void *) &data[i]);
    }
    void *result;
    for(int i = 0; i < 4; ++i){
        pthread_join(threads[i], &result);
        sum += *(int *) result;
    }
    cout << "Sum: " << sum << endl;
    return NULL;
}

int main(){
    clock_t start, end;
    start = clock();
    calculate_sum_driver(1000000);
    end = clock();
    clock_t time_taken = end - start;
    cout << "Time taken: " << time_taken << endl;
}