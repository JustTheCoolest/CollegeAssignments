void fillContainers(int number_of_strings, char *containers[5][number_of_strings], int container_indices[5] ){

}

// Future optimisation: Separate strings who have reached theri \0 to not have to recalculate them in sorting
void radixSortStrings(int number_of_strings, int size_of_string, char *strings[][size_of_string], int i){
    const int number_of_iterations_per_char = ceil(__CHAR_BIT__/2);
    if(i>number_of_iterations_per_char*(size_of_string-1)*number_of_strings){
        return;
    }
    char *containers[4][number_of_strings]; // 1+2^2
    int container_indices[4] = {0, 0, 0, 0};
    for(int i=0; i<__CHAR_BIT__/2; ++i){
        fillContainers(number_of_strings, containers, container_indices, i, size_of_string, strings);
        collectCotainers(number_of_strings, containers, container_indices, i, size_of_string, strings);
        recurseContainers(container_indices);
    }
}

int main(){
    int number_of_strings;
    scanf("%d", &number_of_strings);
    int maximum_length_of_register_number;
    scanf("%d", &maximum_length_of_register_number);
    int size_of_string = maximum_length_of_register_number+1;
    char  strings[number_of_strings][size_of_string];
    getData(number_of_strings, size_of_string, strings);
    radixSortStrings(number_of_strings, size_of_string, strings);
    char string[size_of_string];
    scanf("%s", string);
    int position = binarySearch(number_of_strings, strings, string);
    printf(position>-1 ? "Yes\n" : "No\n");
    printf("%d\n", position);
}