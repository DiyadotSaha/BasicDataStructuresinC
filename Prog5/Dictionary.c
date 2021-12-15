#include "List.h"
#include "Dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Dictionary {
int		slots;				// total number of slots in hash table
int		size;				// number of elements currently in dictionary
unsigned long (*hash_key_f)(void *key);
ListPtr  *hash_table;	    // hash_table is array of ListPtrs
} Dictionary;			// dictionary is maintained as a hash table.

KVPair *kvpair_create(void *key, void *value) {
    KVPair *kv = malloc(sizeof(KVPair));
    kv->key = key;
    kv->value = value;
    return kv;
}

unsigned int ht_hash(Dictionary *d, void *key) {
    return d->hash_key_f(key) % d->slots;
}

/**
 * @brief Creates a new dictionary.
 * 
 * @param hash_table_size The size of the hash table for the dictionary
 * @param dataPrinter Function used to print the value in the KVPair 
 * @param freeData The function to use to free a KVPair
 * @return Dictionary* The newly created dictionary
 */
Dictionary *dictionary_create(int hash_table_size, unsigned long (*hash_key)(void *key), int (*compareKeys)(void *void_kv1, void *void_k), void (*dataPrinter)(void *data), void (*freeData)(void *kvPair)) {
    Dictionary *d = (Dictionary *)malloc(sizeof(Dictionary));
    d->slots = hash_table_size;
    d->size = 0;
    d->hash_table = (ListPtr *)calloc(sizeof(ListPtr), hash_table_size);
    d->hash_key_f = hash_key;
    for (int i = 0; i < d->slots; i++) {
        d->hash_table[i] = list_create(compareKeys,
                                        dataPrinter,
                                        freeData);
    }
    return d;
}

/**
 * @brief Destorys the memory taken up by the dicitonary
 * 
 * @param d The dictionary to destroy
 * @param freeData If to free data contained within the dictionary
 */
void dictionary_destroy(Dictionary *d, bool freeData) {
    for (int i = 0; i < d->slots; i++) {
        list_destroy(d->hash_table[i], freeData);
    }
    free(d->hash_table);
    free(d);
}


/**
 * @brief Insert a key value pair into the dictionary
 * 
 * @param D The dictionary to insert into
 * @param elem The KVPair to insert
 * @return true If the operation succeeded
 * @return false If there already exists an element with the same key in the dictionary
 */
bool dictionary_insert(Dictionary *D, KVPair *elem) {
    int slot = ht_hash(D, elem->key);
    ListPtr l = D->hash_table[slot];
    if (list_find_element(l, elem) >= 0) {
        return false;
    } else {
        list_append(l, elem);
        D->size++;
        return true;
    }
}


/**
 * @brief Removes an entry from the dictionary, returning the removed KVPair. Returns NULL if key not in dictionary.
 * 
 * @param D The dictionary to remove the entry from
 * @param key The key to remove
 * @return KVPair* The KVPair for the key that was removed, or NULL.
 */
KVPair *dictionary_delete(Dictionary *D, void *key) {
    int slot = ht_hash(D, key);
    ListPtr l = D->hash_table[slot];
    KVPair temp_pair;
    temp_pair.key = key;
    int idx = list_find_element(l, &temp_pair);
    if (idx == -1) {
        return NULL;
    } else {
        D->size--;
        return list_del_index(l, idx);
    }
}

/**
 * @brief Gets the entry from the dictionary for the given key. Returns NULL if not in dictionary. 
 * 
 * @param D The dictionary to get the KVPair for
 * @param k The key to find the KVPair for
 * @return KVPair* The KVPair found, or NULL.
 */
KVPair *dictionary_find(Dictionary *D, void *k) {
    int slot = ht_hash(D, k);
    ListPtr l = D->hash_table[slot];
    KVPair temp_pair;
    temp_pair.key = k;
    int idx = list_find_element(l, &temp_pair);
    if (idx == -1) {
        return NULL;
    } else {
        return list_get_index(l, idx);
    }
}


/**
 * @brief Prints the dictionary to stdout in format k: v\n
 * 
 * @param D The data to print
 */
void dictionary_print(Dictionary *D) {
    for (int i = 0; i < D->slots; i++) {
        list_print(D->hash_table[i]);
    }
    printf("\n");
}

/**
 * @brief Gets the size of the dictionary.
 * 
 * @param D The dictionary to get the size of
 * @return int THe number of items in the dictionary
 */
int dictionary_size(Dictionary *D) {
    return D->size;
}