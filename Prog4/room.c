// room.c
#include <cairo.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Wall.h"
#include "List.h"
#include "BSP.h"
#include <math.h>


// Two line segments are equal if they start and end at the same point
// Returns 0 if segments are equal, -1 otherwise
int SegmentsEqual(void* segment1, void* segment2){
	//printf("Inside Segment Equal \n"); 
	segment *temp1 = (segment*) segment1;
	segment *temp2 = (segment*) segment2;
	if((temp1 -> start -> x == temp2 -> start -> x)&&(temp1 -> start -> y == temp2 -> start -> y)&&(temp1 -> end -> x == temp2 -> end -> x)&&(temp1 -> end -> y == temp2 -> end -> y)){
		return 0; 
	}
	else{
		return -1; 
	}		
}

//print out the coordinates of the segment, remember to use %d for integers
void PrintSegment(void* segment1){
	segment *temp = (segment*) segment1;  
	if(segment1 != NULL){
		printf("%d %d %d %d\n", temp -> start -> x, temp -> start -> y, temp -> end -> x, temp -> end -> y);
	}
	else{
		printf("NULL!\n"); 
	}
}

// remember to free the start and end points of the segment
void DestroySegment(segment* seg){
	free(seg -> start); 
	free(seg -> end); 
	free(seg); 
	seg = NULL; 
}

/**
* @brief Takes a parent node and generates a list containing all elements that form the left subtree of parent
* Note: The original list should be modified so that it contains only elements that form the right subtree of parent
* Assumes that parent is not in original
*
* @param parent The parent node which elements in the list argument will be compared with to determine left/right relationship
* @param original A pointer to a list containing all children of the parent. Original is modified to contain all right children
*
* @return ListPtr pointing to a list which holds all elements which will form the left subtree of parent. Returns NULL if parent or orignal
* are null
*/
ListPtr GetPartitions(void* parent, ListPtr remaining){
	//printf("Inside get partitions\n"); 
	ListPtr leftpoints = list_create(SegmentsEqual, PrintSegment, DestroySegment); 
	segment *temp = (segment*)parent;
	int i; 
	for(i = 0; i< list_length(remaining); i++){
		segment *list_seg = list_get_index(remaining, i);
		if(ClassifySegment(*temp, *list_seg) == SEGMENT_WALL_SIDE_FRONT){
			list_append(leftpoints, list_get_index(remaining, i)); 
 
		}
		else if(ClassifySegment(*temp, *list_seg) == SEGMENT_WALL_SIDE_BEHIND){
			//list already contains the point needed  
		}
		else if (ClassifySegment(*temp, *list_seg) == SEGMENT_WALL_SIDE_STRADDLING){
			//printf("This is straddling \n"); 
			segment *s1 = (segment*)malloc(sizeof(segment));
			segment *s2 = (segment*)malloc(sizeof(segment));
			SplitWallSegment(*temp, *list_seg, s1, s2);
			//printf("insert breakpoint \n");
			int found =  list_find_element(remaining, list_seg); 
			list_del_index(remaining, found); 
			if(ClassifySegment(*temp, *s1) == SEGMENT_WALL_SIDE_FRONT){
				list_insert(remaining, i, s2); //Debugging: switched from s1 to s2
				list_append(leftpoints, s1); 
			}
			else if (ClassifySegment(*temp, *s1) == SEGMENT_WALL_SIDE_BEHIND)
			{
				list_append(leftpoints, s2); //Debugging: switched from s1 to s2
				list_insert(remaining, i, s1);
			} 		
		}
		
	}
	
	int j; 
	for(j =0; j < list_length(leftpoints); j++){
		int found = list_find_element(remaining, list_get_index(leftpoints, j)); 
		list_del_index(remaining, found); 

	}
	
	/*debugging 
	printf("---------------\n");  
	printf("Left_Points: \n"); 
	list_print(leftpoints); 
	printf("------------\n"); 
	printf("---------------\n"); 
	printf("Right_Points: \n"); 
	list_print(remaining); 
	printf("------------\n");*/
	return leftpoints; 
	
}
/**
 * @brief used to select the data which will form the root of a new subtree
 *
 * @param remaining A listpointer containing all the remaining data, after execution it should not contain the removed value
 *
 * @return void* A pointer to the extracted data
 */ 
