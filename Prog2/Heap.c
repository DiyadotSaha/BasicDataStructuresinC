// Implementation of (Min) Heap
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<math.h>
#include"Heap.h"


// TODO: Implement funcs for fetching parent and left/right child

int parent(int i){ 
    return floor(i/2);  
}

int left(int i){
    int l = (2*i); 
    return l; 
}

int right(int i){
    int r = (2*i)+1;
    return r; 
}

// trying to recieve the right child of the heap


//------------------------------------------------------------------------

// TODO: Helper function for swapping A[i] and A[j] elements in an array
void swap(int* A, int i, int j){
    int temp = A[i];
    A[i] = A[j]; 
    A[j] = temp; 
}

//------------------------------------------------------------------------

/* TODO: declare the Heap struct as in the header file
This Heap struc has the following fields:
- len: length of the array used for implementing the heap
- size: number of elements in the backbone array that are 'heapified' or ordered as heap
- array: (pointer to) array used for implementing the heap
- id: (pointer to) array of client id used for implementing the heap
*/
typedef struct Heap{
    int len; 
    int size; 
    int *array; 
    int *id;  
}Heap; 


//------------------------------------------------------------------------

/* TODO: implement initializeHeap function which instantiates a heap using malloc.
It returns a pointer to the instantiated heap
*/
Heap* initializeHeap(int len, int h_size, int* arr, int* id){
    Heap *temp_heap = (Heap*)malloc(sizeof(Heap)); 
    temp_heap -> len = len; 
    temp_heap -> size = h_size; 
    temp_heap -> array = arr; 
    temp_heap -> id = id;
    return temp_heap;  
}


//------------------------------------------------------------------------


/*  TODO: implement heap destructor that frees memory allocated to heap */
void destructHeap(Heap* h){
    free(h); 
}

//------------------------------------------------------------------------

/* TODO: implement 'heapify' function, given a heap pointer and an index i
This function maintain (min) Heap property given an index i for heap h
*/
void heapify(Heap* h, int i){
    int left_i = left(i);  
    int right_i = right(i); 
    int heap_min; 
    if((left_i <= h->size) && (h->array[left_i]< h-> array[i])){            // checks for boundaries of the left
        heap_min = left_i; 
    }
    else{
        heap_min = i;                                                       // reached the end of the left 
    }
    if((right_i<=h->size) && (h->array[right_i]< h-> array[heap_min])){     // checks for boundaries of the right
        heap_min = right_i; 
    }
    if(heap_min != i){                                                      // if not reached the end of the heap 
        swap(h->array, i, heap_min);                                        // swap with the min 
        swap(h->id, i, heap_min);                                           // swap with the min for id 
        heapify(h, heap_min);                           
    }
}


//------------------------------------------------------------------------

/* TODO: implement array_to_heap function
You may use initializeHeap function for implementing this function
*/
Heap* array_to_Heap(int* A, int* id, int len, int size){
    Heap *temp_heap = initializeHeap(len, size, A, id);             // make a heap 
    temp_heap -> size = temp_heap -> len;                           // make sure size = len 
    for(int i = (temp_heap -> len)/2; i> 1; i--){                   // start from half way and start sorting
        heapify(temp_heap, i);
    }
    return temp_heap; 
}

//------------------------------------------------------------------------

/* TODO: implement utility functions:
- size(): returns the size field of a heap
- len(): returns the length field of a heap
*/
int size(Heap* h){
    return h->size; 
}

int len(Heap* h){
    return h->len; 
}

void printHeap(Heap* h){
    for(int i=0; i<size(h); i++){
        printf("%d ", h->id[i]);                    //prints out the IDs 
    }
}


