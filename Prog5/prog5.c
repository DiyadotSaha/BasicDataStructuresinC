#include "Graph.h"
#include "List.h"
#include "PQueue.h"
#include "Dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Point {
    int x;
    int y;
} Point;

Point *create_point(int x, int y) {
    Point *p = malloc(sizeof(Point));
    p->x = x;
    p->y = y;
    return p;
}
void Printpoint(void* point){ 
	Point *temp = (Point*) point; 
    printf("%d, %d\n", temp-> x, temp -> y); 
}

void list_DataPrinter(void* obj){
	int *temp = (int*) obj; 
    printf("%d\n", temp); 
}

int list_DataCompare(void* obj1, void* obj2){
	int *temp1 = (int*) obj1;
    int *temp2 = (int*) obj2;  
    if(temp1 == temp2){
        return 0; 
    }
    else{
        return -1; 
    }
}

int PointEqual(void* segment1, void* segment2){
	//printf("Inside Segment Equal \n"); 
	Point *temp1 = (Point*) segment1;
	Point *temp2 = (Point*) segment2;
	if((temp1 -> x == temp2 ->x)&&(temp1 ->y == temp2 -> y)){
		return 0; 
	}
	else{
		return -1; 
	}		
}

void freepoint(void*p){
    free(p);

}
//Hint: The ListPtrs will store ints for bfs and a_star.
//      You need to define the dataCompare, dataPrinter and freeData functions here. 


/**
 * @brief Implements the bst algorithm to find the shortest path between 2 nodes in an unweighted graph.
 * 
 * @param g The graph to search through
 * @param vertex_start The index of the vertex in the graph from where to start the search.
 * @param vertex_end The index of the vertex in the graph that needs to be reached.
 * @param vertices_explored The value in this pointer should be set to the number of vertices that were visited by the algorithm.
 * @return ListPtr A list of the nodes that make up the path from the start to the end, including the start and end nodes.
 */
ListPtr bfs(Graph *g, int vertex_start, int vertex_end, long *vertices_explored) {
    //Perform bfs traversal. Make sure to store who the parent of each node in your traversal is.
    //final list contaning the path
    ListPtr bfs_path = list_create(list_DataCompare, list_DataPrinter, freepoint); 
    //contains the queue we need to itterate
    ListPtr frontier = list_create(list_DataCompare, list_DataPrinter, freepoint);  
    //contains the nodes visited 
    ListPtr visited = list_create(list_DataCompare, list_DataPrinter, freepoint); 
    //contains the parent nodes 
    int previous[graph_num_vertices(g)]; 
    // add the start node to the visited 
    list_append(bfs_path, vertex_start);  ////---------> check 
    list_append(bfs_path, vertex_end);     // ---------> check
    list_append(visited, vertex_start); // check null
    //the startnode's parent is the start node itself 
    previous[vertex_start] = vertex_start;
    // adding start node to the queue
    list_append(frontier, vertex_start); 
    while(list_length(frontier) > 0){
        //pop off the first element from the queue
        int current = list_del_index(frontier, 0); 
        // if  it's the stop vertex stop traversing
        if(current == vertex_end){
            break; 
        }
        //gets all the neighbours of current node
        ListPtr list_neighbours = graph_get_neighbors(g, current); 
        int i; 
        //iterating through all the neighbours 
        for(i =0; i < list_length(list_neighbours);i++){
            int found = *(int*)list_get_index(list_neighbours, i); 
            // checking if the element is in visited all ready 
            if(list_find_element(visited, found)==-1){
                (*vertices_explored)++; 
                // if not 
                // appened to frontier 
                list_append(frontier, found); 
                list_append(visited, found); 
                // set the parent of the child to current                                                                      
                previous[found] = current; 
            }
            else{
                //printf("matched"); 
            }
        }     
    }
    int lastindex = previous[vertex_end]; 
    int index = vertex_end; 
    while(index != vertex_start){
        index = previous[index]; 
        list_append(bfs_path, index); 
    } 
    // printf("list-lenght of the path: %d\n", (list_length(bfs_path)-2)); 
    // printf("nodes visited of the path: %d\n", verticesvisited); 
    //printf("%d %d ",verticesvisited, list_length(bfs_path)-2);
    // // Mark visited nodes to maek sure not to visit them twice
    return bfs_path;
}

/**
 * @brief Implements the A* search algorithm to find the shortest path between 2 nodes in an unweighted graph.
 * 
 * @param g The graph to search through
 * @param nodeArr Array of positions of the graph vertices on a 2d plane. Note this is a pointer to a contiguous array, where nodeArr[i] should correspond to node i in the graph. 
 * @param vertex_start The index of the vertex in the graph from where to start the search.
 * @param vertex_end The index of the vertex in the graph that needs to be reached.
 * @param vertices_explored The value in this pointer should be set to the number of vertices that were visited by the algorithm.
 * @return ListPtr A list of the nodes that make up the path from the start to the end, including the start and end nodes.
 */
