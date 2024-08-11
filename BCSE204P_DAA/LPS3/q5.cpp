// Maximum non-contiguous subarray for non-negative integers

#include <iostream>
using namespace std;

void mncms(int arr[], int n){
    int sum = 0;
    cout << "Maximum non-contiguous subarray: " << endl;
    for(int i=0; i<n; i++){
        cout << "Element number " << i+1 << ": ";
        if(arr[i] > 0){
            sum += arr[i];
            cout << "Include" << endl;
        }
        else{
            cout << "Exclude" << endl;
        }
    }
    cout << "Sum: " << sum << endl;
}

int main(){
    int array[] = {0, 0, 2, 3, 8, 6, 0, 0, 1, 0};
    int size = sizeof(array) / sizeof(array[0]);
    mncms(array, size);
}