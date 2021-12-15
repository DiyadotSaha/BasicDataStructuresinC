#include <stdbool.h>
#ifndef DICT_HEADER
#define DICT_HEADER
typedef struct {
	void *key;		// key for dictionary element
	void *value;	// generic pointer to value of dictionary element
}	KVPair;		// key:value pair of dictionary elements

typedef struct Dictionary Dictionary;
#endif

// -------------------------------
// Function headers
// -------------------------------

/**
 * @brief Creates a new kvpair.
 * 
 * @param key The key to set
 * @param value The value to set.
 * @return KVPair* The created KVPair.
 */
KVPair *kvpair_create(void *key, void *value);

/**
 * @brief Creates a new dictionary.
 * 
 * @param hash_key The function to use to hash the key.
 * @param compareKeys The function used to compare 2 keys.
 * @param hash_table_size The size of the hash table for the dictionary
 * @param dataPrinter Function used to print the value in the KVPair 
 * @param freeData The function to use to free a KVPair
 * @return Dictionary* The newly created dictionary
 */
Dictionary *dictionary_create(int hash_table_size,
								unsigned long (*hash_key)(void *key),
								int (*compareKeys)(void *void_kv1, void *void_k),
								void (*dataPrinter)(void *data),
								void (*freeData)(void *kvPair));

/**
 * @brief Destorys the memory taken up by the dicitonary
 * 
 * @param d The dictionary to destroy
 * @param freeData If to free data contained within the dictionary
 */
void dictionary_destroy(Dictionary *d, bool freeData);


/**
 * @brief Insert a key value pair into the dictionary
 * 
 * @param D The dictionary to insert into
 * @param elem The KVPair to insert
 * @return true If the operation succeeded
 * @return false If there already exists an element with the same key in the dictionary
 */
bool dictionary_insert(Dictionary *D, KVPair *elem);


/**
 * @brief Removes an entry from the dictionary, returning the removed KVPair. Returns NULL if key not in dictionary.
 * 
 * @param D The dictionary to remove the entry from
 * @param key The key to remove
 * @return KVPair* The KVPair for the key that was removed, or NULL.
 */
KVPair *dictionary_delete(Dictionary *D, void *key);

/**
 * @brief Gets the entry from the dictionary for the given key. Returns NULL if not in dictionary. 
 * 
 * @param D The dictionary to get the KVPair for
 * @param k The key to find the KVPair for
 * @return KVPair* The KVPair found, or NULL.
 */
KVPair *dictionary_find(Dictionary *D, void *k);

/**
 * @brief Gets the size of the dictionary.
 * 
 * @param D The dictionary to get the size of
 * @return int THe number of items in the dictionary
 */
int dictionary_size(Dictionary *D);

/**
 * @brief Prints the dictionary to stdout in format k: v\n
 * 
 * @param D The data to print
 */
void dictionary_print(Dictionary *D);