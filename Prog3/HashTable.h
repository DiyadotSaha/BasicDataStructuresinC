/**
 * @brief Hashes a string key to a value.
 * 
 * @param str The string to hash 
 * @return unsigned long The integer representation
 */
unsigned long ht_string2int(char *str);

/**
 * @brief Computes the array index in the hash table for a given key.
 * 
 * @param key The key to compute the element for
 * @param slots The number of slots in the hash table.
 * @return unsigned int 
 */
unsigned int ht_hash(char *key, unsigned int slots);