void* SelectPartitionRoot(ListPtr remaining){
	if(list_length(remaining)>1){
		int s = floor(list_length(remaining)/2); 
		segment* temp = list_del_index(remaining, s-1);
		return temp;
	}   
	return list_del_index(remaining, 0); 	
}

/**
 * BONUS POINT CASE.
 * Determines which wall the Fancy Door is located on using bsp tree
 * The fancy door is a segment with given endpoints
 *
 * @param tree The BSP tree you built with the provided rooms
 * @param door A segment to be found
 * @param Wall It will store the wall contains the door here.
 *
 * @return int Returns -1 if the door outside the room (as long as part of the door is outside the room), 
 *						0 if the door inside the room (including the door touch the walls), 
 *						1 if the door on the walls
*/ 
int FindFancyDoor(BSPTree* tree, segment fancydoor, segment* Wall){
	//did not attempt
};

/**
 * Determines which wall the door is located on using bsp tree
 * The door is a point with given coordinates
 *
 * @param tree The BSP tree that you built with the provided rooms
 * @param door A coordinate point to be found
 * @param Wall It will store the wall contains the door here.
 *
 * @return int Returns -1 if the door outside the room, 0 if the door inside the room, 1 if the door on the walls
 */
int FindDoor(BSPTree* tree, point door, segment* Wall){
	ListPtr roomlist = BSP_GetTraversal(tree); 
	// testing if the door is on the wall segment or on the corner of two wall segments
	int i; 
	for(i =0; i< list_length(roomlist); i++){
		segment* wall_seg = list_get_index(roomlist, i); 
		// checking if the wall is on the vertical walls of the polygon
		if((((door.y <= wall_seg ->start -> y) && (door.y >= wall_seg ->end -> y))
		||((door.y >= wall_seg ->start -> y) && (door.y <= wall_seg ->end -> y)))
		&&((door.x == wall_seg ->start->x)&&(door.x == wall_seg->end->x)) && GetOrientation(wall_seg)==VERTICAL){
			*Wall = *wall_seg;  
			return 1; 
		}
		//checking if the walls are on the horizontal walls of the polygon
		else if((((door.x >= wall_seg -> start -> x)&&(door.x <= wall_seg -> end -> x)
		||(door.x <= wall_seg -> start -> x)&&(door.x >= wall_seg -> end -> x))
		&&((door.y == wall_seg -> start -> y)&&(door.y == wall_seg -> end -> y))) && GetOrientation(wall_seg)==HORIZONTAL){ 
			*Wall = *wall_seg; 
			return 1; 			
		}
	}
	// checking the walls that are not on the wall segments or corners 
	int intersection_counter =0; 
	for(i =0; i< list_length(roomlist); i++){
		segment* wall_seg = list_get_index(roomlist, i); 
		// testing for doors inside or outside the polygon. 
		// checking only for the VERTICAL WALLS on the right side or the door
		//checking if they cut through any walls
		if(GetOrientation(wall_seg)==VERTICAL){
			if((wall_seg -> start -> x > door.x )&& (wall_seg -> end -> x > door.x )){
				if((((door.y <= wall_seg ->start -> y) && (door.y >= wall_seg ->end -> y))
				||((door.y >= wall_seg ->start -> y) && (door.y <= wall_seg ->end -> y)))){
					intersection_counter++; 
				}
			}
			else{
				//did not make it into the case hence not intersecting with any walls
			}
		}
	}
	//checks if the counter is even or odd
	//if the counter is even it cuts through both sides of the polygon hence the point is outside
	// if the counter is odd it vuts through only one side of the polygon 
	if((intersection_counter % 2) == 0){
		return -1; 
	}
	else{
		return 0;
	} 
}



/**
 * @brief Used to draw out our BSP (room)
 *
 * @param tree A pointer to the tree containing the room
 * @param filename The name of the outputfile, DrawBSP concatenates with ".png"
 * @param doors A list of doors (points) that will be drawn to the cairo canvas in red
 * @param fancyDoors A list of fancyDoors (segments) that will be drawn to the cairo canvas in yellow
 *
 */

