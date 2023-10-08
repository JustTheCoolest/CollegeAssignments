#include <iostream>
#include <string>

template <class DataType>
void printArray(std::string seperator, int n, DataType numbers[]){
    for(int i=0; i<n-1; ++i){
        std::cout << numbers[i] << seperator;
    }
    std::cout << numbers[n-1] << std::endl;
}

template <class DataType>
void printArrayStringForm(std::string separator, int n, DataType *data[]){
    if(n==0){
        std::cout << "Array is empty" << std::endl;
        return;
    }
    for(int i=0; i<n-1; ++i){
        // std::cout << data[i]->toString() << separator;
    }
    // std::cout << data[n-1]->toString() << std::endl;
}

template <class DataType>
void getInputs(int n, DataType array[]){
    for(int i=0; i<n; ++i){
        std::cout << "Enter element " << i+1 << ": ";
        std::cin >> array[i];
        // std::cout << "The element you entered is " << array[i] << std::endl;
    }
    // std::cout << "Array is ";
    // printArray<DataType>(" ", n, array);
}