ListPtr a_star(Graph *g, Point *nodeArr, int vertex_start, int vertex_end, long *vertices_explored) {
    //Perform a star traversal. Make sure to store who the parent of each node in your traversal is, and the path cost up to that node.
    return NULL;
}


int main(int argc, char* argv[]) {
     // argv[1] will tell you if to run bfs or a_star
    int algorithm = (strcmp(argv[1], "bfs") == 0) ? 0 : 1;
    int num_nodes = 0; 
    char temp[900]; 
    char tempdup[900]; 
    char *token; 
    int ncoord1;
    int ncoord2;
    int ecoord1;
    int ecoord2;  
    int pcoord1;
    int pcoord2;

    ListPtr list_nodes = list_create(PointEqual, Printpoint, freepoint);  
    ListPtr list_path = list_create(PointEqual, Printpoint, freepoint); 
    
    //Parse node locations + count number of nodes
    fgets(temp, 900, stdin); 
    while(fgets(temp, 900, stdin) != NULL){
        temp[strcspn(temp, "\n")] = '\0';
        if(strcmp(temp, "======= Edges =======") != 0){ 
            token = strtok(temp, " ");
            ncoord1 = atoi(token);
            while(token!= NULL){
                token = strtok(NULL, " "); 
                if(token!= NULL){
                    ncoord2 = atoi(token); 
                    Point *temp_p = create_point(ncoord1, ncoord2);
                    list_append(list_nodes, temp_p); 
                    num_nodes+=1;
                }
            } 
        }
        else{
            break; 
        }
    }
    //list_print(list_nodes); 
    // printf("%d", num_nodes); 
    // Create graph
    Graph *mygraph = graph_create(num_nodes); 
        
   // reading the edges in and adding them to the graph 
    while(fgets(temp, 900, stdin) != NULL){
        temp[strcspn(temp, "\n")] = '\0';
        if(strcmp(temp, "======= Find paths =======") != 0){ 
            token = strtok(temp, " ");
            ecoord1 = atoi(token);
            while(token!= NULL){
                token = strtok(NULL, " "); 
                if(token!= NULL){
                    ecoord2 = atoi(token); 
                    graph_add_edge(mygraph, ecoord1, ecoord2); 
                } 
            } 
        }
        else{
            break; 
        }       
    }
    
    // reading in the path and adding them to the list to run bfs on them 
    while(fgets(temp, 900, stdin) != NULL){
        temp[strcspn(temp, "\n")] = '\0';
        token = strtok(temp, " ");
        pcoord1 = atoi(token);
        while(token!= NULL){
            token = strtok(NULL, " "); 
            if(token!= NULL){
                pcoord2 = atoi(token); 
                Point *temp_p = create_point(pcoord1, pcoord2);
                list_append(list_path, temp_p);
            }
              
        }       
    }
    //Parse and add graph edges

    //Parse start and end points and run through correct search algorithm
    //Print results to stdout

    //free Data structures
    int left ; 
    int right; 
    int up ; 
    int down ;
    long *vertices = (long*)malloc(sizeof(long)); 
    *vertices = 0; 
    // itterate through the path list and run bsf
    int i; 
    for(i =0; i <list_length(list_path); i++){
        left = 0; 
        right =0; 
        up = 0;
        down = 0;
        *vertices = 0; 
        Point *temp_p = list_get_index(list_path, i); 
        int strt = temp_p -> x; 
        int end = temp_p -> y; 
        ListPtr bfs_path = bfs(mygraph, strt, end, vertices);
        //list_print(bfs_path); 
        int i; 
        for(i =0; i < list_length(bfs_path)-1; i++){
            int vertix1 = list_get_index(bfs_path, i); 
            int vertix2 = list_get_index(bfs_path, i+1); 
            Point *node1 = list_get_index(list_nodes, vertix1); 
            Point *node2 = list_get_index(list_nodes, vertix2); 
            // printf("Node 2: "); 
            // Printpoint(node2); 
            // printf("\n");

            int nodex1 = node1 -> x; 
            int nodey1 = node1 -> y;

            int nodex2 = node2 -> x; 
            int nodey2 = node2 -> y;

            //printf("%d, %d \n", nodex, nodey); 
            if(nodey1 == nodey2){
                if(nodex1 < nodex2){
                    left++; 
                }
                if(nodex1 > nodex2){
                    right++; 
                }
            }
            if(nodex1 == nodex2){
                if(nodey1 < nodey2){
                    up++; 
                }
                if(nodey1 > nodey2){
                    down++; 
                }
            }
             
        } 
        printf("%ld ", *(vertices)); 
        printf("%d ", list_length(bfs_path)-2); 
        printf("%d %d %d %d\n", left, right, up, down);
        //printf("\nprinting list: \n"); 
        //list_print(bfs_path); 
    }
    return 0;
}