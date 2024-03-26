#include<stdio.h>
#define MAX 50

typedef struct{
    int nums[MAX];
    int count;
}arrType;

int getInput();
void insertSort(arrType *arr, int x);
void displayArr(arrType arr);

int main(void){
    arrType arr={.count=0};
    while(1){
        insertSort(&arr,getInput());    
        displayArr(arr);
    }
    
}
    
int getInput(){
    int temp;
    printf("Enter a number: ");
    scanf("%d", &temp);
    return temp;
}

void insertSort(arrType *arr, int x){
    int i, j;
    for(i=0;i<arr->count && arr->nums[i] < x ;i++){}
    for(j=arr->count-1;j>=i;j--){
        arr->nums[j+1] = arr->nums[j];
    }
    arr->nums[i] = x;
    arr->count++;
}

void displayArr(arrType arr){
    int i;
    for(i=0;i<arr.count;i++){
        printf("%d ", arr.nums[i]);
    }
    printf("\n");
}














