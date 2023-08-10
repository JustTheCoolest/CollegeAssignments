void insertElement(int n, int array[], int element, int position){
    for(int i=n; i>position; --i){
        array[i] = array[i-1];
    }
    array[position] = element;
}