#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int isOdd(int number){
    return number%2;
}

int getDigit(int number, int index){
    number = abs(number);
    int number_with_left_part_of_digit_removed = number % (int)(pow(10, index));
    int digit = number_with_left_part_of_digit_removed/(int)pow(10, index-1);
    return digit;
}

int main(){
    int n, p;
    scanf("%d\n%d", &n, &p);
    printf(isOdd(getDigit(n, p)) ? "Odd\n" : "Even\n");
}
