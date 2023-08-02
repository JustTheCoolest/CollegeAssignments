#include <stdio.h>
#include <stdlib.h>

// Alternative: Calculate the sums while reading the array itself without ever having to store the elements

void find_sum_of_diagonal(int *sum_of_dexter_diagonal, int *sum_of_sinister_diagonal, int n, int matrix[n][n]){
    *sum_of_dexter_diagonal = 0;
    *sum_of_sinister_diagonal = 0;
    for(int i=0; i<n; ++i){
        *sum_of_dexter_diagonal += matrix[i][i];
        *sum_of_sinister_diagonal += matrix[i][n-i-1];
    }
}

int find_difference_of_diagonals(int sum_of_dexter_diagonal, int sum_of_sinister_diagonal, int n, int matrix[n][n]){
    return abs(sum_of_dexter_diagonal - sum_of_sinister_diagonal);
}

int main(){
    int m, n;
    scanf("%d", &n);
    int matrix[n][n];
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            scanf("%d", matrix[i]+j);
        }
    }
    int sum_of_dexter_diagonal, sum_of_sinister_diagonal;
    find_sum_of_diagonal(&sum_of_dexter_diagonal, &sum_of_sinister_diagonal, n, matrix);
    printf("%d\n%d\n%d\n", 
        sum_of_dexter_diagonal, 
        sum_of_sinister_diagonal, 
        find_difference_of_diagonals(sum_of_dexter_diagonal, sum_of_sinister_diagonal, n, matrix)
    );
}