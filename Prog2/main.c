#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<limits.h>
#include"Queue.h"
#include"Heap.h"
#include"PriorityQueue.h"


int main(void)
{
    int tester[] = {3, 7, 2, 1, 5, 4}; 
    int testerId[] = {5, 11, 3, 33, 21, 16}; 
    Heap *testh = array_to_Heap(tester, testerId, 5, 6);
    printHeap(testh); 
    //heapify(testh,1); 
    return 0;
}


