#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct arg_struct {
    int n;
    const int *sequence;
    int frame_count;
};

int inArray(int target, int n, int array[]){
    for(int i=0; i<n; ++i){
        if(array[i] == target){
            return 1;
        }
    }
    return 0;
}

void *fifo(void *arg){
    struct arg_struct *argv = (struct arg_struct *)arg;
    const int n = argv->n;
    const int *sequence = argv->sequence;
    int frame_count = argv->frame_count;
    int frames[frame_count];
    for(int i=0; i<frame_count; ++i){
        frames[i] = -1;
    }
    int iterator = 0;
    int page_faults = 0;
    for(int i=0; i<n; ++i){
        int page = sequence[i];
        if(!inArray(page, frame_count, frames)){
            frames[iterator] = page;
            iterator = (iterator + 1) % frame_count;
            ++page_faults;
        }
    }
    int *result = (int *)malloc(sizeof(int));
    *result = page_faults;
    //printf("FIFOt: %d\n", *result);
    return (void *)result;
}

void use(int page, int frame_count, int *frames, int *last_used){
    int prev = page;
    for(int j=0; j<frame_count; ++j){
        int current = last_used[j];
        last_used[j] = prev;
        prev = current;
        if(prev == page){
            break;
        }
    }
}

void *lru(void *arg){
    struct arg_struct *argv = (struct arg_struct *)arg;
    const int n = argv->n;
    const int *sequence = argv->sequence;
    int frame_count = argv->frame_count;
    int frames[frame_count];
    for(int i=0; i<frame_count; ++i){
        frames[i] = -1;
    }
    int iterator = 0;
    int page_faults = 0;
    int last_used[frame_count];
    for(int i=0; i<n; ++i){
        int page = sequence[i];
        if(inArray(page, frame_count, frames)){
            use(page, frame_count, frames, last_used);
        }else{
            int target = last_used[frame_count-1];
            for(int j=0; j<frame_count; ++j){
                if(frames[j] == target){
                    frames[j] = page;
                    break;
                }
            }
            use(page, frame_count, frames, last_used);
            ++page_faults;
        }
    }
    int *result = (int *)malloc(sizeof(int));
    *result = page_faults;
    return (void *)result;
}

int distance(const int target, const int array[], const int n){
    for(int i=0; i<n; ++i){
        if(array[i] == target){
            return i+1;
        }
    }
    return n+1;
}

int max_index(int array[], int n){
    int max = array[0];
    int index = 0;
    for(int i=1; i<n; ++i){
        if(array[i] > max){
            max = array[i];
            index = i;
        }
    }
    return index;
}

void *optimal(void *arg){
    struct arg_struct *argv = (struct arg_struct *)arg;
    const int n = argv->n;
    const int *sequence = argv->sequence;
    int frame_count = argv->frame_count;
    int frames[frame_count];
    for(int i=0; i<frame_count; ++i){
        frames[i] = -1;
    }
    int iterator = 0;
    int page_faults = 0;
    for(int i=0; i<n; ++i){
        int page = sequence[i];
        if(inArray(page, frame_count, frames)){
            continue;
        }
        int distances[frame_count];
        for(int j=0; j<frame_count; ++j){
            distances[j] = distance(frames[j], sequence+i+1, n-i-1);
        }
        int replace = max_index(distances, frame_count);
        frames[replace] = page;
        ++page_faults;
    }
    int *result = (int *)malloc(sizeof(int));
    *result = page_faults;
    return (void *)result;
}

int main(){
    // const int n = 30;
    // const int sequence[] = {1, 2, 3, 4, 2, 1, 4,2,5, 6, 2, 1, 6,5, 2, 3, 7, 5, 4,2, 6, 3, 2, 1, 2, 3, 6,4,2,5};
    int n;
    scanf("%d", &n);
    int sequence[n];
    for(int i=0; i<n; ++i){
        scanf("%d", sequence+i);
    }
    const int frame_count = 3;
    pthread_t fifot, lrut, optt;
    struct arg_struct args;
    args.n = n;
    args.sequence = sequence;
    args.frame_count = frame_count;
    pthread_create(&fifot, NULL, fifo, (void *)&args);
    pthread_create(&lrut, NULL, lru, (void *)&args);
    pthread_create(&optt, NULL, optimal, (void *)&args);
    void *fifo_result, *lru_result, *opt_result;
    pthread_join(fifot, (void **)&fifo_result);
    pthread_join(lrut, (void **)&lru_result);
    pthread_join(optt, (void **)&opt_result);
    printf("FIFO: %d\n", *(int*)fifo_result);
    printf("LRU: %d\n", *(int*)lru_result);
    printf("OPT: %d\n", *(int*)(opt_result));
    free(fifo_result);
    free(lru_result);
    free(opt_result);
}