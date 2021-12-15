#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<limits.h>
#include"Queue.h"
#include"Heap.h"
#include"PriorityQueue.h"

// Function signatures
void generateArrival(int i, Queue* q, Heap* h, int pMax);
int processQueue(Queue* q);


typedef struct Client{
    int* id;
    int* arrive;
    int* service;
    int* finish;
}Client;

Client* createClient(int* id, int* arrive, int* service, int* finish){
    Client* c = (Client *) malloc(sizeof(Client));
    c->id = id;
    c->arrive = arrive;
    c->service = service;
    c->finish = finish;
    return c;
}


/*
- generateArrival() would simulate arrival of clients.
- Only one client arrive at a time
- If an client is stochastically arrived and to be added, it will be added to both queue and priority queue
- the service time of the client is randomly generated from [1, sMax]
*/

void generateArrival(int i, Queue* q, Heap* h, int ser)
{
    enqueue(q, i, ser);
    insert(h, i, ser);
}

/*
- processQueue() would simulate client service
*/
int processQueue(Queue* q)
{
    int index = dequeue(q);
    return index;
}



int main(void)
{   
    /* PARAMETERS:
    - sMax: Maximum service time
    - num:  Total number of clients
    - seed: seed value for ensuring replicability
    - time: interval of arrive time between two clients
    */
    // declaring the parameters
    int serMax, num, seed, time;
    fscanf(stdin, "%d %d %d %d", &serMax, &num, &seed, &time);
    // setting the seed for replicability guarantees
    srand(seed);

    
    int id[num], arrive[num], service[num], finish[num];
    for(int i=0; i<num; i++){
        id[i] = i;
        arrive[i] = 0;
        service[i] = rand()%serMax + 1;
        finish[i] = INT_MAX;
    }

    Client *c = createClient(id, arrive, service, finish);
    
    // declaring arrays for implementation of heap and queue ADTs
    int qarray[num];
    int harray[num];
    int hid[num];
   
    // initializing the heap
    Heap* h = initializeHeap(num, 0, harray, hid);
    
    // initializing the queue
    Queue* q = initializeQueue(num, qarray, id);

    //running client
    for (int i = 0; i < num; i++){
        if(!i){
            //assuming the first client arrive at 0
            c->arrive[i] = 0;
        }
        else{
            //only one client would arrive at a time
            c->arrive[i] = c->arrive[i-1] + rand()%time + 1;
        }
    }

    printf("Client information:\n");
    printf("ClientID ArriveTime ServiceTime\n");
    for(int i=0; i<num; i++){
        printf("%-10d %-10d %-10d\n", c->id[i], c->arrive[i], c->service[i]);
    }
    printf("\n===== Service Start =====\n\n");


    int index = 0;
    int counter_Q = 0;    //Counter for queue
    int counter_P = 0;    //Counter for priority queue
    int k = 0;      //client in q
    int x = 0;      //client in p
    int num_p = 0;  //client processed in p
    //record the overall waiting time for queue and priority queue
    int wait_q = 0;
    int wait_p = 0;

    for(int i = 0; i< INT_MAX; i++){
        if(i == c->arrive[index]){
            printf("Time %-2d, Add %d\n", i, c->id[index]);
            generateArrival(index, q, h, c->service[index]);
            index++;
        }
        
        // Queue
        if(counter_Q) //queue processing busy
            counter_Q --;
        if(!counter_Q && count(q)){
            k = processQueue(q);    //Serving the kth client
            wait_q += i - c->arrive[k];
            counter_Q = c->service[k];
            printf("Time %-2d, Serve: %d (Q)\n", i, k);
        }

        // P Queue 
        if(counter_P){
            counter_P--;
        }
        if(!counter_P && size(h)){
            x = extract_min(h);
            wait_p += i - c->arrive[x];
            counter_P = c->service[x];
            printf("Time %-2d, Serve: %d (P)\n", i, x);
            num_p++;
        }

        if((!counter_Q && count(q) == 0 && k == num-1) && (!counter_P && size(h) == 0 && num_p == num))
            break;
    }
    printf("\n===== Service End =====\n");


    //printQueue(q);
    // printHeap(h);
  
    // free memory allocated to queue and heap
    destructHeap(h);
    destructQueue(q);
    free(c);

    printf("Queue:          Overall waiting time: %d\n", wait_q);
    printf("Priority Queue: Overall waiting time: %d\n", wait_p);
    
    return 0;
}
