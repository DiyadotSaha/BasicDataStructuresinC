typedef struct PQueue PQueue;

/**
 * @brief Creates a new priority queue. Not: This priority queue is based on a heap, so is not a stable sort.
 * 
 * @param initialLength The number of initially available slots. More will automatically be added if needed
 * @return PQueue* A newly reated priority queue
 */
PQueue* pqueue_create(int initialLength);

/**
 * @brief Destroys memory used by the priority queue
 * 
 * @param pq The priority queue to destroy
 */
void pqueue_destroy(PQueue* pq);

/**
 * @brief The number of elements currently stored in the queue
 * 
 * @param pq The priority queue to get the number of elements in
 * @return int The number of elements in the priority queue
 */
int pqueue_size(PQueue* pq);

/**
 * @brief Prints the contents of the priority queue.
 * 
 * @param pq The priority queue to print
 */
void pqueue_print(PQueue* pq);

/**
 * @brief Gets the id with the minimum priority value from the priority queue
 * 
 * @param pq The priority queue to get the minimum element from
 * @return int The element (id) with the lowest priority
 */
int pqueue_get_min(PQueue* pq);

/**
 * @brief Extracts the id with the minimum priority value from the priority queue
 * 
 * @param pq The priority queue to extract the minimum element from
 * @return int The element (id) with the lowest priority
 */
int pqueue_extract_min(PQueue* pq);

/**
 * @brief Inserts an element into the priority queue.
 * 
 * @param pq The priority queue to insert the element into
 * @param id The id assosciated with the element to insert
 * @param priority The priority of the new element
 */
void pqueue_insert(PQueue* pq, int id, int priority);