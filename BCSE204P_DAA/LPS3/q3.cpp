#include <iostream>
using namespace std;

void mvms(int arr[], int n){
    int l = 0, u = n;
    while(arr[l] == 0){
        l++;
    }
    while(arr[u-1] == 0){
        u--;
    }
    int sum = 0;
    for(int i=l; i<u; i++){
        sum += arr[i];
    }
    cout << "Start at element number " << l+1 << endl;
    cout << "End at element number " << u << endl;
    cout << "Sum: " << sum << endl;
}

int main(){
    int array[] = {0, 0, 2, 3, 8, 6, 0, 0, 1, 0};
    int size = sizeof(array) / sizeof(array[0]);
    mvms(array, size);
}