void DrawBSP(BSPTree* tree, char* filename, ListPtr doors, ListPtr fancyDoors){
	// Get a list of our BSP data sorted by pre-order traversal
	ListPtr traversalList = BSP_GetTraversal(tree);
	cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 512, 512);
	cairo_t *cr = cairo_create (surface);
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_rectangle(cr, 0, 0, 512, 512);
	cairo_fill(cr);
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_set_line_width(cr, 5.0);
	cairo_set_font_size(cr, 32);
	char label[10];
	for(int i = 0; i < list_length(traversalList); i++){
		segment* seg = (segment*)list_get_index(traversalList, i);
		//draw the line
		cairo_move_to(cr, seg->start->x, seg->start->y);
		cairo_line_to(cr, seg->end->x, seg->end->y);
		cairo_stroke(cr);
		int midX = (seg->start->x + seg->end->x)/2;
		int midY = (seg->start->y + seg->end->y)/2;
		cairo_move_to(cr, midX, midY);
		sprintf(label, "%d", i);
		cairo_show_text(cr, label);
	}
	
	if(doors != NULL){
		cairo_close_path(cr);
		cairo_set_source_rgb(cr, 1, 0, 0);
		for(int i = 0; i < list_length(doors); i++){
			point* d = (point*)list_get_index(doors, i);
			cairo_rectangle(cr, (d->x) - 5, (d->y) - 5, 10, 10);
			cairo_stroke(cr);
		}
	}

	if(fancyDoors != NULL){
		cairo_set_source_rgb(cr, 1, 1, 0);
		for(int i = 0; i < list_length(fancyDoors); i++){
			segment* seg = (segment*)list_get_index(fancyDoors, i);
			//draw the line
			cairo_move_to(cr, seg->start->x, seg->start->y);
			cairo_line_to(cr, seg->end->x, seg->end->y);
			cairo_close_path(cr);
			cairo_stroke(cr);
		}
	}

	cairo_destroy(cr);
	char* outputName = strcat(filename, ".png");
	cairo_surface_write_to_png(surface, outputName);
	cairo_surface_destroy(surface);
}


int main (int argc, char **argv){
	char room_name[100]; 
	FILE *room_file; 
	room_file = fopen (argv[1], "r");
	FILE *door_file; 
	door_file = fopen (argv[2], "r");
	int Rx_coord1; 
	int Ry_coord1; 
	int Rx_coord2; 
	int Ry_coord2;
	int Dx_coord; 
	int Dy_coord; 
	int c; 

	ListPtr room_list = list_create(SegmentsEqual, PrintSegment, DestroySegment);
	ListPtr door_list = list_create(SegmentsEqual, PrintSegment, DestroySegment); 
	
	// reading the name of the file 
	fgets(room_name, sizeof(room_name), room_file);
	//scanning the coords of the rooms into a list 
	while(!feof(room_file)){
		fscanf(room_file, "%d", &Rx_coord1);
		fscanf(room_file, "%d", &Ry_coord1);  
		fscanf(room_file, "%d", &Rx_coord2);
		fscanf(room_file, "%d", &Ry_coord2);
		point* point1 = point_create(Rx_coord1,Ry_coord1);
		point* point2 = point_create(Rx_coord2, Ry_coord2);
		segment* temp_seg = segment_create(point1, point2); 
		list_append(room_list, temp_seg); 
	}
	
	int door; 
	//scanning whether the fancy door or not
	fscanf(door_file, "%d", &door);
	//scanning the coords of the door 
	while(!feof(door_file)){
		fscanf(door_file, "%d", &Dx_coord);
		fscanf(door_file, "%d", &Dy_coord); 
		point *point1 = point_create(Dx_coord, Dy_coord);	 
		list_append(door_list, point1); 
	}

	BSPTree* temp_tree = BSP_Create(room_list, SelectPartitionRoot, GetPartitions, SegmentsEqual, PrintSegment,DestroySegment);
	DrawBSP(temp_tree, room_name, door_list, NULL); 
	
	int i; 
	//looping through all the doors and running find doors 
	for( i =0; i< list_length(door_list); i++){
		point* door_point = list_get_index(door_list, i); 
		point* point1 = point_create(0,0);
		point* point2 = point_create(0, 0);
		segment* intersect_seg = segment_create(point1, point2);
		// storing the finddoors output 
		int foundDoor = FindDoor(temp_tree, *door_point, intersect_seg);
		if(foundDoor == 0){
			printf("IN\n");  
		}
		else if(foundDoor == -1){
			printf("OUT\n");   
		}
		else if(foundDoor == 1){
			PrintSegment(intersect_seg);
		}
	}
}