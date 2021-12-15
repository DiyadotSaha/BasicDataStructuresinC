#include <stdio.h>
#include <math.h>
#include "Wall.h"

point* point_create(int x, int y){
	point* p = (point*)malloc(sizeof(point));
	p->x = (double)x;
	p->y = (double)y;
	return p;
}

segment* segment_create(point* start, point* end){
	segment* wall = (segment*)malloc(sizeof(segment));
	wall->start = start;
	wall->end = end;
	wall->orientation = GetOrientation(wall);
	return wall;
}

enum WallOrientation GetOrientation(segment* wall){
	if (wall->start->x == wall->end->x){
		return VERTICAL;
	} else {
		return HORIZONTAL;   
	}
}

// determine a wall located on which side of the partition segment
enum ESegmentWallSide ClassifySegment(segment PartitionSeg, segment wall)
{
	if(GetOrientation(&PartitionSeg)==VERTICAL){
		if((wall.start ->x <= PartitionSeg.start -> x)&&(wall.end ->x <= PartitionSeg.end -> x)){
			return SEGMENT_WALL_SIDE_FRONT; 
		}
		else if ((wall.start ->x >= PartitionSeg.start -> x)&&(wall.end ->x >= PartitionSeg.end -> x)){
			return SEGMENT_WALL_SIDE_BEHIND; 
		}
		else{
			return SEGMENT_WALL_SIDE_STRADDLING;
		}
	}
	else if(GetOrientation(&PartitionSeg)==HORIZONTAL){
		if((wall.start -> y <= PartitionSeg.start -> y)&&(wall.end -> y <= PartitionSeg.end -> y)){
			return SEGMENT_WALL_SIDE_FRONT;
			
		}
		else if ((wall.start -> y >= PartitionSeg.start -> y)&&(wall.end -> y >= PartitionSeg.end -> y)){
			return SEGMENT_WALL_SIDE_BEHIND; 
		}
		else{
			return SEGMENT_WALL_SIDE_STRADDLING;
		}
	}
}

// compute the intersection point on the wall divided by the PartitionSeg
int IntersectionWalls(segment PartitionSeg, segment wall, point* out){
	//sets the point to the intersection 
	if(ClassifySegment(PartitionSeg, wall) == SEGMENT_WALL_SIDE_STRADDLING){
		if(GetOrientation(&PartitionSeg)==VERTICAL){
			out -> x = PartitionSeg.start -> x; 
			out -> y = wall.start -> y;
		}
		else if(GetOrientation(&PartitionSeg)==HORIZONTAL){
			out -> x = wall.start -> x;
			out -> y = PartitionSeg.start -> y; 
		}
		 
		return 1; 
	}
	else{
		return -1; 
	}
}


// Output the two segments of the original wall divided by the partition segment to frontSeg and backSeg                                                                                                         
void SplitWallSegment(segment PartitionSeg, segment wall, segment *frontSeg, segment *backSeg)
{
	//printf("inside splitwallSegment\n"); 
	point *intersecting_point = (point*)malloc(sizeof(point )); 
	if(GetOrientation(&PartitionSeg)==VERTICAL){
		//printf("WALL_VERTICAL\n");
		int check_intersecting = IntersectionWalls(PartitionSeg, wall,intersecting_point);
		*frontSeg = *segment_create(wall.start, intersecting_point); 
		*backSeg = *segment_create(intersecting_point, wall.end); 

	}
	else if(GetOrientation(&PartitionSeg)==HORIZONTAL){
		//printf("WALL_HORIZONTAL\n");
		int check_intersecting = IntersectionWalls(PartitionSeg, wall,intersecting_point);
		*frontSeg = *segment_create(wall.start, intersecting_point); 
		*backSeg = *segment_create(intersecting_point, wall.end);
	}
}
