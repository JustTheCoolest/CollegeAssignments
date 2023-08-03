#include <stdio.h>

void getInputs(int n, int numbers[]){
    for(int i=0; i<n; i++){
        scanf("%d", &numbers[i]);
    }
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp; 
}

int incrementedTraverser(int numbers[], int traverser, int pivot, int index_limit){
    int direction = index_limit - traverser > 0 ? 1 : -1;
    while(numbers[traverser]*direction <= pivot*direction && traverser*direction < index_limit*direction){
        traverser += direction;
    }
    return traverser;
}

int isInRange(int current_position, int start_position, int end_position){
    return current_position >= start_position && current_position <= end_position;
}

void printArray(int n, int numbers[], int k1, int k2){
    for(int i=k1; i<=k2; ++i){
        printf("%d ", numbers[i]);
    }
    printf("\n");
}

// Inference: Cannot use a swap flag to break loop because choice of pivot influences number of swaps too
void quickSort(int numbers[], int start_index, int end_index){
    //printArray(10, numbers, 0, 9);
    int pivot = numbers[start_index];
    int left_traverser = start_index;
    int right_traverser = end_index;
    while(1){
        left_traverser = incrementedTraverser(numbers, left_traverser, pivot, end_index);
        right_traverser = incrementedTraverser(numbers, right_traverser, pivot, start_index);
        if(left_traverser >= right_traverser){
            break;
        }
        swap(&numbers[left_traverser], &numbers[right_traverser]);
    }
    if(start_index != right_traverser){
        swap(&numbers[start_index], &numbers[right_traverser]);
    }
    int left_segment_end_index = right_traverser-1;
    if(isInRange(left_segment_end_index, start_index, end_index)){
        //printf("%d %d\n", start_index, left_segment_end_index);
        quickSort(numbers, start_index, left_segment_end_index);
    }
    int right_segment_start_index = right_traverser+1;
    if(isInRange(right_segment_start_index, start_index, end_index)){
        //printf("%d %d\n", right_segment_start_index, end_index);
        quickSort(numbers, right_segment_start_index, end_index);
    }
}

int test_main(){
    int n = 10;
    int numbers[10] = {10, 3, 5, 9, 7, 2, 6, 1, 4, 8};
    int k1 = 4, k2 = 9;
    //printArray(n, numbers, 0, n-1);
    quickSort(numbers, 0, n-1);
    printArray(n, numbers, 0, n-1);
    printArray(n, numbers, k1, k2);
}

int main(){
    int n;
    scanf("%d", &n);
    int numbers[n];
    getInputs(n, numbers);
    int k1, k2; 
    scanf("%d %d", &k1, &k2);
    quickSort(numbers, 0, n-1);
    printArray(n, numbers, 0, n-1);
    printArray(n, numbers, k1, k2);
}