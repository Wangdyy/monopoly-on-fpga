//board is 240 square width
//corner squares are 32 pixels width
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
	
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
	
void clear_screen();
void wait_for_vsync();
void plot_pixel(int x, int y, short int color);
void draw_rectangle(int x1, int y1, int x2, int y2, int color, int orientation);
void draw_railroad(int x1, int y1, int x2, int y2, int orientation);
void draw_text(char* text, int x_position, int y_position);

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

	for(int x=240; x<320; x++){
		for(int y=0; y<240; y++){
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
	draw_rectangle(33,24,51,31, RED, 3);
	//#2: x1=52, y1=24, x2=70, y2 = 31
	draw_rectangle(71,24,89,31, RED, 3);
	//#3: x1=90, y1=24, x2=108, y2 = 31
	draw_rectangle(90,24,108,31, RED, 3);
	
	//yellow properties
	//#1: x1=128, y1=24, x2=146, y2 = 31
	draw_rectangle(128,24,146,31, YELLOW, 3);
	//#2: x1=147, y1=24, x2=165, y2 = 31
	draw_rectangle(147,24,165,31, YELLOW, 3);
	//#3: x1=185, y1=24, x2=208, y2 = 31
	draw_rectangle(185,24,208,31, YELLOW, 3);
	
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
    volatile int *pixel_ctrl_ptr = (int *)0xFF203020;
    volatile int *status =(int *)0x0000;

    *pixel_ctrl_ptr = 1; //request to sync with vga timing

    while((*status & 0x01) != 0){
		status = status; //keep reading status
	}
pixel_buffer_start = *(pixel_ctrl_ptr + 1);
}
