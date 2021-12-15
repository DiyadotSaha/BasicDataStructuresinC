#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"Queue.h"
// Implemeting Queue

/*
TODO: define the Queue structure using 'typedef struct Queue' - this queue holds integer values
the Queue struct has the following fields:
- head: corresponding to the head of the queue
- tail: indicating the tail of the queue
- length: length of the array used for implementing the queue
- count: number of elements in the queue
- array: (pointer to) the array used for implementing the queue
- id: (pointer to) the array of client id used for implementing the queue
*/
typedef struct Queue{
    int head; 
    int tail; 
    int length; 
    int count; 
    int* array; 
    int* id; 
}Queue; 


//------------------------------------------------------------------------

/*
TODO: implement the initializeQueue - this function instantiates the Queue struct using malloc and sets the values for the fields.
It returns a pointer to the instantiated Queue
*/
Queue* initializeQueue(int n, int* arr, int* id){
    Queue* temp = (Queue*) malloc(sizeof(Queue)); 
    temp -> head = 0;
    temp -> length = n;
    temp -> array = arr;
    temp -> count = 0;
    temp -> tail = -1; 
    temp -> id = id; 
    return temp;
}

//------------------------------------------------------------------------

/*
TODO: implement Queue destructor - this function frees memory allocated to Queue
*/
void destructQueue(Queue* q){
    free(q); 
}

//------------------------------------------------------------------------

/* TODO: implement the 'enqueue' functionality
This function takes in a queue pointer and int service time 'ser' and adds 'ser' to queue
*/
void enqueue(Queue* q, int i, int ser){ 
    if(q-> count >= q -> length){                               // if array is full don't add anything
        return; 
    }
    else{
        q-> tail = (q-> tail+1)%(q -> length);                  // incrementing the tail cause it's -1
        q -> array[q->tail]= ser;                               // storing new value at the end
        q -> id[q->tail] = i;                                   // storing new value at the end of id
        q -> count++;                                           // incrementing the count
    }   
}

//------------------------------------------------------------------------

/* TODO: implement the 'dequeue' functionality
This function takes in a queue pointer and removes element from head of the queue
*/
int dequeue(Queue* q){
    if(count <= 0){                                     // if nothing in the queue return nothing
        return; 
    } 
    else{   
        int del_element = q-> id[q-> head];             // storing the element to be deleted 
        q->head = (q->head+1)%(q->length);              //increasing the head by 1 
        q -> count --;                                  // decreasing count after deletion
        return del_element;                             // returning the stored element
    }
}
//------------------------------------------------------------------------

/* TODO: implement the printQueue
This function takes in a queue pointer and prints the contents of the queue in order (head to tail)
*/
void printQueue(Queue* q){ 
    if(q -> count == 0){                                // checking if the queue is empty
        printf("Queue empty!\n"); 
    }
    else{
        for(int j = q -> head; j< (q->tail+1); j++){    //for looping through the head to tail printing everyhting
            printf(" %d ", q->id[j]); 
        }
    } 
}


//------------------------------------------------------------------------

/* TODO: implement the count
This function takes in a queue pointer and returns the 'count' field of the queue
*/
int count(Queue* q){
    return q-> count;               //returning count 
}

