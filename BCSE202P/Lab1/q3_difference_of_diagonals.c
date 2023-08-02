#include <stdio.h>
#include <stdlib.h>

// Alternative: Calculate the sums while reading the array itself without ever having to store the elements

int find_difference_of_diagonals(int n, int matrix[n][n]){
    int sum_of_left_diagonal = 0;
    int sum_of_right_diagonal = 0;
    for(int i=0; i<n; ++i){
        sum_of_left_diagonal += matrix[i][i];
        sum_of_right_diagonal += matrix[i][n-i-1];
    }
    return abs(sum_of_left_diagonal - sum_of_right_diagonal);
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
    printf("%d\n", find_difference_of_diagonals(n, matrix));
}