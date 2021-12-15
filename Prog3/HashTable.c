#include "HashTable.h"

unsigned long ht_string2int(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

//TODO: Implement
unsigned int ht_hash(char *key, unsigned int slots) {
    //printf("Has number: %d\n", ht_string2int(key) % slots);
    return ht_string2int(key) % slots; 
}