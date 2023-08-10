// void fillContainers(int number_of_strings, char *containers[5][number_of_strings], int container_indices[5] ){

// }

// // Future optimisation: Separate strings who have reached theri \0 to not have to recalculate them in sorting
// void radixSortStrings(int number_of_strings, int size_of_string, char *strings[][size_of_string], int i){
//     const int number_of_iterations_per_char = ceil(__CHAR_BIT__/2);
//     if(i>number_of_iterations_per_char*(size_of_string-1)*number_of_strings){
//         return;
//     }
//     char *containers[4][number_of_strings]; // 1+2^2
//     int container_indices[4] = {0, 0, 0, 0};
//     for(int i=0; i<__CHAR_BIT__/2; ++i){
//         fillContainers(number_of_strings, containers, container_indices, i, size_of_string, strings);
//         collectCotainers(number_of_strings, containers, container_indices, i, size_of_string, strings);
//         recurseContainers(container_indices);
//     }
// }

#include <stdio.h>
#include <string.h>

void getData(int number_of_strings, int size_of_string, char strings[][size_of_string]){
    for(int i=0; i<number_of_strings; ++i){
        scanf("%s", strings[i]);
    }
}

void swapStrings(int size_of_string, char *string1, char *string2){
    char temp[size_of_string];
    strcpy(temp, string1);
    strcpy(string1, string2);
    strcpy(string2, temp);
}

void bubbleSortStrings(int number_of_strings, int size_of_string, char strings[][size_of_string]){
    for(int i=0; i<number_of_strings-1; ++i){
        for(int j=0; j<number_of_strings-i-1; ++j){
            if(strcmp(strings[j], strings[j+1])>0){
                swapStrings(size_of_string, strings[j], strings[j+1]);
            }
        }
    }
}

int binarySearch(int const number_of_strings, int const size_of_string, char const strings[][size_of_string], char const *string){
    int left = 0, right = number_of_strings;
    int mid, comparison_result;
    while(left<right){
        mid = (left+right)/2;
        comparison_result = strcmp(strings[mid], string);
        //printf("%d %d %d %d\n", left, mid, right, comparison_result);
        //printf("%s %s\n", strings[mid], string);
        if(!comparison_result){
            return mid;
        }
        else if(comparison_result>0){
            right = mid;
        }
        else{
            left = mid+1;
            break;
        }
    }
    return -1;
}

int test_main(){
    const int number_of_strings = 5;
    const int size_of_string = 6;
    char strings[5][6] = {"abcde", "abcdf", "abcef", "abcf", "abc"};
    bubbleSortStrings(number_of_strings, size_of_string, strings);
    for(int i=0; i<number_of_strings; ++i){
        printf("%s ", strings[i]);
    }
    char string[6] = "abc";
    printf("\n%d\n", strcmp("abcde", "abc"));
    int position = binarySearch(number_of_strings, size_of_string, strings, string);
    printf(position>-1 ? "Yes\n" : "No\n");
    printf("%d\n", position);
}

int main(){
    int number_of_strings;
    scanf("%d", &number_of_strings);
    int maximum_length_of_register_number;
    scanf("%d", &maximum_length_of_register_number);
    int size_of_string = maximum_length_of_register_number+1;
    char  strings[number_of_strings][size_of_string];
    getData(number_of_strings, size_of_string, strings);
    bubbleSortStrings(number_of_strings, size_of_string, strings);
    // for(int i=0; i<number_of_strings; ++i){
    //     printf("%s ", strings[i]);
    // }
    char string[size_of_string];
    scanf("%s", string);
    int position = binarySearch(number_of_strings, size_of_string, strings, string);
    printf(position>-1 ? "Yes\n" : "No\n");
    printf("%d\n", position);
}