//board is 240 square width
//corner squares are 32 pixels width
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
	
#define BACKGROUND_COLOUR 0xCF3A
#define BLACK 0x0000
#define LIGHT_BLUE 0xAF1F
#define BROWN 0x92A6
#define RED 0xE8C4
#define YELLOW 0xFF80
#define ORANGE 0xF4A3
#define PINK 0xD9D2
#define GREEN 0x1D8B
#define DARK_BLUE 0x0397
#define WHITE  0xffff
	
void clear_screen();
void wait_for_vsync();
void plot_pixel(int x, int y, short int color);
void draw_rectangle(int x1, int y1, int x2, int y2, int color, int orientation);
void draw_railroad(int x1, int y1, int x2, int y2, int orientation);
void draw_text(char* text, int x_position, int y_position);
void draw_jail();
void draw_go();
void draw_arc(int x, int y, int radius, int start_degrees, int end_degrees, int thickness, int color);
void draw_horizontal(int x_start, int x_end, int y, int thickness, int color);
void draw_vertical(int x, int y_start, int y_end, int thickness, int color);
void draw_chance(int x, int y, int orientation);	

void write_char(int x, int y, char c) {
  // VGA character buffer
  volatile char * character_buffer = (char *) (0xC9000000 + (y<<7) + x);
  *character_buffer = c;
}

//global variables
volatile int pixel_buffer_start;
volatile int * pixel_ctrl_ptr;


struct Property{
	int x1;
	int x2;
	int y1;
	int y2;
	int color;
	int orientation;
};

int main(void)
{
	// set front pixel buffer to start of FPGA On-chip memory
	pixel_ctrl_ptr = (int *) 0xFF203020;
	
	volatile int *key_ptr = (int *) 0xFF200050;
			
	// first store the address in the back buffer
	*(pixel_ctrl_ptr + 1) = 0xC8000000;
	
	// now, swap the front/back buffers, to set the front buffer location
	wait_for_vsync();
	
	// initialize a pointer to the pixel buffer, used by drawing functions
	pixel_buffer_start = *pixel_ctrl_ptr; 
	
	// set back pixel buffer to start of SDRAM memory
	*(pixel_ctrl_ptr + 1) = 0xC0000000;
	
	pixel_buffer_start = *(pixel_ctrl_ptr + 1); // we draw on the back buffer
	
	//initialize properties;
	//property properties[22];
	//light blue properties
	struct Property lb1= {33,209,51,216, LIGHT_BLUE, 1};
	//set up the back buffer drawing
	//clear character buffer
		for(int x=0; x<80; x++){
			for(int y=0; y<60; y++){
				char* clear = " ";
				while (*clear) {
					write_char(x, y, *clear);
					clear++;
				}
			}	
		}


	clear_screen();
	
	wait_for_vsync(); //swap buffers
	
	//set up the swapped back buffer drawing
	clear_screen();
	
	wait_for_vsync(); //swap buffers
	//char buffer variables
	int x;
	//char* text;
	
	
}

void plot_pixel(int x, int y, short int color){
	*(short int *)(pixel_buffer_start+(y<<10)+(x<<1)) = color;
}


