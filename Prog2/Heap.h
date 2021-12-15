#ifndef __HEAP_H_
#define __HEAP_H_

//----------------------------------------------------
// Heap.h
// Header file for Heap
// Heap implementation using an array of integers
// ---------------------------------------------------

typedef struct Heap Heap;

// Constructor-Destructors --------------------------

// initialize Heap of size 'h_size' from aray of length 'len'
Heap* initializeHeap(int len, int h_size, int* arr, int* id);

// free memory allocated to Heap pointer h
void destructHeap(Heap* h);


// Heap Functionalities ------------------------------

// Maintain Heap property given an index i for heap pointed to by h
void heapify(Heap* h, int i);

// Build heap from array of ints A
Heap* array_to_Heap(int* A, int* id, int len, int size);

// Return int corresponding to size of Heap* h

int size(Heap* h);

int len(Heap* h);


// Helper functions for fetching parent, left or right child
int parent(int i);

int left(int i);

int right(int i);

// Helper for replacing A[i] and A[j] elements in an array
void swap(int* A, int i, int j);

void printHeap(Heap* h);

#endif // __HEAP_H_