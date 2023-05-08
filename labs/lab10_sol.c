#include <stdio.h>
#include <stdlib.h>

// swap two elements in an array 
void swap(int array[], int i, int j){
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

// find the index of the minimum element in an array
int find_max_idx(int array[], int len){ 
    int idx = 0; 
    int max = array[0];
    for (int i = 1; i < len; i++)
    {
        if(array[i] > max){
            max = array[i];
            idx = i; 
        }
    }
    
    return idx; 
}

// print an array
void print_array(int array[], int len){
    for (int i = 0; i < len; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// sort an array using selection sort
void sort(int array[], int len){
    for (int i = 1; i <= len-1; i++){
        
        int max_idx = find_max_idx(array, len - i + 1); 

        swap(array, max_idx, len - i);

        print_array(array, len);
    }
}

// recursive version of selection sort
void sort_2(int array[], int len){
    int max_idx = find_max_idx(array, len); 
    swap(array, max_idx, len - 1);

    if(len>1){ 
        sort_2(array, len-1);
    }
}

void main()
{
    int array[] = {5,3,2,4};
    int len = 4;
    
    printf("testing find_max_idx-----------------------\n");
    // testing find_min_idx
    int min_idx = find_max_idx(array, len);
    printf("max_idx: %d\n", min_idx);

    printf("testing swap-----------------------\n");
    //testing swap
    swap(array, 0, 1);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    printf("testing sort-----------------------\n");
    //test sort
    int a [] = {5, 3, 2, 1, 2,  4};
    len = 6;
    sort(a, len);
    print_array(a, len);

    printf("testing sort (recursive)-----------------------\n");
    sort_2(a, len);
    print_array(a, len);
}