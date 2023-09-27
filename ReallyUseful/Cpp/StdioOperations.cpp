#include <iostream>
#include <string>

using namespace std;

template <class DataType>
void printArray(string seperator, int n, DataType numbers[]){
    for(int i=0; i<n-1; ++i){
        cout << numbers[i] << seperator;
    }
    cout << numbers[n] << endl;
}

template <class DataType>
void getInputs(int n, DataType array[]){
    for(int i=0; i<n; ++i){
        cout << "Enter element " << i+1 << ": ";
        cin >> array[i];
    }
}
