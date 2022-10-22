//board is 240 square width
//corner squares are 32 pixels width
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
	
void clear_screen();
initial_board();
void wait_for_vsync();
void plot_pixel(int x, int y, short int color);

//global variables
volatile int pixel_buffer_start;
volatile int * pixel_ctrl_ptr;

void write_char(int x, int y, char c) {
  // VGA character buffer
  volatile char * character_buffer = (char *) (0xC9000000 + (y<<7) + x);
  *character_buffer = c;
}

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
	
	//set up the back buffer drawing
	clear_screen();
	
	wait_for_vsync(); //swap buffers
	
	//set up the swapped back buffer drawing
	clear_screen();
	
	wait_for_vsync(); //swap buffers
	//char buffer variables
	int x;
	char* text;
	
	//char to be converted from int
	
	initial_board();
	
}

void plot_pixel(int x, int y, short int color){
	*(short int *)(pixel_buffer_start+(y<<10)+(x<<1)) = color;
}


void clear_screen(){
	for(int x=0; x<240; x++){
		for(int y=0; y<240; y++){
			if (x == 32 || x == 208){
				plot_pixel(x, y, 0x0000);
			}
			else if (y == 32 | y == 208){
				plot_pixel(x, y, 0x0000);
			}
			else{
				plot_pixel(x, y, 0xCF3A);
			}
		}
	}
	for (int x=51; x<189; x+=19){
		for (int y=0; y<32; y++){
			plot_pixel(x, y, 0x0000);
		}
	}
	for(int x=51; x<189; x+=19){
		for(int y=208; y<240; y++){
			plot_pixel(x, y, 0x0000);
		}
	}
	for(int x=0; x<32; x++){
		for(int y=51; y<189; y+=19){
			plot_pixel(x, y, 0x0000);
		}
	}
	for(int x=208; x<240; x++){
		for(int y=51; y<189; y+=19){
			plot_pixel(x, y, 0x0000);
		}
	}

	for(int x=240; x<320; x++){
		for(int y=0; y<240; y++){
			plot_pixel(x, y, 0x0000);
		}
	}
	
}

initial_board(){
	//main border lines
	

//void draw_line(int x1, int y1, int x2, int y2){
	
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
