#include <stdbool.h>
//----------------------------------------------------
// List.h
// Header file for List ADT
// Implement you List ADT as a linked
// list of events.
// ---------------------------------------------------

#ifndef LIST_HEADER
#define LIST_HEADER
typedef struct NodeObj{
    void *data;
    struct NodeObj* next;
} NodeObj;
typedef NodeObj* NodePtr;

typedef struct ListObj{
    NodePtr head;
    bool (*dataEqual)(void *obj1, void*obj2);
    void (*dataPrinter)(void *data);
    void (*freeData)(void *data);
    int length;
}ListObj;
typedef struct ListObj* ListPtr;
#endif



// Constructors-Destructors --------------------------

/**
 * @brief Creates a new list
 * 
 * @param dataEqual Function to use to check if 2 pieces of data are equal to each other
 * @param dataPrinter Function to use to print out a piece of data in the list
 * @param freeData Function to use to free data in a node when destroying the list
 * @return List The newly created list.
 */
ListPtr newList(bool (*dataEqual)(void *obj1, void*obj2), void (*dataPrinter)(void *data), void (*freeData)(void *data));

/**
 * @brief Frees the space taken up by the list
 * 
 * @param pL       A pointer to the list to deallocate. The pointer should be set to NULL
 * @param freeData If to also free the data contained within the list
 */
void freeList( ListPtr *pL, bool freeData);

// Access functions ----------------------------------

/**
 * @brief Gets the length of a list
 * 
 * @param L The list for which the length should be returned.
 * @return int The length of the list, or -1 if error
 */
int length( ListPtr L );

/**
 * @brief Returns the index of the search data in the list
 * 
 * @param L The list to check
 * @param comp The data to search for
 * @return int The index of the data in the list, or -1 if not in list
 */
int findElement(ListPtr L, void *comp);

/**
 * @brief Returns the data stored at the index i.
 * 
 * @param i The index to fetch
 * @return void* The data at the index, or NULL if out of range
 */
void *getElement( ListPtr L, int i);


// Manipulation functions ----------------------------

/**
 * @brief Deletes the entry at the specified index and returns the data from the entry.
 * 
 * @param L The list to delete the entry from.
 * @param i The index of the entry to remove
 * @return void* The data that was stored in that entry. Returns NULL if the entry does not exist.
 */
void *delElement( ListPtr L, int i );

/**
 * @brief Appends an entry to the list.
 * 
 * @param L    The list to append to
 * @param data The data to insert into the new entry.
 * @return true  If the append was succesfull
 * @return false If the entry could not be appended
 */
bool appendList( ListPtr L, void *data );

/**
 * @brief Inserts an entry into the list.
 * 
 * @param L      The list to insert the entry into
 * @param pos    The position into which to insert the entry
 * @param data   The data to insert into the entry
 * @return true  If the insert was succesfull
 * @return false If the insert could not be performed
 */
bool insertElement(ListPtr L, int pos, void *data);


// Other functions ----------------------------
/**
 * @brief Prints the data in the list in the format "%s\n" for each entry
 * 
 * @param L           The list to print
 */
void printList(ListPtr L);
