#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "PQueue.h"

typedef struct PQueue{
    int num_slots;
    int size;
    int* priority_arr;
    int* id_arr;
} PQueue;

// Implementation of (Min) Heap

int parent(int i){
    i += 1;
    return ((int) i / 2) - 1; // the int is there just in case
}

int left(int i){
    i += 1;
    return (2 * i) - 1; //If i not equals 0 return 2 x i else return 1
}

int right(int i){
    return left(i) + 1;
}

void swap(int *A, int i, int j){
    int temp = 0;
    temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

PQueue* pqueue_create(int initialLength) {
    PQueue* h = (PQueue *) malloc(sizeof(PQueue));
    assert(h != NULL);
    h->num_slots = initialLength;
    h->size = 0;
    h->priority_arr = (int*)calloc(sizeof(int), initialLength);
    h->id_arr = (int*)calloc(sizeof(int), initialLength);
    return h;
}

void pqueue_destroy(PQueue* h) {
    assert(h != NULL);
    free(h->priority_arr);
    free(h->id_arr);
    free(h);
}

void heapify(PQueue* h, int i){
    assert(h != NULL);
    int l = left(i);
    int r = right(i);
    int min = i;
    if (l <= h->size && h->priority_arr[l] < h->priority_arr[r]){
        min = l;
    }
    if (r <= h->size && h->priority_arr[r] < h->priority_arr[min]){
        min = r;
    }
    if ( min != i) {
        swap(h->priority_arr, i, min);
        swap(h->id_arr, i, min);
        heapify(h, min);
    }
}


int pqueue_size(PQueue* h){
    assert(h != NULL);
    return h->size;
}

void pqueue_print(PQueue* h){
    assert(h != NULL);
    int i;
    printf("PQueue:\n");
    for(i=0; i<h->size; i++){
        printf("%d [%d]\n",h->id_arr[i], h->priority_arr[i]);
    }
    printf("End of PQueue:\n");
}

int pqueue_get_min(PQueue* h){
    assert(h != NULL);
    assert(h->size > 0);
    return h->id_arr[0];
}

int pqueue_extract_min(PQueue* h){
    assert(h != NULL);
    int min_id = pqueue_get_min(h);
    h->priority_arr[0] = h->priority_arr[h->size - 1];
    h->id_arr[0] = h->id_arr[h->size - 1];
    h->size -= 1;
    heapify(h, 0);
    return min_id;
}

void pqueue_insert(PQueue* h, int id, int priority){
    assert(h != NULL);
    // Increaase heap size if needed
    if (h->num_slots == h->size) {
        h->priority_arr = realloc(h->priority_arr, sizeof(int) * (h->num_slots + 20));
        h->id_arr  = realloc(h->id_arr, sizeof(int) * (h->num_slots + 20));
        h->num_slots += 20;
    }
    h->priority_arr[h->size] = priority;
    h->id_arr[h->size] = id;
    h->size += 1;
    // Insert into correct position
    int i = h->size - 1;
    while (i > 0 && h->priority_arr[parent(i)] > h->priority_arr[i]){
        swap(h->priority_arr, i, parent(i));
        swap(h->id_arr, i, parent(i));
        i = parent(i);
    }    
}