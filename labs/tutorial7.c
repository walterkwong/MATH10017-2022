#include <stdio.h>
#include <stdlib.h> // for string compare function 'strcmp'

// SORTING STRINGS
/*
** swap: swap the i and j elements of an array of strings
*/
void swap(char* array[], int i, int j){
    char* temp = array[i];
    // YOUR CODE HERE
}

/*
** find_max_idx: find the index of the "largest" string in array
*/
int find_max_idx(char* array[], int len){
    int idx = 0;
    char* max = array[0];
    // YOUR CODE HERE
    // note: strcmp(s1, s2) returns 'true' if s1 > s2
}

void print_array(char* array[], int len){
    for(int i = 0; i < len; i++){
        printf("%s ", array[i]);
    }
    printf("\n");
}

/*
** sort: sort array of strings in ascending order
*/
void sort(char* array[], int len){
    // YOUR CODE HERE
}

/*
** sort2: sort array of strings in ascending order using a *recursive* algorithm
*/
void sort2(char* array[], int len){
    // YOUR CODE HERE
}


// STRING COMPARISON
/*
** my_strcmp: return <0 if s<t, 0 if s==t, >0 if s>t
*/
int my_strcmp(char* s, char* t){

}

int main(){
    // MAKE SOME STRINGS
    char* s1 = "string 1";
    char* s2 = "hello, world!";
    char* s3 = "about";
    char* s4 = "zebra";

    // TEST SORT
    printf("TESTING sort\n\n");
    char* arr1[] = {s1, s2, s3, s4};
    print_array(arr1, 4);
    // YOUR CODE HERE

    printf("TESTING sort2\n\n");
    char* arr2[] = {s1, s2, s3, s4};
    print_array(arr2, 4);
    // YOUR CODE HERE

    printf("TESTING my_strcmp\n\n");
    // YOUR CODE HERE
}
