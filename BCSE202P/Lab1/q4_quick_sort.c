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

void quickSort(int numbers[], int start_index, int end_index){
    int pivot = numbers[start_index];
    int left_traverser = start_index+1;
    int right_traverser = end_index;
    int swapped_flag = 0;
    while(1){
        while(numbers[left_traverser] < pivot && left_traverser <= end_index){
            left_traverser++;
        }
        while(numbers[right_traverser] > pivot && right_traverser >= start_index){
            right_traverser--;
        }
        if(left_traverser >= right_traverser){
            break;
        }
        swap(&numbers[left_traverser], &numbers[right_traverser]);
        swapped_flag = 1;
    }
    if(start_index != end_index){
        swap(&numbers[start_index], &numbers[right_traverser]);
        swapped_flag = 1;
    }
    if(swapped_flag == 0){
        return;
    }
    quickSort(numbers, start_index, right_traverser-1);
    quickSort(numbers, right_traverser+1, end_index);
}

void printArray(int n, int numbers[], int k1, int k2){
    for(int i=k1; i<=k2; ++i){
        printf("%d ", numbers[i]);
    }
    printf("\n");
}

int main(){
    int n;
    scanf("%d", &n);
    int numbers[n];
    getInputs(n, numbers);
    int k1, k2; 
    scanf("%d %d", &k1, &k2);
    //quickSort(numbers, 0, n-1);
    printArray(n, numbers, 0, n-1);
    printArray(n, numbers, k1, k2);
}