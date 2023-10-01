template <class DataType>
void freeArray(int n, DataType array[]){
    while(--n){
        delete array[n];
    }
}

template <class DataType>
bool notGreaterThanCorresponding(int n, DataType array[], DataType array2[]){
    for(int i=0; i<n; ++i){
        if(array[i] > array2[i]){
            return false;
        }
    }
    return true;
}

template <class DataType>
void multiplyEach(int n, DataType array[], int k){
    for(int i=0; i<n; ++i){
        array[i] *= k;
    }
}

template <class DataType>
void addEach(int n, DataType array[], DataType array2[]){
    for(int i=0; i<n; ++i){
        array[i] += array2[i];
    }
}

template <class DataType>
void copyArray(int n, DataType destination[], DataType source[]){
    for(int i=0; i<n; ++i){
        destination[i] = source[i];
    }
}

template <class DataType>
void copyObjectsFromPointerArray(int n, DataType *destination[], DataType *source[]){
    while(--n){
        destination[n] = new DataType(*source[n]);
    }
}

template <class DataType>
void sortByParameter(int const index, int const n, DataType array[]){
    // Task: Take function input instead of index input to give more power
    int copy = n;
    while(--copy){
        for(int i=0; i<copy, ++i){
            if(array[i][index] > array[i+1][index]){
                DataType temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
            }
        }
    } 
}

 