#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "BSP.h"
#include "Wall.h"
#include "List.h"
/**
 * @brief Creates a new BSP and using the provided data. This constructor calls BuildSubtree, which is a recursive function 
 *
 * @param data A ListPtr of the data that should be used to build the tree
 * @param GetPartitionRoot A function which delets a node from the list and returns the data
 * @param GetSubtrees Given a data value, modifies the provided list to contain the 'right' sublist and returns a pointer to the 'left' sub list
 * @param DataCompare A function for comparing two values, returns 0 if equal, >0 if obj1 is greater, and <0 if obj2 is greater
 * @param DataPrinter A function for printing out a piece of data in the list
 * @param FreeData A function used to free data from the BSP
 *
 * @return A pointer to the newly created and partitioned BSP
 */
BSPTree* BSP_Create(ListPtr data, void* (*GetSubtreeRoot)(ListPtr data), ListPtr (*GetSubtrees)(void* parent, ListPtr remaining), int (*DataCompare)(void* data1, void* data2), void (*DataPrinter)(void* data), void (*FreeData)(void *data)){
    BSPTree* temp_tree = (BSPTree*) malloc(sizeof(BSPTree));
    temp_tree -> GetSubtreeRoot = GetSubtreeRoot; 
    temp_tree -> GetSubtrees = GetSubtrees; 
    temp_tree -> DataCompare = DataCompare; 
    temp_tree -> DataPrinter = DataPrinter; 
    temp_tree -> FreeData = FreeData;  
    // setting the root to Buildsubtree
    temp_tree -> root = BuildSubtree(temp_tree, data, temp_tree -> root); 
    return temp_tree; 
}

/**
 * @brief Helper function to create a new node for the BSP
 *
 * @param data The data to be stored within the created node
 *
 * @return A pointer to the newly created TreeNode
 */
TreeNode* TreeNode_Create(void* data){
    TreeNode* temp_node = (TreeNode*) malloc(sizeof(TreeNode));
    temp_node -> data = data; 
    temp_node -> parent = NULL; 
    temp_node -> left = NULL; 
    temp_node -> right = NULL; 
    return temp_node; 
}


/**
 * @brief Recursive function that operates on a List to select a subtree root node and build that node's left and right subtrees
 *
 * @param tree A pointer to a BSPTree which contains functions to GetSubtreeRoot, and GetSubtrees
 * @param remaining A list pointer to the remaining elements not already in the BSP
 * @param parent The node which is parent to the returned TreeNode
 *
 * @return TreeNode* A pointer to the root of the generated subtree
 *
 */
TreeNode* BuildSubtree(BSPTree* tree, ListPtr remaining, TreeNode* parent){
    segment* temp_seg = tree -> GetSubtreeRoot(remaining);
    //checking for NULL segs 
    if(temp_seg == NULL){
        return NULL; 
    }
    TreeNode* temp_node = TreeNode_Create(temp_seg); 
    temp_node -> parent = parent; 
    //returning the base node 
    if(list_length(remaining)<1){
        return temp_node; 
    } 
    temp_node -> left = BuildSubtree(tree, tree -> GetSubtrees(temp_seg, remaining), temp_node); 
    temp_node -> right = BuildSubtree(tree, remaining, temp_node);
    return temp_node; 
}


/**
 * @brief A function which prints the contents of the BSP in using pre-order traversal
 *
 * @param tree A pointer to the tree to print
 */
void BSP_print(BSPTree* tree){
    // printing the tree using the Gettraversal 
    //printf("\nPrinting BSP tree:\n"); 
    ListPtr printList = BSP_GetTraversal(tree); 
    list_print(printList); 	
}	

/**
 * @brief Returns a list containing all elements in the BSP, sorted using pre-order traversal
 *
 * @param tree The tree to build the list from
 *
 * @return ListPtr A pointer to a list which contains all elements sorted using pre-order traversal
 */
ListPtr BSP_GetTraversal(BSPTree* tree){
    //calling the preorder traversal 
    ListPtr temp_List = list_create(tree->DataCompare, tree-> DataPrinter, tree-> FreeData); 
    PreOrderTraverse(temp_List, tree->root); 
    return temp_List; 	
}

/**
 * @brief A recursive function which traverses the BSP and adds the data to the provided list
 *
 * @param list A pointer to a list. When the recursion ends, this list will contain all elements from the BSP
 * @param node A TreeNode* from a BSP
 */
void PreOrderTraverse(ListPtr list, TreeNode* node){
    if (node == NULL){ 
        return NULL; 
    }
    //traversing left child and right child 
    list_append(list, node->data); 
    PreOrderTraverse(list, node -> left);
    PreOrderTraverse(list, node -> right);	
}

/**
 * @brief
 *
 * @param tree A pointer to the tree to delete
 * @param freeData A bool indicating whether the underlying data should be freed
 */ 
void DestroyTree(BSPTree* tree, bool freeData){
    free(tree);
}