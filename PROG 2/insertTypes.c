#include<stdio.h>

int main(void){

    int arr[15] = {5,4,8,2,3,6,1};
    int size = 7, position = 2;
    
    int i,j, key = 9;

// insert first
    
    for(i=size-1;i>=0;i--){
        arr[i+1] = arr[i];
    }
    arr[0] = key;
    size++;

// insert middle
    
    for(i=0;i<size && arr[i] != position;i++){}
    
    for(j=size-1;j>=i;j--){
        arr[j+1] = arr[j];
    }
    arr[i+1] = key;
    size++;

// insert last
    arr[size++] = key;
    
    
    // display
    for(i=0;i<size;i++){
        printf("%d ", arr[i]);
    }
    
    return 0;
}
