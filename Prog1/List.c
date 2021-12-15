#include <stdio.h>
#include <stdlib.h>
#include "List.h" 



ListPtr newList(bool (*dataEqual)(void *obj1, void*obj2), void (*dataPrinter)(void *data), void (*freeData)(void *data)){
    ListPtr temp = (ListPtr) malloc(sizeof(ListObj)); 
    temp -> head = NULL; 
    temp -> dataEqual = dataEqual;
    temp -> dataPrinter = dataPrinter; 
    temp -> freeData = freeData; 
    temp -> length = 0; 
    return temp; 
}

// check is the for loops is needed to traverse throught the list or the param called the length can be used while being updated throught
// the function 
// update the length length-- when the delete is called 
// update the length length++ when the add/ appened functio nis called.
int length(ListPtr L){
    /*NodePtr itterNode = malloc(sizeof(NodePtr));
    itterNode = L -> head; 
    //int max_data = itterNode -> data;
    int list_length = 1;  
    while(itterNode -> next != NULL){
        list_length+=1;
        itterNode = itterNode -> next;
    } 
    printf("%d", list_length); 
    printf("function length: %d\n", L -> length);*/
    return (L->length);  
}

// needs to handle the error checking and the conflicts in time and the name of the events
bool appendList( ListPtr L, void *data){
    NodePtr newNode = malloc(sizeof(NodePtr));
    NodePtr itterNode = malloc(sizeof(NodePtr));
    newNode -> data = data;                 //moves to the next node 
    newNode ->  next = NULL;                //makes to clear before appending
    if (L -> head == NULL){
        L -> head = newNode;                // if the list is empty  
        (L -> length)+=1; 
        return true; 
    }
    else{
        //adds to the end of the list loops until it finds the end
        itterNode = L-> head; 
        while(itterNode -> next != NULL){
            itterNode = itterNode -> next;          //increment the node 
        }
        itterNode->next = newNode;                  //increment 
        (L -> length) +=1;                            //increment the length of the list 
        return true; 
    }
    return false;     
}

// inserts elements at the middle of the list
bool insertElement(ListPtr L, int pos, void *data){
    NodePtr currNode = malloc(sizeof(NodePtr));
    NodePtr insertNode =  malloc(sizeof(NodePtr));
    insertNode -> data = data;                  //points to the data given 
    insertNode -> next = NULL;                  //makes to clear before appending
    int counter = 1;  
    currNode = L -> head;
    if(pos > L ->length){
        printf("Out of bounds"); 
        return false; 
    } 
    if(pos == 0){
        L -> head = insertNode;                 //inserts at the begining of the list 
        insertNode -> next = currNode;          // points to the next node 
        L -> length++; 
        return true; 
    }
    else{
        //loops till it finds the given index
        while(counter < pos){
            currNode = currNode -> next;            // inserts at the middle of the list 
            if(currNode-> data == NULL){
                break; 
            }
            counter++; 

        }
        // connect the prev to the current node and the current to the next node
        if(currNode-> data != NULL){
            insertNode-> next = currNode -> next; 
            currNode -> next = insertNode; 
            L-> length ++; 
            return true; 
        }
        else{
            printf("Out of bounds"); 
            return false; 
        }   
    }
     
}



// not working for the first element or the last element but is working for the elments in between
void *delElement( ListPtr L, int i){
    NodePtr itterNode = NULL;
    NodePtr prevNode = NULL; 
    NodePtr tempNode = NULL; 
    //NodePtr freeNode = NULL; 
    itterNode = L -> head;                  //points to the given data 
    int index_count = -1;                   // counter to check 
    if(i == 0){
        L-> head = itterNode -> next;  
        L -> length--; 
        return itterNode -> data; 
    }
    else if(i > L->length){
        return false; 

    }
    else{
        //when not the first elemnt iter through 
        while (itterNode-> next != NULL){
            index_count++; 
            if(index_count == i){
                break; 
            }
            prevNode = itterNode;                   //stores the previous node 
            itterNode = itterNode -> next;             // increments to the next node 
            prevNode -> next = itterNode;               // points the previous node to the current node
        }
        // breaks at the given index and deletes the specific node
        if(itterNode -> next == NULL){
            tempNode = prevNode; 
            prevNode -> next = NULL; 
            L -> length--;           
            return tempNode -> data; 
        }
        if(prevNode -> next == NULL){
            itterNode = itterNode -> next; 
        }
        else{
            prevNode -> next = itterNode -> next; 
        }
        itterNode -> next = NULL; 
        L -> length--;
        return prevNode -> data; 
    }
    return NULL;     
}


// find element work perfectly and return -1 when object not found
int findElement(ListPtr L, void *comp){ 
    NodePtr itterNode = malloc(sizeof(NodePtr));
    itterNode = L -> head; 
    int index = 0; 
    NodeObj* find_data = comp;
    if(L -> head == NULL){
        return -1; 
    }
    if((*L -> dataEqual)(itterNode-> data, comp)){ 
        return index;                               //returns index if the first element is the same 
    }
    index++;                                        // increments the index of the list 
    while(itterNode -> next != NULL){
        itterNode = itterNode -> next;
        if((*L -> dataEqual)(itterNode-> data, comp)){  
            return index;                               //gets  the index for the middle of the list 
        }
        else{
            index+=1;
        }
    }  
    return -1;
}


// prints everything perfectly 
void printList( ListPtr L ){
    // loops throught the linked list object and calls dataPrinter on each event
    NodeObj* itterNode = NULL;
    itterNode = L-> head; 
    if(L -> head == NULL){
        return;
    }
    while(itterNode -> next != NULL){
        // source: TA section Xiaoxue Zhang
        (*L -> dataPrinter)(itterNode-> data);              //running data printer 
        printf("%s","\n"); 
        itterNode = itterNode -> next; 
    } 
    (*L -> dataPrinter)(itterNode-> data);
    printf("%s","\n");
}


// iterates throught the list to return a data = event obj 
void *getElement( ListPtr L, int i){
    //NodeObj* itterNode = malloc(sizeof(NodeObj));
    NodeObj* itterNode = NULL;
    //printf("Hii"); 
    int listIndex =1; 
    itterNode = L -> head; 
    if(i<0){
        return NULL; 
    }
    else if(i>(L->length-1)){
        return NULL; 
    }
    else if(i == 0){
        return L-> head -> data;                //returns the first element for position 0
    }
    //when greater than the 0 iterrates through the list to give the element
    else if (i > 0 )
    {
        while(itterNode -> next != NULL){
            itterNode = itterNode -> next;
            if (i == listIndex){
                return itterNode-> data;                //returns the data at the given index 
            } 
            listIndex++;
        }   
    }
    else{
        return NULL;                        //if nothing else works just return a null obj 
    }
}




void freeList( ListPtr* pL, bool freeData){

}