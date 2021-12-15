#include "List.h"
#include "HashTable.h"
#include "Dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dictionary {
int		slots;				// total number of slots in hash table
int		size;				// number of elements currently in dictionary
ListPtr  *hash_table;	    // hash_table is array of ListPtrs
} Dictionary;			// dictionary is maintained as a hash table.

//TODO: Implement a key comparison function to pass to list. (This only needs to check for equality)
//Hint: Look at List.h to see what kind of comparison function the list expects

int dataCompare(void *obj1, void *obj2){
    KVPair *object1 = obj1; 
    KVPair *object2 = obj2; 
    int compareValue = strcmp(object1 -> key, object2 -> key);  
    return compareValue; 
}

//TODO: Implemement all functions from headers
Dictionary *dictionary_create(int hash_table_size, void (*dataPrinter)(void *data), void (*freeData)(KVPair *kvPair)){
    Dictionary* temp_dict = (Dictionary*) malloc(sizeof(Dictionary));
    temp_dict -> slots = hash_table_size; 
    temp_dict -> size = 0; 
    temp_dict -> hash_table = (ListPtr *)calloc(sizeof(ListPtr), hash_table_size); 
    int i; 
    //for looping through each slot and creating an empty list 
    for(i =0; i < temp_dict -> slots; i++){
        temp_dict -> hash_table[i] = list_create(dataCompare,dataPrinter, (void*)(void*)freeData); 
    }  
    return temp_dict; 
}

void dictionary_destroy(Dictionary *d, bool freeData){
    int i; 
    //looping through all the slots and destroying list in each slot 
    for(i =0; i< d->slots; i++){
        list_destroy(d->hash_table[i], freeData); 
    }
    free(d -> hash_table); 
    free(d); 
}

bool dictionary_insert(Dictionary *D, KVPair *elem){
    int index = ht_hash(elem -> key, D->slots);
    bool checker = list_append(D -> hash_table[index], elem); //if found don't insert at all 
    if(!checker){
        return false; 
    }
    else{                                                      // else add and increase the size
        D -> size = (D -> size) + 1;
        return true; 
    }                
}

KVPair *dictionary_delete(Dictionary *D, char *key){
    KVPair* foundelement = dictionary_find(D, key);                    
    if(foundelement != NULL){                                   //if found in dict delete that element
        int index = ht_hash(key, D -> slots);
        int found = list_find_element(D -> hash_table[index], foundelement);    // find element in that spot
        D -> size  = (D -> size) -1;                                               
        return list_del_index(D->hash_table[index], found); 
    }
    else{                                                       //else return a NULL pointer
        return NULL; 
    }
}

KVPair *dictionary_find(Dictionary *D, char *k){
    int found;  
    KVPair* element = (KVPair*) malloc(sizeof(KVPair)); 
    element -> key = k;                             //create a temp KV pair to store the value
    element -> value = 1; 
    int index = ht_hash(k, D->slots); 
    found = list_find_element(D->hash_table[index], element); //if found return the list obj
    if(found == -1){
        //free(element);                              
        return NULL;                                       //else return a NULL obj 
    } 
    else{
        return list_get_index(D->hash_table[index], found); 
    }           

}

void dictionary_print(Dictionary *D){
    int i; 
    for(i = 0; i < D -> slots; i++){
        if(D -> hash_table[i] != NULL){         //loop through each list and list_print each list
            list_print(D->hash_table[i]);
        } 
    }
}

int dictionary_size(Dictionary *D){
    return D -> size; 
}