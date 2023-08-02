#include <stdio.h>

void update_top_element(int *top, int element){
    *top = element;
    printf("%d ", *top);
}

void print_top_elements(int array[], int n){
    int top;
    update_top_element(&top, array[n-1]);
    for(int i=n-1; i>=0; --i){
        if(array[i] > top){
            update_top_element(&top, array[i]);
        }
    }
    printf("\n");
}

int main(){
    int n;
    scanf("%d", &n);
    int array[n];
    for(int i=0; i<n; ++i){
        scanf("%d", array+i);
    }
    print_top_elements(array, n);
}