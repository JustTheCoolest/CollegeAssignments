#include <iostream>
#include <vector>
using namespace std;

// Since maximal subarray is shortest, we will assume minimal means longest

void mvms(int arr[], int n){
    int l = 0, u = n;
    // while(arr[l] == 0){
    //     l++;
    // }
    // while(arr[u-1] == 0){
    //     u--;
    // }
    int sum = 0;
    for(int i=l; i<u; i++){
        sum += arr[i];
    }
    cout << "Maximal value minimal subarray: " << endl;
    cout << "Start at element number " << l+1 << endl;
    cout << "End at element number " << u << endl;
    cout << "Sum: " << sum << endl;
}

// void minimal_value_maximal_subarray(int arr[], int n){
//     int l = 0, u = 0;
//     bool flag = true;
//     int sum;
//     for(int i=0; i<n; i++){
//         if(flag && arr[i] == 0){
//             l = i;
//             flag = true;
//         }
//         else if(!flag && arr[i] != 0){
//             u = i;
//             flag = false;
//         }
//     }
//     if(u>=l){
//         u = n-1;
//     }
    
// }

void minimal_value_maximal_subarray(int arr[], int n){
    int pos = -1, min = __INT_MAX__;
    for(int i=0; i<n; i++){
        if(arr[i] < min){
            min = arr[i];
            pos = i;
        }
    }
    cout << "Minimal value maximal subarray: " << endl;
    cout << "Start at element number " << pos+1 << endl;
    cout << "End at element number " << pos+1 << endl;
    cout << "Sum: " << min << endl;
}

// void minimal_value_minimal_subarray(int arr[], int n){
//     int min = __INT_MAX__;
//     vector<int> positions;
//     for(int i=0; i<n; i++){
//         if(arr[i] < min){
//             min = arr[i];
//             positions.clear();
//             positions.push_back(i);
//         }
//         else if(arr[i] == min){
//             positions.push_back(i);
//         }
//     }
//     int max_length = 0;
//     int start = 0;
//     int end = 0;
//     for(auto i: positions){
//         int l = i, u = i;
//         while(l>0 && arr[l-1] == 0){
//             l--;
//         }
//         while(u<n-1 && arr[u+1] == 0){
//             u++;
//         }
//         if(u-l > max_length){
//             max_length = u-l;
//             start = l;
//             end = u;
//         }
//     }
//     cout << "Minimal value minimal subarray: " << endl;
//     cout << "Start at element number " << start+1 << endl;
//     cout << "End at element number " << end+1 << endl;
//     cout << "Sum: " << min << endl;
// }

int sum(int arr[], int l, int u){
    int sum = 0;
    for(int i=l; i<u; i++){
        sum += arr[i];
    }
    return sum;
}

void minimal_value_minimal_subarray(int arr[], int n){
    int min = __INT_MAX__;
    int L = -1, R = -1;
    for(int s=n; s>0; s--){
        for(int i=0; i<=n-s; i++){
            int j = i+s;
            if(sum(arr, i, j) < min){
                min = sum(arr, i, j);
                L = i;
                R = j;
            }
        }
    }
    cout << "Minimal value minimal subarray: " << endl;
    cout << "Start at element number " << L+1 << endl;
    cout << "End at element number " << R << endl;
    cout << "Sum: " << min << endl;
}


int main(){
    int array[] = {0, 0, 2, 3, 8, 6, 0, 0, 1, 0};
    int size = sizeof(array) / sizeof(array[0]);
    mvms(array, size);
    minimal_value_maximal_subarray(array, size);
    minimal_value_minimal_subarray(array, size);
}