#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"Heap.c"
#include"PriorityQueue.h"


/* TODO: implement get_min
returns minumum element in heap/shortest processing time
*/
/*
 * params: 
 * 	h: pointer to the heap  
 * 
 * returns minimum integer in the heap  
 */
int get_min(Heap* h){ 
    if(h->size <= 0){                       //checking if heap is empty or not
        return; 
    }
    else{
        heapify(h,1); 
        return h -> id[1];                  //return the first element cause min-heap
    }
    
}


//------------------------------------------------------------------------

/* TODO: implement extract_min
extracts and returns min element in heap
note that heap property must be maintained after extraction
also check for valid input (cannot extract from empty heap)
*/
/*
 * params: 
 * 	h: pointer to the heap  
 * 
 * removes the minimum integer from the heap and sorts the heap 
 * accordingly
 */
int extract_min(Heap* h){
    int minimum; 
    if(h->size <= 0){
        return; 
    }
    else{
        minimum = h -> id[1]; 
        h -> array[1] = h -> array[h -> size];         // moving the last node up to front 
        h -> id[1] = h -> id[h->size];                 // moving the last node of id to the front  
        h -> size = h -> size -1;                      // decreasing the size by 1 
        heapify(h, 1);                                 //making sure the heap is sorted 
        return minimum;
    }
     
}


//------------------------------------------------------------------------

/* TODO: implement increase_priority
This function increases priority of element at index i to 'new_value'
*/
/*
 * params: 
 * 	h: pointer to the heap
 *  i: index priority needs to be increased
 *  new_value: new interger to be added into the array
 *  idn: new integer to be added into the id array
 * 
 * increases the priority of the array and the idarray
 * at the index i  
 */
void increase_priority(Heap* h, int i, int new_value, int idn){
    if(new_value > h-> array[i]){
        return; 
    }
    h->array[i] = new_value;                    //adding new value to array 
    h->id[i] = idn;                             //adding new value to id 
    while((i>1) && (h->array[parent(i)] > h->array[i])){ 
        swap(h->array, i, parent(i));           //moving the element up  
        swap(h->id, i, parent(i));              
        heapify(h,1); 
        i = parent(i); 
    }
}

//------------------------------------------------------------------------

/* TODO: implement insert functionality
This function inserts priority 'value' into heap
You will need to have implemented the increase_priority and use it here
*/
/*
 * params: 
 * 	h: pointer to the heap  
 *  id: id needed to be inserted 
 *  value: value needed to be inserted 
 * 
 * inserts an id and array into the given heap   
 */

void insert(Heap* h, int id, int value){
    h -> size = h -> size +1;                   // increasing the size to 1
    h -> array[h -> size] = __INT_MAX__;        // setting the last value to infinity 
    h -> id[h->size] = __INT_MAX__;             // setting the last value to infinity
    increase_priority(h, h->size, value, id);   
}