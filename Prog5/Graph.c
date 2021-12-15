#include <stdlib.h>
#include <stdio.h>
#include "List.h"
#include "Graph.h"

typedef struct Graph{
    int num_vertices;
    int num_edges; 
    ListPtr *adjacency_list; // Is an array of ListPtrs for faster access
} Graph;

int graph_dataCompare(void *obj1, void *obj2){
     
    int *object1 = (int *)obj1; 
    int *object2 = (int *)obj2; 
    if (*object1 == *object2){
        return 0; 
    }
    else{
        return -1; 
    }
}

void graph_dataPrinter(void *obj){
    int *data = (int*)obj; 
    printf("%d\n", *data); 
}

void graph_freeData(void *data){
    // free(data); 
    // data = NULL; 
}

// Hints: You will need to implement a ListPtr DataCompare, DataPrinter and 
//        freeData for the lists used in the adjacency list. These will be ints.
//        You can copy this from the ones in prog5.c, but they should have different name to avoid a namesapce collision.
//TODO: Implement all functions from the header file.
Graph *graph_create(int numVertices){
    Graph *temp_graph = (Graph *)malloc(sizeof(Graph)); 
    if(temp_graph == NULL){
        return temp_graph; 
    }
    temp_graph -> num_vertices = numVertices; 
    temp_graph -> num_edges =0; 
    temp_graph -> adjacency_list = calloc(temp_graph -> num_vertices, sizeof(ListPtr *)); 
    int i; 
    for(i =0; i < temp_graph -> num_vertices; i++){
        temp_graph -> adjacency_list[i] = list_create(graph_dataCompare, graph_dataPrinter, graph_freeData); 
    }
    return temp_graph; 
}

/**
 * @brief Destroys the memory used by the graph.
 * 
 * @param g The graph to destroy
 */
void graph_destroy(Graph *g){
    if (g == NULL) {
        return g; 
    }
    else{
        for(int i = 0; i < g->num_vertices; i++) {
            list_destroy(g->adjacency_list[i], false);      // Needs to be fixed
        }
        free(g->adjacency_list);
        free(g);
        g = NULL;
    }
   
}

/**
 * @brief Adds a new undirected, unweighted edge to the graph between 2 nodes
 * 
 * @param g The graph to add the edge to
 * @param v1 The vertex to add the edge to
 * @param v2 The second vertex to add the edge to
 * @return true If the operation was succesfull
 * @return false If the operation failed. E.g. node out of bounds, edge already exists
 */
bool graph_add_edge(Graph *g, int v1, int v2){
    int *object1 = (int *)malloc(sizeof(int));
    int *object2 = (int *)malloc(sizeof(int));
    // int *o1 = (int *)malloc(sizeof(int));
    int *o2 = (int *)malloc(sizeof(int));
    *o2 = v2; 
    if(g == NULL){
        return false; 
    }
    if((v1 >= 0 && v1 <= g -> num_vertices)&&(v2 >= 0 && v2 <= g -> num_vertices)){
        int i; 
        for(i =0; i < list_length(g -> adjacency_list[v1]); i++){
            if(list_get_index(g -> adjacency_list[v1], i) == o2){
                return false; 
            }
        }
        *object1 = v1; 
        *object2 = v2; 
        list_append(g->adjacency_list[v2], object1);
        list_append(g->adjacency_list[v1], object2);
        g -> num_edges++; 
        return true;         
    }
    else{
        return false; 
    }
}

/**
 * @brief Resize graph to add more vertices.
 * 
 * @param g The graph to add vertices to
 * @param numVertices The number of new vertices to add
 * @return true If the operation was succesfull
 * @return false If the operation failed. E.g realloc failed
 */
bool graph_add_nodes(Graph *g, int numVertices){
    if(g == NULL){
        return false; 
    }
    else{
        int newSize = g -> adjacency_list + numVertices; 
        g->adjacency_list = (ListPtr *)realloc(g->adjacency_list, newSize *sizeof(ListPtr));   
        int i; 
        for (i = g->num_vertices; i < newSize; i++) {
            g->adjacency_list[i] = list_create(graph_dataCompare, graph_dataPrinter, graph_freeData);
        }
        g->num_vertices += numVertices;    
        return true;
    }
}

/**
 * @brief Removes an edge from the graph
 * 
 * @param g The graph to remove the edge from
 * @param v1 One vertex of the edge
 * @param v2 The second vertex of the edge
 * @return true If the operation was succesfull
 * @return false If the operation failed. E.g. edge does not exist, vertices not in graph
 */
bool graph_remove_edge(Graph *g, int v1, int v2){
    int *o1 = (int *)malloc(sizeof(int));
    int *o2 = (int *)malloc(sizeof(int));
    *o1 = v1; 
    *o2 = v2; 
    int count =0; 
    if((v1 >= 0 && v1 <= g -> num_vertices)&&(v2 >= 0 && v2 <= g -> num_vertices)){
        int i; 
        for(i =0; i < list_length(g -> adjacency_list[v1]); i++){
            if ((*(int*)list_get_index(g -> adjacency_list[v1], i)) == v2){
                list_del_index(g->adjacency_list[v1], i);
                count++; 

            } 
        }
        for(i =0; i < list_length(g -> adjacency_list[v2]); i++){
            if ((*(int*)list_get_index(g -> adjacency_list[v2], i)) == v1){
                list_del_index(g->adjacency_list[v2], i);
                count++; 
            }
        }
        if(count == 2){
            g -> num_edges --; 
            return true;
        }  
    }
    else{
        return false; 
    }
}

/**
 * @brief Decides if the graph has an edge between 2 nodes.
 * 
 * @param g The graph to check
 * @param v1 Vertex 1 the edge should connect to
 * @param v2 Vertex 2 the edge should connect to
 * @return true If the graph has the edge
 * @return false If the edge does not exist
 */
bool graph_has_edge(Graph *g, int v1, int v2){
    int *o1 = (int *)malloc(sizeof(int));
    int *o2 = (int *)malloc(sizeof(int));
    *o1 = v1; 
    *o2 = v2;
    if((v1 >= 0 && v1 <= g->num_vertices)&&(v2 >= 0 && v2 <= g->num_vertices)){
        int i; 
        if ((list_find_element(g -> adjacency_list[v2], o1) != -1)&&(list_find_element(g -> adjacency_list[v1], o2) != -1)){ 
            return true; 
            
        }
        return false; 
    }
    else{
        return false; 
    }
}


/**
 * @brief Gets the neighbors of a vertex in a graph.
 * 
 * @param g The graph to get teh neighbors from
 * @param vertex The vertex to get the neighbors for
 * @return ListPtr If the operation suceeded, a list of int* to every neighbouring vertex, otherwiese NULL.
 */
ListPtr graph_get_neighbors(Graph *g, int vertex){
    if (vertex > 0 && vertex < g->num_vertices) {
        if(g -> adjacency_list[vertex] == NULL){
            return NULL; 
        }
        return g->adjacency_list[vertex];
    }
    else{
        return NULL;
    }
    
}

/**
 * @brief Gets the number of vertices in the graph.
 * 
 * @param g The graph to count the vertices for
 * @return int The number of vertices
 */
int graph_num_vertices(Graph *g){
    return g -> num_vertices; 
}

/**
 * @brief Gets the number of edges in the graph.
 * 
 * @param g The graph to count the number of edges for
 * @return int The number of edges
 */
int graph_num_edges(Graph *g){
    return g -> num_edges;
}