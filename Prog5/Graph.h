#include "List.h"

typedef struct Graph Graph;

/**
 * @brief Creates a new graph
 * 
 * @param numVertices The number of vertices in the graph. 
 * @return Graph Pointer to a new graph object
 */
Graph *graph_create(int numVertices);

/**
 * @brief Destroys the memory used by the graph.
 * 
 * @param g The graph to destroy
 */
void graph_destroy(Graph *g);

/**
 * @brief Adds a new undirected, unweighted edge to the graph between 2 nodes
 * 
 * @param g The graph to add the edge to
 * @param v1 The vertex to add the edge to
 * @param v2 The second vertex to add the edge to
 * @return true If the operation was succesfull
 * @return false If the operation failed. E.g. node out of bounds, edge already exists
 */
bool graph_add_edge(Graph *g, int v1, int v2);

/**
 * @brief Resize graph to add more vertices.
 * 
 * @param g The graph to add vertices to
 * @param numVertices The number of new vertices to add
 * @return true If the operation was succesfull
 * @return false If the operation failed. E.g realloc failed
 */
bool graph_add_nodes(Graph *g, int numVertices);

/**
 * @brief Removes an edge from the graph
 * 
 * @param g The graph to remove the edge from
 * @param v1 One vertex of the edge
 * @param v2 The second vertex of the edge
 * @return true If the operation was succesfull
 * @return false If the operation failed. E.g. edge does not exist, vertices not in graph
 */
bool graph_remove_edge(Graph *g, int v1, int v2);

/**
 * @brief Decides if the graph has an edge between 2 nodes.
 * 
 * @param g The graph to check
 * @param v1 Vertex 1 the edge should connect to
 * @param v2 Vertex 2 the edge should connect to
 * @return true If the graph has the edge
 * @return false If the edge does not exist
 */
bool graph_has_edge(Graph *g, int v1, int v2);


/**
 * @brief Gets the neighbors of a vertex in a graph.
 * 
 * @param g The graph to get teh neighbors from
 * @param vertex The vertex to get the neighbors for
 * @return ListPtr If the operation suceeded, a list of int* to every neighbouring vertex, otherwiese NULL.
 */
ListPtr graph_get_neighbors(Graph *g, int vertex);

/**
 * @brief Gets the number of vertices in the graph.
 * 
 * @param g The graph to count the vertices for
 * @return int The number of vertices
 */
int graph_num_vertices(Graph *g);

/**
 * @brief Gets the number of edges in the graph.
 * 
 * @param g The graph to count the number of edges for
 * @return int The number of edges
 */
int graph_num_edges(Graph *g);