void clear_screen(){
	char* text;
	
	//draw border horizontal and vertical lines and background color
	for(int x=0; x<240; x++){
		for(int y=0; y<240; y++){
			if (x == 32 || x == 208){
				plot_pixel(x, y, BLACK);
			}
			else if (y == 32 | y == 208){
				plot_pixel(x, y, BLACK);
			}
			else{
				plot_pixel(x, y, BACKGROUND_COLOUR);
			}
		}
	}
	//temporarily black area on right
	for(int x=240; x<320; x++){
		for(int y=0; y<240; y++){
			plot_pixel(x, y, BLACK);
		}
	}
	//draw bordes for each edge box
	for (int x=51; x<189; x+=19){
		for (int y=0; y<32; y++){
			plot_pixel(x, y, BLACK);
		}
	}
	for(int x=51; x<189; x+=19){
		for(int y=208; y<240; y++){
			plot_pixel(x, y, BLACK);
		}
	}
	for(int x=0; x<32; x++){
		for(int y=51; y<189; y+=19){
			plot_pixel(x, y, BLACK);
		}
	}
	for(int x=208; x<240; x++){
		for(int y=51; y<189; y+=19){
			plot_pixel(x, y, BLACK);
		}
	}

	
	
	//properties
	
	//bottom edge properties
	
	//light blue properties
	//#1: x1=33, y1=209, x2=51, y2 = 216
	draw_rectangle(33,209,51,216, LIGHT_BLUE, 1);
	//#2: x1=52, y1=209, x2=70, y2 = 216
	draw_rectangle(52,209,70,216, LIGHT_BLUE, 1);
	//#3: x1=90, y1=209, x2=108, y2 = 216
	draw_rectangle(90,209,108,216, LIGHT_BLUE, 1);
	
	//brown properties
	//#1: x1=147, y1=209, x2=165, y2 = 216
	draw_rectangle(147,209,165,216, BROWN, 1);
	//#2: x1=185, y1=209, x2=208, y2 = 216
	draw_rectangle(185,209,208,216, BROWN, 1);
	
	//red properties
	//#1 x1=33, y1=24, x2=51, y2 = 31
	draw_rectangle(33,24,51,32, RED, 3);
	//#2: x1=52, y1=24, x2=70, y2 = 31
	draw_rectangle(71,24,89,32, RED, 3);
	//#3: x1=90, y1=24, x2=108, y2 = 31
	draw_rectangle(90,24,108,32, RED, 3);
	
	//yellow properties
	//#1: x1=128, y1=24, x2=146, y2 = 31
	draw_rectangle(128,24,146,32, YELLOW, 3);
	//#2: x1=147, y1=24, x2=165, y2 = 31
	draw_rectangle(147,24,165,32, YELLOW, 3);
	//#3: x1=185, y1=24, x2=208, y2 = 31
	draw_rectangle(185,24,208,32, YELLOW, 3);
	
	//orange properties
	//#1: x1=25, y1=33, x2=32, y2 = 51
	draw_rectangle(25,33,32,51, ORANGE, 2);
	draw_rectangle(25,52,32,70, ORANGE, 2);
	draw_rectangle(25,90,32,108, ORANGE, 2);
	
	//pink properties
	draw_rectangle(25,128,32,146, PINK, 2);
	draw_rectangle(25,147,32,165, PINK, 2);
	draw_rectangle(25,185,32,208, PINK, 2);
	
	//green properties
	draw_rectangle(209,33,216,51, GREEN, 4);
	draw_rectangle(209,52,216,70, GREEN, 4);
	draw_rectangle(209,90,216,108, GREEN, 4);
	
	//pink properties
	draw_rectangle(209,147,216,165, DARK_BLUE, 4);
	draw_rectangle(209,185,216,208, DARK_BLUE, 4);
	
	//draw railroads
	//bottom railroad
	draw_railroad(109,212,127,219,1);
	//top railroad
	draw_railroad(109,21,127,28,1);
	//left railroad
	draw_railroad(21,109,28,127,2);
	//right railroad
	draw_railroad(212,109,219,127,2);
	
	//Go to jail square x: 208-240, y: 0-32
	//text = "GO TO JAIL";
	draw_text("GO TO", 54, 2);
	draw_text("JAIL", 54, 4);
	
	//Jail square x:0-32, y: 208-240
	draw_jail();
	
	//Go square x:208-240, y: 208-240
	draw_go();
	
	//chance squares
	draw_chance(71, 209, 0);
	draw_chance(70, 32, 2);
	draw_chance(209, 185, 3);
}

	//Test horizontal and vertical line functions
	//draw_horizontal(100,140,120,2,BLACK);
	//draw_vertical(100,140,160,2,BLACK);
void draw_arc(int x, int y, int radius, int start_degrees, int end_degrees, int thickness, int color){
	//x and y define the centre of arc, radius defines the inner radius
	//draw an arc from start_degrees to end_degrees
	for(int thickness_offset=0; thickness_offset<thickness; thickness_offset++){
		int x_current;
		int y_current;
		int radius_current = radius + thickness_offset; 
		for(int current_degree=start_degrees;current_degree<end_degrees;current_degree++){
			//Set x_current, y_current
			double current_radians = current_degree * 0.017453;
			x_current = round(x + radius_current * cos(current_radians));
			y_current = round(y + radius_current * sin(current_radians));
			plot_pixel(x_current,y_current,BLACK);
		}
	}
}
void draw_horizontal(int x_start, int x_end, int y, int thickness, int color){
	for (int x_current = x_start; x_current <= x_end; x_current++){
		for (int y_offset = 0; y_offset < thickness; y_offset++){
			plot_pixel(x_current,y+y_offset,color);
		}
	}
}
void draw_vertical(int x, int y_start, int y_end, int thickness, int color){
	for (int y_current = y_start; y_current <= y_end; y_current++){
		for (int x_offset = 0; x_offset < thickness; x_offset++){
			plot_pixel(x+x_offset,y_current,color);
		}
	}	
}
void draw_go(){
	//Draw the triangle on the left
	int y = 232;
	int height = 1;
	plot_pixel(211,232,BLACK);
	for(int x=212;x<216;x++){
		plot_pixel(x,y+height,BLACK);
		plot_pixel(x,y-height,BLACK);
		for(int y_offset=0;y_offset<height;y_offset++){
			int y = 232 + y_offset;
			plot_pixel(x,y,RED);
			y = 232 - y_offset;
			plot_pixel(x,y,RED);
		}
		height++;
	}
	for(int y_offset=0;y_offset<height;y_offset++){
		plot_pixel(216,232+y_offset,BLACK);
		plot_pixel(216,232-y_offset,BLACK);
	}
	draw_rectangle(216,231,236,234,RED,4);
	for(int x=216;x<237;x++){
		plot_pixel(x,230,BLACK);
		plot_pixel(x,234,BLACK);
	}
	draw_arc(217,219,5,0,315,2,BLACK);
	draw_rectangle(217,219,222,220,BLACK,1);
	draw_arc(231,219,5,0,360,2,BLACK);
	
}
void draw_railroad(int x1, int y1, int x2, int y2, int orientation){
	int horizontal;
	if(orientation ==1){
		for(int x = x1; x<x2; x++){
			for (int y = y1; y<y2; y++){
				if (x%2==0){
					plot_pixel(x,y,BLACK);
				}
				if (y == y1+1 || y == y2-2){
					plot_pixel(x,y,BLACK);
				}
			}
		}
	}
	else{
		for(int x = x1; x<x2; x++){
			for (int y = y1; y<y2; y++){
				if (y%2==0){
					plot_pixel(x,y,BLACK);
				}
				if (x == x1+1 || x == x2-2){
					plot_pixel(x,y,BLACK);
				}
			}
		}
	}
	
}
void draw_jail(){
	draw_rectangle(10, 209, 32, 231, ORANGE, 2);
	for(int x=9; x<32; x++){
	plot_pixel(x, 231, BLACK);	
	}
	draw_rectangle(16, 211, 28, 223, WHITE, 2);
	for(int x=15; x<28; x++){
	plot_pixel(x, 211, BLACK);	
	plot_pixel(x, 223, BLACK);	
	}
	for(int y=211; y<223; y++){
	plot_pixel(27, y, BLACK);
	}
	for(int x=18; x<28; x=x+3){
		for(int y=211; y<223; y++){
			plot_pixel(x,y,BLACK);
		}
	}
	
	
}

