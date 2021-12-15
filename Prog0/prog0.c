#include <cairo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * params: 
 * 	cr: pen 
 * 	blx, bly: bottomleft x, bottomleft y
 * 	brx, bry: bottomright x, bottomright y
 * 	trx, try: topright x, topright y
 * 	tlx, tly: topleft x, topleft y
 *
 * drawBox is a function that takes four endpoints and draws
 * a box contained withint the  4 given points.  
 */
void drawBox(cairo_t *cr,double blx,double bly,double brx,double bry,double trx,double try,double tlx,double tly){
        // draws the box using the 4 points that are passed in
	cairo_move_to(cr, blx, bly);
        cairo_line_to(cr, brx, bry);
	cairo_line_to(cr, trx, try); 
	cairo_line_to(cr, tlx, tly); 
	cairo_close_path(cr); 
        cairo_set_source_rgb(cr,1,1,1); //sets pen to white
        cairo_stroke(cr);
}

/*
 * params:
 * 	depth: recursive depth, how many times we have to recurse 
 *	fract: fraction we need to shift 
 * 	blx, bly: bottomleft x, bottomleft y
 * 	brx, bry: bottomright x, bottomright y
 * 	trx, try: topright x, topright y
 * 	tlx, tly: topleft x, topleft y
 * 	cr: pen 
 * drawRect is the fuction that calculated the new starting point for each rectangle and calls the drawRect to 
 * create recatngle and then recurisvely calls itself with the new recursive depth. 
 */

void drawRects(int depth, double fract, double blx, double bly, double brx, double bry, double trx, double try,double tlx,double  tly, cairo_t *cr){ 
	if (depth==0){ 
		return; 
	}
	else{	
		
		double tempblx = blx; 		//storing the initial x value for later use
		double tempbly = bly; 		//storing the initial y value for later calculation
		blx += fract *(brx-blx);	//calculate the bottom-rightx 
		bly += fract *(bry-bly);  	//calculate the bottom-righty
		brx += fract *(trx-brx); 	//calculate the bottom-leftx
		bry += fract *(try-bry);	//calculate the bottom-lefty
		trx += fract *(tlx-trx); 	//calculate the top-leftx
		try += fract *(tly-try); 	//calculate the top-lefty
		tlx += fract *(tempblx-tlx); 	//calculate the top-rightx
		tly += fract *(tempbly-tly); 	//calculate the top-righty
		drawBox(cr, blx, bly, brx, bry, trx, try, tlx, tly); // creates the square with the points passed in
		depth -= 1;  										
		drawRects(depth, fract, blx, bly, brx, bry, trx, try, tlx, tly, cr);  // recursively calls itself
	}	

}

int main(){
	//declaring variables 
	char out_file[30]; 
	char extension[] = ".png"; 
	int dimw; 
	int dimh; 
	int rdepth;
	double fraction;  
	double startx; 
	double starty; 
	double endx; 
	double endy; 
	double toprightx; 
	double toprighty; 
	double topleftx; 
	double toplefty; 
	
	//scanning into the variables
	scanf("%s", out_file);  
	scanf("%d", &dimw); 
	scanf("%d", &dimh); 
	scanf("%d", &rdepth);
	scanf("%lf", &fraction);   
	scanf("%lf", &startx); 
	scanf("%lf", &starty); 
	scanf("%lf", &endx); 
	scanf("%lf", &endy);
	strcat(out_file, extension);	// makes the file name with the .png extension 	 
	// creating canvas 
	cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, dimw, dimh); 
	cairo_t *cr = cairo_create(surface); 	
	// creating blue background
	cairo_set_source_rgb(cr,0, 0, 1); 
	cairo_rectangle(cr, 0, 0, dimw, dimh); 
	cairo_fill(cr);  
	// calculating the top right and the top left corners in case of a tilted square
	toprightx = endx + (endy - starty);  
	toprighty = endy - (endx - startx); 
	topleftx = toprightx - (endx - startx); 
	toplefty = toprighty - (endy - starty);
	// testing the calculated values
	//printf("%lf ", toprightx); 
	//printf("%lf ", toprighty); 
	//printf("%lf ", topleftx); 
	//printf("%lf ", toplefty);  
	// calculates and draws the base rectangle	
	drawBox(cr, startx, starty, endx, endy, toprightx, toprighty, topleftx, toplefty);
	//call the draw rect function   
 	drawRects(rdepth, fraction, startx, starty, endx, endy, toprightx, toprighty,topleftx,toplefty, cr); 	
	//output to png file
	cairo_destroy(cr); 
	cairo_surface_write_to_png(surface, out_file); 	
	cairo_surface_destroy(surface); 
	return 0; 		
}

