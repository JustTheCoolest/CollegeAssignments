#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void get_inputs(int words[], int n, int word_length){
    for(int i = 0; i < n; i++){
        printf("Enter the word %d (MSB to LSB): ", i+1);
        int word = 0;
        for(int j = 0; j < word_length; j++){
            int bit;
            printf("Enter the bit %d: ", j+1);
            scanf("%d", &bit);
            word <<= 1;
            word |= bit;
        }
        words[i] = word;
    }
}

int get_checksum(int words[], int n, int word_length){
    int checksum = 0;
    for(int i = 0; i < n; i++){
        checksum += words[i];
    }
    printf("The sum of the words is: %d\n", checksum);
    int max_value = (1 << word_length) - 1;
    int number_of_numbers = max_value + 1;
    printf("The maximum value of the word is: %d\n", max_value);
    while(checksum > max_value){
        checksum = checksum / number_of_numbers + checksum % number_of_numbers;
    }
    printf("The checksum before inversion is: %d\n", checksum);
    checksum = max_value - checksum; // inversion
    return checksum;
}

char* sprint_binary(int number, int word_length){
    char* binary = (char*)malloc(word_length * sizeof(char));
    for(int i=word_length-1; i>=0; --i){
        binary[i] = (number & 1) + '0';
        number >>= 1;
    }
    return binary;
}

void print_codeword(int checksum, int words[], int n, int word_length){
    for(int i = 0; i < n; i++){
        printf("%s", sprint_binary(words[i], word_length));
    }
    printf("%s", sprint_binary(checksum, word_length));
}

int main(){
    int n;
    printf("Number of words: ");
    scanf("%d", &n);
    int word_length;
    printf("Enter the word length: ");
    scanf("%d", &word_length);
    int words[n];

    get_inputs(words, n, word_length);
    int checksum = get_checksum(words, n, word_length);
    printf("The checksum is: %d\n", checksum);
    printf("The codeword is: ");
    print_codeword(checksum, words, n,  word_length);
    printf("\n");
}