void draw_chance(int x, int y, int orientation){
	//0 -> bottom 1->left 2-> top 3-> right

	if (orientation == 0){
		draw_arc(x + 9, y + 11, 5, 180 + 90*orientation, 420 + 90*orientation, 1, BLACK);
		draw_arc(x + 14, y + 19, 4, 180 + 90*orientation, 240 + 90*orientation, 1, BLACK);
		draw_vertical(x + 9, y + 19, y + 22, 1, BLACK);
		draw_vertical(x + 9, y + 25, y + 26, 1, BLACK);
	}
	else if (orientation == 1){
		draw_arc(x - 11, y + 9, 5, 180 + 90*orientation, 420 + 90*orientation, 1, BLACK);
		draw_arc(x - 19, y + 14, 4, 180 + 90*orientation, 240 + 90*orientation, 1, BLACK);
		draw_horizontal(x - 22, x - 19, y + 9, 1, BLACK);
		draw_horizontal(x - 26, x - 25, y + 9, 1, BLACK);
	}
	else if (orientation == 2){
		draw_arc(x - 9, y - 11, 5, 180 + 90*orientation, 420 + 90*orientation, 1, BLACK);
		draw_arc(x - 14, y - 19, 4, 180 + 90*orientation, 240 + 90*orientation, 1, BLACK);
		draw_vertical(x - 9, y - 22, y - 19, 1, BLACK);
		draw_vertical(x - 9, y - 26, y - 25, 1, BLACK);
	}
	else if (orientation == 3){
		draw_arc(x + 11, y - 10, 5, 180 + 90*orientation, 420 + 90*orientation, 1, BLACK);
		draw_arc(x + 19, y - 15, 4, 180 + 90*orientation, 240 + 90*orientation, 1, BLACK);
		draw_horizontal(x + 19, x + 22, y - 10, 1, BLACK);
		draw_horizontal(x + 25, x + 26, y - 10, 1, BLACK);
	}
	

}

void draw_rectangle(int x1, int y1, int x2, int y2, int color, int orientation){
	for(int x = x1; x<x2; x++){
		if (orientation ==3){
			plot_pixel(x,y1-1,BLACK);
		}
		for (int y=y1; y<y2; y++){
			if (orientation ==2){
				plot_pixel(x1-1,y,BLACK);
			}
			plot_pixel(x, y, color);
			if (orientation ==4){
				plot_pixel(x2,y,BLACK);
			}
		}
		if (orientation ==1){
			plot_pixel(x,y2,BLACK);
		}
	}
}

void draw_text(char* text, int x_position, int y_position){
		int x = x_position;
		while (*text) {
			write_char(x, y_position, *text);
			x++;
			text++;
		}
}




void wait_for_vsync(){
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
	register int status;
	
	*pixel_ctrl_ptr = 1; // start synchronization (write to buffer register)
	status = *(pixel_ctrl_ptr + 3);

	while ((status & 0x01) != 0) { // wait for S to be 0
		status = *(pixel_ctrl_ptr + 3);
	}
	
	pixel_buffer_start = *(pixel_ctrl_ptr + 1);
}
	
