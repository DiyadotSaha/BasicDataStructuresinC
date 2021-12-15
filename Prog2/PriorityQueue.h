#ifndef __PRIORITYQUEUE_H_
#define __PRIORITYQUEUE_H_

//----------------------------------------------------
// PriorityQueue.h
// Header file for Priority Queue ADT
// Priority Queue implementation using a (min) heap
// ---------------------------------------------------

// Priority Queue Functionalities ---------------------------------------

// return min element in priority queue
int get_min(Heap* h);

// remove and return the min elemenet in priority queue
int extract_min(Heap* h);

// increase priority of element i to 'new_value'
void increase_priority(Heap* h, int i, int new_value, int idn);

// insert element with priority 'value' into the priority queue
void insert(Heap* h, int id, int value);

#endif // __PRIORITYQUEUE_H_