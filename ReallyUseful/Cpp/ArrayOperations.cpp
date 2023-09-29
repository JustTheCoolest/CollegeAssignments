template <class DataType>
void freeArray(int n, DataType array[]){
    while(--n){
        delete array[n];
    }
}

template <class DataType>
bool allNotGreaterThan(int n, DataType array[], DataType array2[]){
    for(int i=0; i<n; ++i){
        if(array[i] > array2[i]){
            return false;
        }
    }
    return true;
}

template <class DataType>
void allMultiply(int n, DataType array[], int k){
    for(int i=0; i<n; ++i){
        array[i] *= k;
    }
}

template <class DataType>
void allAdd(int n, DataType array[], DataType array2[]){
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