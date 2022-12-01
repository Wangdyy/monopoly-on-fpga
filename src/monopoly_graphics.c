// board is 240 square width
// corner squares are 32 pixels width
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
#define WHITE 0xffff
#define CREAM 0xEF5B

void init_graphics(int num_players);
void draw_bank_balance(int player, int value);
void set_square_structs();
void wait_for_vsync();
void plot_pixel(int x, int y, short int color);
void draw_rectangle(int x1, int y1, int x2, int y2, int color);
void draw_circle(int x, int y, int r, int color);
void draw_railroad(int x1, int y1, int x2, int y2, int orientation);
void draw_jail();
void draw_go();
void draw_arc(int x, int y, int radius, int start_degrees, int end_degrees, int thickness, int color);
void draw_horizontal(int x_start, int x_end, int y, int thickness, int color);
void draw_vertical(int x, int y_start, int y_end, int thickness, int color);
void draw_chance(int x, int y, int orientation);
void draw_chest(int x1, int y1, int x2, int y2, int orientation);
void plot_bitmap_row(char hex, int x, int y, int colour);
void plot_monochrome_bitmap(char bitmap[], int x, int y, int width, int height, int colour);

void draw_text(char *text, int x_position, int y_position);
int write_string(char *line, int max_x, int max_y, int start_x, int start_y);
void draw_dialogue(char *question, int num_options, char **options, bool chance, bool community_chest);
void draw_dice(int x, int y, int num);
void draw_player(int x, int y, int player);

void roll_dice(int r1, int r2);
void move_player(int from, int to, bool to_jail, int player);

char water[256] = "c7ffffffbbffffffbbffffffbbffffffbbffffffd7ffffffefffffffffffffff87ffffffb7fdffffb7fdffffb801ffffbffdffffdffdffffe001ffffffbdffffffbdfffffe0fffff";
char water_blue[256] = "ffffffffc7ffffffc7ffffffc7ffffffc7ffffffefffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";
char parking[128] = "ffffffffffffffffffffffffdd5545a3cc4ced2bd554ecafcecd45b3ffffffffffffffffffffffffff7511ffff7577ffff1333ffff7577ffff1311ffffffffff";
char gotojail[128] = "f1ed830ff5edef7ffde1ef7ffdedef7ffdedef7ff073837fffffffffffffffffffffffffffffffff8387f787bb33f733b37bf77bbf7bf77bbb33f733c387c187";
char jail[48] = "ffffffffc6a23fffd6b6fffff636fffff6b6ffffc362ffff";
char paytax[128] = "b55fffffb55fffffb1bfffffb55fffff1b5fffffffffffffffffffffffffffff75bfffff75bfffff11bfffff555fffff1b5fffffffffffff";
char lightbulb[128] = "ffffffffffffffffffff07fffffcf9fffff3feffffceff7ff0317fbff28fbfbff10fbfbff0317fbfffceff7ffff3fefffffcf9ffffff07ffffffffffffffffff";
char lightbulb_yellow[128] = "ffffffffffffffffffffffffffff07fffffc01fffff100ffffce807ffd70407ffef0407fffce807ffff100fffffc01ffffff07ffffffffffffffffffffffffff";
char choice_symbols[46] = "1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,./";
char monopoly_text[800] = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffc71c7f03f8fc7f03f8fffc0fe003f8ffffffffffc71c7c00f8f87c00f8fff003e003f8ffffffffffc60c787878f8787878ffe1e1e3fff8ffffffffffc64c78fc78f078fc78ffe3f1e3fff8ffffffffffc64c71fe38f071fe38ffc7f8e3fff8ffffffffffc64c71fe38e471fe38ffc7f8e3fff8ffffffffffc44471fe38e471fe3803c7f8e3fff07fffffffffc4e471fe38cc71fe3801c7f8e3fff07fffffffffc4e471fe38cc71fe38f0c7f8e3ffe23fffffffffc4e471fe389c71fe38f8c7f8e3ffe23fffffffffc0e071fe389c71fe38f8c7f8e3ffc71fffffffffc0e078fc783c78fc78f8e3f1e3ffc71fffffffffc1f07878783c787878f0e1e1e3ff870fffffffffc1f07c00f87c7c00f801f003e3ff8f8fffffffffc1f07f03f87c7f03f803fc0fe3ff8f8fffffffffffffffffffffffffffffffffffffffffffff";
char player1[196] = "3f8139e7c067cf033f8139e7c0678f033f9f39e7cfe79fcf3f9f39e7cfe71fcf3f9f01e7cfe73fcf039f01e7c0603fcf019f39c3c0601fcf399f39c3cfe79fcf399f9399cfe79f4f399f9399cfe79f0f019fc73cc0601f8f039fc73cc0603fcf";
char zero[98] = "87ffffff03ffffff33ffffff33ffffff33ffffff33ffffff33ffffff33ffffff33ffffff33ffffff03ffffff87ffffffzz";
char one[98] = "c0ffffffc0fffffff3fffffff3fffffff3fffffff3fffffff3fffffff3ffffffd3ffffffc3ffffffe3fffffff3ffffffzz";
char two[98] = "03ffffff03ffffff3fffffff1fffffff8fffffffc7ffffffe3fffffff3ffffff33ffffff33ffffff03ffffff87ffffffzz";
char three[98] = "c3ffffff81ffffff99ffffff99fffffff9ffffffe1ffffffe3fffffff9ffffff99ffffff99ffffff81ffffffc3ffffffzz";
char four[96] = "f9fffffff9fffffff9fffffff9ffffff80ffffff80ffffff99ffffff89ffffffc1ffffffe1fffffff1fffffff9ffffff";
char five[96] = "87ffffff03ffffff33ffffff33fffffff3fffffff3ffffff03ffffff03ffffff3fffffff3fffffff03ffffff03ffffff";
char six[96] = "87ffffff03ffffff33ffffff33ffffff33ffffff03ffffff07ffffff3fffffff3fffffff33ffffff03ffffff87ffffff";
char seven[96] = "3fffffff3fffffff9fffffff9fffffffcfffffffcfffffffcfffffffe7ffffffe7fffffff3ffffff03ffffff03ffffff";
char eight[98] = "87ffffff87ffffff33ffffff33ffffff33ffffff03ffffff87ffffff33ffffff33ffffff33ffffff87ffffff87ffffffzz";
char nine[98] = "87ffffff03ffffff33fffffff3fffffff3ffffff83ffffff03ffffff33ffffff33ffffff33ffffff03ffffff87ffffffzz";


char dollar_sign[98]="efffffff83ffffff01ffffff29ffffffe9ffffff81ffffff03ffffff2fffffff29ffffff81ffffff83ffffffefffffffzz";
char bank[212]="8079f33f19f9ffff8039f33f19f9ffff9f99f33e19f3ffff9f99f33c19e3ffff9f98033c99c7ffff9f98033998cfffff8038e331981fffff8018e333981fffff9f98e327998fffff9f9c470799c7ffff9f9e0f0f99e3ffff803e0f1f99f1ffff807f1f1f99f9ffffzzzz";

void write_char(int x, int y, char c)
{
	// VGA character buffer
	volatile char *character_buffer = (char *)(0xC9000000 + (y << 7) + x);
	*character_buffer = c;
}

int min(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int max(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int abs(int x){
	if (x < 0){
		x *= -1;
	}
	return x;
}

// global variables
volatile int pixel_buffer_start;
volatile int *pixel_ctrl_ptr;

struct Square
{
	char *type;
	int x1;
	int x2;
	int y1;
	int y2;
	int color;
	int orientation;
};

struct Square squares[40];
//bottom row structures
struct Square go = {"Go", 208, 240, 208, 240, WHITE, 1};
struct Square b1 = {"Property", 185, 208, 208, 240, BROWN, 1};
struct Square chest1 = {"Chest", 166, 184, 208, 240, WHITE, 1};
struct Square b2 = {"Property", 147, 165, 208, 240, BROWN, 1};
struct Square tax = {"Tax", 128, 146, 208, 240, WHITE, 1};
struct Square rail1 = {"Railroad", 109, 127, 208, 240, WHITE, 1};
struct Square lb1 = {"Property", 90, 108, 208, 240, WHITE, 1};
struct Square chance1 = {"Chance", 71, 89, 208, 240, WHITE, 1};
struct Square lb2 = {"Property", 52, 70, 208, 240, WHITE, 1};
struct Square lb3 = {"Property", 33, 51, 208, 240, WHITE, 1};

//left structures
struct Square jail1 = {"Jail", 0, 32, 208, 240, WHITE, 2};
struct Square p1 = {"Property", 0, 32, 185, 208, PINK, 2};
struct Square electric = {"Utility", 0, 32, 166, 184, WHITE, 2};
struct Square p2 = {"Property", 0, 32, 147, 165, PINK, 2};
struct Square p3 = {"Property", 0, 32, 128, 146, PINK, 2};
struct Square rail2 = {"Railroad", 0, 32, 109, 127, WHITE, 2};
struct Square o1 = {"Property", 0, 32, 90, 108, ORANGE, 2};
struct Square chest2 = {"Chest", 0, 32, 71, 89, WHITE, 2};
struct Square o2 = {"Property", 0, 32, 52, 70, ORANGE, 2};
struct Square o3 = {"Property", 0, 32, 33, 51, ORANGE, 2};

//top row structures
struct Square freeparking = {"Parking", 0, 32, 0, 32, WHITE, 3};
struct Square r1 = {"Property", 33, 51, 0, 32, RED, 3};
struct Square chance2 = {"Chance", 52, 70, 0, 32, WHITE, 3};
struct Square r2 = {"Property", 71, 89, 0, 32, RED, 3};
struct Square r3 = {"Property", 90, 108, 0, 32, RED, 3};
struct Square rail3 = {"Railroad", 109, 127, 0, 32, WHITE, 3};
struct Square yel1 = {"Property", 128, 146, 0, 32, YELLOW, 3};
struct Square yel2 = {"Property", 147, 165, 0, 32, YELLOW, 3};
struct Square waterworks = {"Utility", 166, 184, 0, 32, WHITE, 3};
struct Square yel3 = {"Property", 185, 208, 0, 32, YELLOW, 3};

//right structures
struct Square gojail = {"Go to Jail", 208, 240, 0, 32, WHITE, 4};
struct Square g1 = {"Property", 208, 240, 33, 51, GREEN, 4};
struct Square g2 = {"Property", 208, 240, 52, 70, GREEN, 4};
struct Square chest3 = {"Chest", 208, 240, 71, 89, WHITE, 4};
struct Square g3 = {"Property", 208, 240, 90, 108, GREEN, 4};
struct Square rail4 = {"Railroad", 208, 240, 109, 127, WHITE, 4};
struct Square space = {"Empty", 208, 240, 128, 146, WHITE, 4};
struct Square db1 = {"Property", 208, 240, 147, 165, DARK_BLUE, 4};
struct Square chance3 = {"Chance", 208, 240, 166, 184, WHITE, 4};
struct Square db2 = {"Property", 208, 240, 185, 208, DARK_BLUE, 4};

int main(void)
{
	// set front pixel buffer to start of FPGA On-chip memory
	pixel_ctrl_ptr = (int *)0xFF203020;

	volatile int *key_ptr = (int *)0xFF200050;

	// first store the address in the back buffer
	*(pixel_ctrl_ptr + 1) = 0xC8000000;

	// now, swap the front/back buffers, to set the front buffer location
	wait_for_vsync();

	// initialize a pointer to the pixel buffer, used by drawing functions
	pixel_buffer_start = *pixel_ctrl_ptr;

	// set back pixel buffer to start of SDRAM memory
	*(pixel_ctrl_ptr + 1) = 0xC0000000;

	pixel_buffer_start = *(pixel_ctrl_ptr + 1); // we draw on the back buffer

	// initialize properties
	set_square_structs();
	// set up the back buffer drawing
	// clear character buffer
	for (int x = 0; x < 80; x++)
	{
		for (int y = 0; y < 60; y++)
		{
			char *clear = " ";
			while (*clear)
			{
				write_char(x, y, *clear);
				clear++;
			}
		}
	}

	// initialize board function- currently assumes at least 2 players
	init_graphics(4);

	wait_for_vsync(); // swap buffers

	//TESTING GRAPHIC FUNCTIONS
	roll_dice(2,3);
	move_player(3, 5, false, 2);
	move_player(5, 7, false, 2);


	// char buffer variables
	int x;
	// char* text;
}

void plot_pixel(int x, int y, short int color)
{
	*(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = color;
}

void set_square_structs(){
	squares[0] = go;
	squares[1] = b1;
	squares[2] = chest1;
	squares[3] = b2;
	squares[4] = tax;
	squares[5] = rail1;
	squares[6] = lb1;
	squares[7] = chance1;
	squares[8] = lb2;
	squares[9] = lb3;

	squares[10] = jail1;
	squares[11] = p1;
	squares[12] = electric;
	squares[13] = p2;
	squares[14] = p3;
	squares[15] = rail2;
	squares[16] = o1;
	squares[17] = chest2;
	squares[18] = o2;
	squares[19] = o3;

	squares[20] = freeparking;
	squares[21] = r1;
	squares[22] = chance2;
	squares[23] = r2;
	squares[24] = r3;
	squares[25] = rail3;
	squares[26] = yel1;
	squares[27] = yel2;
	squares[28] = waterworks;
	squares[29] = yel3;

	squares[30] = gojail;
	squares[31] = g1;
	squares[32] = g2;
	squares[33] = chest3;
	squares[34] = g3;
	squares[35] = rail4;
	squares[36] = space;
	squares[37] = db1;
	squares[38] = chance3;
	squares[39] = db2;
}


void init_graphics(int num_players)
{
	char *text;

	// draw border horizontal and vertical lines and background color
	for (int x = 0; x < 240; x++)
	{
		for (int y = 0; y < 240; y++)
		{
			if (x == 32 || x == 208)
			{
				plot_pixel(x, y, BLACK);
			}
			else if (y == 32 | y == 208)
			{
				plot_pixel(x, y, BLACK);
			}
			else
			{
				plot_pixel(x, y, BACKGROUND_COLOUR);
			}
		}
	}
	// temporarily cream area on right
	for (int x = 240; x < 320; x++)
	{
		for (int y = 0; y < 240; y++)
		{
			plot_pixel(x, y, CREAM);
		}
	}
	// draw bordes for each edge box
	for (int x = 51; x < 189; x += 19)
	{
		for (int y = 0; y < 32; y++)
		{
			plot_pixel(x, y, BLACK);
		}
	}
	for (int x = 51; x < 189; x += 19)
	{
		for (int y = 208; y < 240; y++)
		{
			plot_pixel(x, y, BLACK);
		}
	}
	for (int x = 0; x < 32; x++)
	{
		for (int y = 51; y < 189; y += 19)
		{
			plot_pixel(x, y, BLACK);
		}
	}
	for (int x = 208; x < 240; x++)
	{
		for (int y = 51; y < 189; y += 19)
		{
			plot_pixel(x, y, BLACK);
		}
	}

	// properties

	// bottom edge properties

	// light blue properties
	//#1: x1=33, y1=209, x2=51, y2 = 216
	draw_rectangle(33, 209, 51, 216, LIGHT_BLUE);
	//#2: x1=52, y1=209, x2=70, y2 = 216
	draw_rectangle(52, 209, 70, 216, LIGHT_BLUE);
	//#3: x1=90, y1=209, x2=108, y2 = 216
	draw_rectangle(90, 209, 108, 216, LIGHT_BLUE);

	// brown properties
	//#1: x1=147, y1=209, x2=165, y2 = 216
	draw_rectangle(147, 209, 165, 216, BROWN);
	//#2: x1=185, y1=209, x2=208, y2 = 216
	draw_rectangle(185, 209, 208, 216, BROWN);

	// red properties
	//#1 x1=33, y1=24, x2=51, y2 = 31
	draw_rectangle(33, 24, 51, 32, RED);
	//#2: x1=52, y1=24, x2=70, y2 = 31
	draw_rectangle(71, 24, 89, 32, RED);
	//#3: x1=90, y1=24, x2=108, y2 = 31
	draw_rectangle(90, 24, 108, 32, RED);

	// yellow properties
	//#1: x1=128, y1=24, x2=146, y2 = 31
	draw_rectangle(128, 24, 146, 32, YELLOW);
	//#2: x1=147, y1=24, x2=165, y2 = 31
	draw_rectangle(147, 24, 165, 32, YELLOW);
	//#3: x1=185, y1=24, x2=208, y2 = 31
	draw_rectangle(185, 24, 208, 32, YELLOW);

	// orange properties
	//#1: x1=25, y1=33, x2=32, y2 = 51
	draw_rectangle(25, 33, 32, 51, ORANGE);
	draw_rectangle(25, 52, 32, 70, ORANGE);
	draw_rectangle(25, 90, 32, 108, ORANGE);

	// pink properties
	draw_rectangle(25, 128, 32, 146, PINK);
	draw_rectangle(25, 147, 32, 165, PINK);
	draw_rectangle(25, 185, 32, 208, PINK);

	// green properties
	draw_rectangle(209, 33, 216, 51, GREEN);
	draw_rectangle(209, 52, 216, 70, GREEN);
	draw_rectangle(209, 90, 216, 108, GREEN);

	// pink properties
	draw_rectangle(209, 147, 216, 165, DARK_BLUE);
	draw_rectangle(209, 185, 216, 208, DARK_BLUE);

	// draw railroads
	// bottom railroad
	draw_railroad(109, 212, 127, 219, 1);
	// top railroad
	draw_railroad(109, 21, 127, 28, 1);
	// left railroad
	draw_railroad(21, 109, 28, 127, 2);
	// right railroad
	draw_railroad(212, 109, 219, 127, 2);

	// Go to jail square x: 208-240, y: 0-32
	// text = "GO TO JAIL";
	// draw_text("GO TO", 54, 2);
	//	draw_text("JAIL", 54, 4);

	// Jail square x:0-32, y: 208-240
	draw_jail();

	// Go square x:208-240, y: 208-240
	draw_go();

	// chance squares
	draw_chance(71, 209, 0);
	draw_chance(70, 32, 2);
	draw_chance(209, 185, 3);

	// community chests
	draw_chest(166, 209, 184, 216, 1);
	draw_chest(32, 71, 0, 89, 2);
	draw_chest(209, 89, 240, 71, 4);
	

	plot_monochrome_bitmap(jail, 12, 225, 32, 6, BLACK);
	plot_monochrome_bitmap(water, 167, 5, 32, 18, BLACK);
	plot_monochrome_bitmap(water_blue, 167, 5, 32, 18, LIGHT_BLUE);
	plot_monochrome_bitmap(parking, 0, 5, 32, 16, BLACK);
	plot_monochrome_bitmap(gotojail, 209, 5, 32, 16, BLACK);
	plot_monochrome_bitmap(paytax, 131, 215, 32, 14, BLACK);
	plot_monochrome_bitmap(lightbulb, 0, 167, 32, 16, BLACK);
	plot_monochrome_bitmap(lightbulb_yellow, 0, 167, 32, 16, YELLOW);
	plot_monochrome_bitmap(monopoly_text, 43, 55, 160, 20, RED);
	plot_monochrome_bitmap(player1, 248, 10, 64, 12, BLACK);
    plot_monochrome_bitmap(bank, 255, 55, 64, 13, BLACK);
	
	//draw inital player positions on GO
	if (num_players == 2){
		draw_2player(0,1,2);
	}
	else if (num_players ==3){
		draw_3player(0,1,2,3);
	}
	else{
		draw_4player(0,1,2,3,4);
	}
	
	//BANK
	//draw player numbers for bank
	plot_monochrome_bitmap(one, 243, 80, 32, 12, BLACK);
	plot_monochrome_bitmap(two, 244, 100, 32, 12, BLACK);
	
	if(num_players>2){
		plot_monochrome_bitmap(three, 244, 120, 32, 12, BLACK);
	}
	if (num_players ==4){
		plot_monochrome_bitmap(four, 244, 140, 32, 12, BLACK);
	}
	
	//draw inital bank balance of $1500
	for (int i = 1; i<num_players+1; i++){
		int y = 60 + i*20;
		plot_monochrome_bitmap(dollar_sign, 256, y, 32, 12, BLACK);
		draw_bank_balance(i, 1500);
		
	}	
}

void draw_bank_balance(int player, int value){
    
    //set y value higher of balance based on player
    //balances are 20 px apart and 60 px from top
    int y = player*20+60;
    //set x value of first number to 264, will increment by 8 px each time
    int x = 264;

    //convert int to string, 7 is max number of digits
    char val[7];
    sprintf(val, "%d", value);
    //iterate through value and print number accordingly
    for (int i = 0; i< strlen(val); i++){
        switch (val[i])
	    {
	    case '0':
            plot_monochrome_bitmap(zero, x, y, 32, 12, BLACK);
			break;
    	case '1'   :
            plot_monochrome_bitmap(one, x, y, 32, 12, BLACK);
			break;
    	case '2':
            plot_monochrome_bitmap(two, x, y, 32, 12, BLACK);
			break;
	    case '3':
            plot_monochrome_bitmap(three, x, y, 32, 12, BLACK);
			break;
	    case '4':
            plot_monochrome_bitmap(four, x, y, 32, 12, BLACK);
			break;
	    case '5':
            plot_monochrome_bitmap(five, x, y, 32, 12, BLACK);
			break;
	    case '6':
            plot_monochrome_bitmap(six, x, y, 32, 12, BLACK);
			break;
	    case '7':
            plot_monochrome_bitmap(seven, x, y, 32, 12, BLACK);
			break;
	    case '8':
            plot_monochrome_bitmap(eight, x, y, 32, 12, BLACK);
			break;
	    case '9':
            plot_monochrome_bitmap(nine, x, y, 32, 12, BLACK);
			break;
	    }
		x+=8;
    }
    
    

}

void move_player(int from, int to, bool to_jail, int player){

	init_graphics(4);
	draw_1player(to, player);
	wait_for_vsync();
}

void draw_1player(int square, int player){
	int x = squares[square].x1 + ((squares[square].x2 - squares[square].x1)/2);
	int y = squares[square].y1 + ((squares[square].y2 - squares[square].y1)/2);

	draw_player(x, y, player);
}

void draw_2player(int square, int player1, int player2){
	int x1 = squares[square].x1 + ((squares[square].x2 - squares[square].x1)/2);
	int y1 = squares[square].y1 + ((squares[square].y2 - squares[square].y1)/3);

	int x2 = squares[square].x1 + ((squares[square].x2 - squares[square].x1)/2);
	int y2 = squares[square].y1 + (2*(squares[square].y2 - squares[square].y1)/3);

	draw_player(x1, y1, player1);
	draw_player(x2, y2, player2);
}

void draw_3player(int square, int player1, int player2, int player3){
	int x1 = squares[square].x1 + ((squares[square].x2 - squares[square].x1)/2);
	int y1 = squares[square].y1 + ((squares[square].y2 - squares[square].y1)/3);

	int x2 = squares[square].x1 + ((squares[square].x2 - squares[square].x1)/3);
	int y2 = squares[square].y1 + (2*(squares[square].y2 - squares[square].y1)/3);

	int x3 = squares[square].x1 + (2*(squares[square].x2 - squares[square].x1)/3);
	int y3 = squares[square].y1 + (2*(squares[square].y2 - squares[square].y1)/3);

	draw_player(x1, y1, player1);
	draw_player(x2, y2, player2);
	draw_player(x3, y3, player3);

}

void draw_4player(int square, int player1, int player2, int player3, int player4){
	int x1 = squares[square].x1 + ((squares[square].x2 - squares[square].x1)/3);
	int y1 = squares[square].y1 + ((squares[square].y2 - squares[square].y1)/3);

	int x2 = squares[square].x1 + (2*(squares[square].x2 - squares[square].x1)/3);
	int y2 = squares[square].y1 + ((squares[square].y2 - squares[square].y1)/3);

	int x3 = squares[square].x1 + ((squares[square].x2 - squares[square].x1)/3);
	int y3 = squares[square].y1 + (2*(squares[square].y2 - squares[square].y1)/3);

	int x4 = squares[square].x1 + (2*(squares[square].x2 - squares[square].x1)/3);
	int y4 = squares[square].y1 + (2*(squares[square].y2 - squares[square].y1)/3);

	draw_player(x1, y1, player1);
	draw_player(x2, y2, player2);
	draw_player(x3, y3, player3);
	draw_player(x4, y4, player4);
}

void draw_player(int x, int y, int player){
	int color;
	int colors[] = {DARK_BLUE, GREEN, YELLOW, RED, PINK, ORANGE};
	color = colors[player - 1];
	draw_circle(x, y, 3, color);
}

void roll_dice(int r1, int r2){
    init_graphics(4);
	//dice are 40 x 40
	draw_dice(70,130,r1);
	draw_dice(130,130,r2);
	wait_for_vsync();
	
}

void draw_dice(int x, int y, int num){
	draw_rectangle(x, y, x+40, y+40, WHITE);
	if (num == 1){
		draw_circle(x+20, y+20, 4, BLACK);
	}
	else if (num == 2){
		draw_circle(x+10, y+10, 4, BLACK);
		draw_circle(x+30, y+30, 4, BLACK);	
	}
	else if (num == 3){
		draw_circle(x+10, y+10, 4, BLACK);
		draw_circle(x+20, y+20, 4, BLACK);
		draw_circle(x+30, y+30, 4, BLACK);
	}
	else if (num == 4){
		draw_circle(x+10, y+10, 4, BLACK);
		draw_circle(x+30, y+30, 4, BLACK);
		draw_circle(x+10, y+30, 4, BLACK);
		draw_circle(x+30, y+10, 4, BLACK);
	}
	else if (num == 5){
		draw_circle(x+10, y+10, 4, BLACK);
		draw_circle(x+30, y+30, 4, BLACK);
		draw_circle(x+10, y+30, 4, BLACK);
		draw_circle(x+30, y+10, 4, BLACK);
		draw_circle(x+20, y+20, 4, BLACK);

	}
	else if (num == 6){
		draw_circle(x+10, y+10, 3, BLACK);
		draw_circle(x+30, y+30, 3, BLACK);
		draw_circle(x+10, y+30, 3, BLACK);
		draw_circle(x+30, y+10, 3, BLACK);
		draw_circle(x+20, y+10, 3, BLACK);
		draw_circle(x+20, y+30, 3, BLACK);
	}
}

void plot_monochrome_bitmap(char bitmap[], int x, int y, int width, int height, int colour)
{
	// Take in an array of hex values of a bitmap to be plotted
	// bitmap should have width of 32 px
	// x, y are the upper-left coordinates
	// Read from the start to end of the char array, plot bottom to top
	// length refers to the array size of bitmap
	// length must be a multiple of 32
	int length = width * height / 4;
	int row = height - 1;
	// row=0
	// row=1
	// row=2
	int col = 0;
	int num_cols = width / 4;
	// Each col represents a row of 4 pixels
	for (int i = 0; i < length; i++)
	{
		plot_bitmap_row(bitmap[i], x + col * 4, y + row, colour);
		col += 1;
		if (col == num_cols)
		{
			col = 0;
			row -= 1;
		}
	}
}

void plot_bitmap_row(char hex, int x, int y, int colour)
{
	// Plots in a hexadecimal value representing a monochrome bitmap row of 4 pixels
	// 1 bit = 1 pixel
	// Row is plotted from left to right
	// 0 will not be plotted, 1 will be plotted with colour
	char b0 = 0;
	char b1 = 0;
	char b2 = 0;
	char b3 = 0;

	switch (hex)
	{
	case '0':
		b0 = 0;
		b1 = 0;
		b2 = 0;
		b3 = 0;
		break;
	case '1':
		b0 = 0;
		b1 = 0;
		b2 = 0;
		b3 = 1;
		break;
	case '2':
		b0 = 0;
		b1 = 0;
		b2 = 1;
		b3 = 0;
		break;
	case '3':
		b0 = 0;
		b1 = 0;
		b2 = 1;
		b3 = 1;
		break;
	case '4':
		b0 = 0;
		b1 = 1;
		b2 = 0;
		b3 = 0;
		break;
	case '5':
		b0 = 0;
		b1 = 1;
		b2 = 0;
		b3 = 1;
		break;
	case '6':
		b0 = 0;
		b1 = 1;
		b2 = 1;
		b3 = 0;
		break;
	case '7':
		b0 = 0;
		b1 = 1;
		b2 = 1;
		b3 = 1;
		break;
	case '8':
		b0 = 1;
		b1 = 0;
		b2 = 0;
		b3 = 0;
		break;
	case '9':
		b0 = 1;
		b1 = 0;
		b2 = 0;
		b3 = 1;
		break;
	case 'a':
		b0 = 1;
		b1 = 0;
		b2 = 1;
		b3 = 0;
		break;
	case 'b':
		b0 = 1;
		b1 = 0;
		b2 = 1;
		b3 = 1;
		break;
	case 'c':
		b0 = 1;
		b1 = 1;
		b2 = 0;
		b3 = 0;
		break;
	case 'd':
		b0 = 1;
		b1 = 1;
		b2 = 0;
		b3 = 1;
		break;
	case 'e':
		b0 = 1;
		b1 = 1;
		b2 = 1;
		b3 = 0;
		break;
	case 'f':
		b0 = 1;
		b1 = 1;
		b2 = 1;
		b3 = 1;
		break;
	}
	if (b0 == 0)
	{
		plot_pixel(x, y, colour);
	}
	if (b1 == 0)
	{
		plot_pixel(x + 1, y, colour);
	}
	if (b2 == 0)
	{
		plot_pixel(x + 2, y, colour);
	}
	if (b3 == 0)
	{
		plot_pixel(x + 3, y, colour);
	}
}

void draw_chest(int x1, int y1, int x2, int y2, int orientation)
{
	if (orientation == 1)
	{
		int corner_x = x1 - 7 + ((x2 - x1) / 2);
		int corner_y = y1 + 11;
		draw_rectangle(corner_x, corner_y, corner_x + 14, corner_y + 3, BROWN);
		draw_rectangle(corner_x, corner_y + 3, corner_x + 14, corner_y + 10, BROWN);
		draw_horizontal(corner_x, corner_x + 13, corner_y + 2, 1, YELLOW);
		draw_vertical(corner_x, corner_y, corner_y + 9, 1, YELLOW);
		draw_vertical(corner_x + 13, corner_y, corner_y + 9, 1, YELLOW);
		draw_horizontal(corner_x, corner_x + 13, corner_y + 3, 1, BLACK);
		draw_horizontal(corner_x, corner_x + 13, corner_y + 9, 1, YELLOW);
		draw_rectangle(corner_x + 6, corner_y + 2, corner_x + 8, corner_y + 4, YELLOW);
	}
	if (orientation == 2)
	{
		int corner_y = y1 - 7 + ((y2 - y1) / 2);
		int corner_x = x1 - 11;
		draw_rectangle(corner_x - 3, corner_y, corner_x + 1, corner_y + 14, BROWN);
		draw_rectangle(corner_x - 10, corner_y, corner_x - 3, corner_y + 14, BROWN);
		draw_vertical(corner_x - 2, corner_y, corner_y + 13, 1, YELLOW);
		draw_horizontal(corner_x - 9, corner_x, corner_y, 1, YELLOW);
		draw_horizontal(corner_x - 9, corner_x, corner_y + 13, 1, YELLOW);
		draw_vertical(corner_x - 3, corner_y, corner_y + 13, 1, BLACK);
		draw_vertical(corner_x - 10, corner_y, corner_y + 13, 1, YELLOW);
		draw_rectangle(corner_x - 4, corner_y + 6, corner_x - 2, corner_y + 8, YELLOW);
	}
	if (orientation == 3)
	{
		int corner_x = x1 - 7 + ((x2 - x1) / 2);
		int corner_y = y1 - 11;
		draw_rectangle(corner_x, corner_y, corner_x - 14, corner_y - 3, BROWN);
		draw_rectangle(corner_x, corner_y - 3, corner_x - 14, corner_y - 10, BROWN);
		draw_horizontal(corner_x, corner_x - 13, corner_y - 2, 1, YELLOW);
		draw_vertical(corner_x, corner_y, corner_y - 9, 1, YELLOW);
		draw_vertical(corner_x - 13, corner_y, corner_y - 9, 1, YELLOW);
		draw_horizontal(corner_x, corner_x - 13, corner_y - 3, 1, BLACK);
		draw_horizontal(corner_x, corner_x - 13, corner_y - 9, 1, YELLOW);
		draw_rectangle(corner_x - 6, corner_y - 2, corner_x - 8, corner_y - 4, YELLOW);
	}
	if (orientation == 4)
	{
		int corner_y = y1 + 7 - ((y1 - y2) / 2);
		int corner_x = x1 + 11;
		draw_rectangle(corner_x + 3, corner_y, corner_x - 1, corner_y - 14, BROWN);
		draw_rectangle(corner_x + 10, corner_y, corner_x + 3, corner_y - 14, BROWN);
		draw_vertical(corner_x + 1, corner_y - 1, corner_y - 14, 1, YELLOW);
		draw_horizontal(corner_x + 8, corner_x - 1, corner_y - 1, 1, YELLOW);
		draw_horizontal(corner_x + 8, corner_x - 1, corner_y - 14, 1, YELLOW);
		draw_vertical(corner_x + 2, corner_y - 1, corner_y - 14, 1, BLACK);
		draw_vertical(corner_x + 9, corner_y - 1, corner_y - 14, 1, YELLOW);
		draw_rectangle(corner_x + 4, corner_y - 6, corner_x + 2, corner_y - 8, YELLOW);
	}
}

// Test horizontal and vertical line functions
// draw_horizontal(100,140,120,2,BLACK);
// draw_vertical(100,140,160,2,BLACK);
void draw_arc(int x, int y, int radius, int start_degrees, int end_degrees, int thickness, int color)
{
	// x and y define the centre of arc, radius defines the inner radius
	// draw an arc from start_degrees to end_degrees
	for (int thickness_offset = 0; thickness_offset < thickness; thickness_offset++)
	{
		int x_current;
		int y_current;
		int radius_current = radius + thickness_offset;
		for (int current_degree = start_degrees; current_degree < end_degrees; current_degree++)
		{
			// Set x_current, y_current
			double current_radians = current_degree * 0.017453;
			x_current = round(x + radius_current * cos(current_radians));
			y_current = round(y + radius_current * sin(current_radians));
			plot_pixel(x_current, y_current, BLACK);
		}
	}
}

void draw_horizontal(int x_start, int x_end, int y, int thickness, int color)
{
	for (int x_current = min(x_start, x_end); x_current <= max(x_start, x_end); x_current++)
	{
		for (int y_offset = 0; y_offset < thickness; y_offset++)
		{
			plot_pixel(x_current, y + y_offset, color);
		}
	}
}

void draw_vertical(int x, int y_start, int y_end, int thickness, int color)
{
	for (int y_current = min(y_start, y_end); y_current <= max(y_start, y_end); y_current++)
	{
		for (int x_offset = 0; x_offset < thickness; x_offset++)
		{
			plot_pixel(x + x_offset, y_current, color);
		}
	}
}

void draw_go()
{
	draw_rectangle(216, 231, 236, 234, RED);
	// Draw the triangle on the left
	int y = 232;
	int height = 1;
	plot_pixel(211, 232, BLACK);
	for (int x = 212; x < 216; x++)
	{
		plot_pixel(x, y + height, BLACK);
		plot_pixel(x, y - height, BLACK);
		for (int y_offset = 0; y_offset < height; y_offset++)
		{
			int y = 232 + y_offset;
			plot_pixel(x, y, RED);
			y = 232 - y_offset;
			plot_pixel(x, y, RED);
		}
		height++;
	}
	for (int y_offset = 0; y_offset < height; y_offset++)
	{
		plot_pixel(216, 232 + y_offset, BLACK);
		plot_pixel(216, 232 - y_offset, BLACK);
	}
	for (int x = 216; x < 237; x++)
	{
		plot_pixel(x, 230, BLACK);
		plot_pixel(x, 234, BLACK);
	}
	draw_vertical(216, 231, 234, 1, RED);
	draw_arc(217, 219, 5, 0, 315, 2, BLACK);
	draw_rectangle(217, 219, 222, 220, BLACK);
	draw_arc(231, 219, 5, 0, 360, 2, BLACK);
}

void draw_railroad(int x1, int y1, int x2, int y2, int orientation)
{
	int horizontal;
	if (orientation == 1)
	{
		for (int x = x1; x < x2; x++)
		{
			for (int y = y1; y < y2; y++)
			{
				if (x % 2 == 0)
				{
					plot_pixel(x, y, BLACK);
				}
				if (y == y1 + 1 || y == y2 - 2)
				{
					plot_pixel(x, y, BLACK);
				}
			}
		}
	}
	else
	{
		for (int x = x1; x < x2; x++)
		{
			for (int y = y1; y < y2; y++)
			{
				if (y % 2 == 0)
				{
					plot_pixel(x, y, BLACK);
				}
				if (x == x1 + 1 || x == x2 - 2)
				{
					plot_pixel(x, y, BLACK);
				}
			}
		}
	}
}

void draw_jail()
{
	draw_rectangle(10, 209, 32, 231, ORANGE);
	for (int x = 9; x < 32; x++)
	{
		plot_pixel(x, 231, BLACK);
	}
	draw_rectangle(16, 212, 27, 223, WHITE);
	for (int x = 15; x < 28; x++)
	{
		plot_pixel(x, 211, BLACK);
		plot_pixel(x, 223, BLACK);
	}
	for (int x = 18; x < 28; x = x + 3)
	{
		for (int y = 211; y < 223; y++)
		{
			plot_pixel(x, y, BLACK);
		}
	}
}

void draw_chance(int x, int y, int orientation)
{
	// 0 -> bottom 1->left 2-> top 3-> right

	if (orientation == 0)
	{
		draw_arc(x + 9, y + 11, 5, 180 + 90 * orientation, 420 + 90 * orientation, 1, BLACK);
		draw_arc(x + 14, y + 19, 4, 180 + 90 * orientation, 240 + 90 * orientation, 1, BLACK);
		draw_vertical(x + 9, y + 19, y + 22, 1, BLACK);
		draw_vertical(x + 9, y + 25, y + 26, 1, BLACK);
	}
	else if (orientation == 1)
	{
		draw_arc(x - 11, y + 9, 5, 180 + 90 * orientation, 420 + 90 * orientation, 1, BLACK);
		draw_arc(x - 19, y + 14, 4, 180 + 90 * orientation, 240 + 90 * orientation, 1, BLACK);
		draw_horizontal(x - 22, x - 19, y + 9, 1, BLACK);
		draw_horizontal(x - 26, x - 25, y + 9, 1, BLACK);
	}
	else if (orientation == 2)
	{
		draw_arc(x - 9, y - 11, 5, 180 + 90 * orientation, 420 + 90 * orientation, 1, BLACK);
		draw_arc(x - 14, y - 19, 4, 180 + 90 * orientation, 240 + 90 * orientation, 1, BLACK);
		draw_vertical(x - 9, y - 22, y - 19, 1, BLACK);
		draw_vertical(x - 9, y - 26, y - 25, 1, BLACK);
	}
	else if (orientation == 3)
	{
		draw_arc(x + 11, y - 10, 5, 180 + 90 * orientation, 420 + 90 * orientation, 1, BLACK);
		draw_arc(x + 19, y - 15, 4, 180 + 90 * orientation, 240 + 90 * orientation, 1, BLACK);
		draw_horizontal(x + 19, x + 22, y - 10, 1, BLACK);
		draw_horizontal(x + 25, x + 26, y - 10, 1, BLACK);
	}
}

void draw_rectangle(int x1, int y1, int x2, int y2, int color)
{
	int x_min = min(x1, x2);
	int x_max = max(x1, x2);
	int y_min = min(y1, y2);
	int y_max = max(y1, y2);

	for (int x = x_min; x < x_max; x++)
	{
		for (int y = y_min; y < y_max; y++)
		{
			plot_pixel(x, y, color);
		}
	}
	draw_horizontal(x_min - 1, x_max, y_min - 1, 1, BLACK);
	draw_horizontal(x_min - 1, x_max, y_max, 1, BLACK);
	draw_vertical(x_min - 1, y_min - 1, y_max, 1, BLACK);
	draw_vertical(x_max, y_min - 1, y_max, 1, BLACK);
}

void draw_circle(int x, int y, int r, int color){
	for (int c_x = x - r; c_x <= x + r; c_x++){
		for (int c_y = y - r; c_y <= y + r; c_y++){
			if ((pow(abs(c_x - x),2) + pow(abs(c_y - y),2)) <= pow(r,2)){
				plot_pixel(c_x, c_y, color);
			}
		}
	}
}

void wait_for_vsync()
{
	volatile int *pixel_ctrl_ptr = (int *)0xFF203020;
	register int status;

	*pixel_ctrl_ptr = 1; // start synchronization (write to buffer register)
	status = *(pixel_ctrl_ptr + 3);

	while ((status & 0x01) != 0)
	{ // wait for S to be 0
		status = *(pixel_ctrl_ptr + 3);
	}

	pixel_buffer_start = *(pixel_ctrl_ptr + 1);
}

///////////////////////////////////////////////////////////////////////////////
// text module
void draw_text(char *text, int x_position, int y_position)
{
	int x = x_position;
	while (*text)
	{
		write_char(x, y_position, *text);
		x++;
		text++;
	}
}

// writes a string over as many lines as needed and returns the last used y
int write_string(char *line, int max_x, int max_y, int start_x, int start_y)
{
	char *p1 = line, *p2 = line;
	int x = start_x, y = start_y;

	while (*p1)
	{
		// find end of next word
		while ((*p2) != ' ' && (*p2) != '\0')
		{
			p2++;
		}

		// check if word fits on this line, else go to next
		if (p2 - p1 > (max_x - x + 1))
		{
			y += 2;
			x = start_x;
		}

		// write the word
		for (char *temp = p1; temp < p2; temp++)
		{
			write_char(x++, y, *temp);
		}

		// if there are more spots in this line, add a space
		if (x < max_x && (*p2) == ' ')
		{
			write_char(x++, y, ' ');
		}

		// onto next word
		if (*p2)
		{
			p2++;
		}
		p1 = p2;
	}

	return y;
}

// display an options dialogue box with the question and key for each option
void display_options_box(char *question,
						 int num_options,
						 char **options,
						 bool chance,
						 bool community_chest)
{
	// consts
	int LINE_START = 14, LINE_END = 46;

	// background
	draw_rectangle(32 + 15, 32 + 15, 209 - 15, 209 - 15, BLACK);

	int last_y = LINE_START;

	if (chance)
	{
		last_y = write_string("CHANCE", LINE_END, LINE_END, LINE_START, last_y);
		last_y = write_string("------", LINE_END, LINE_END, LINE_START, last_y + 1);
	}
	else if (community_chest)
	{
		last_y = write_string("COMMUNITY CHEST", LINE_END, LINE_END, LINE_START, last_y);
		last_y = write_string("---------------", LINE_END, LINE_END, LINE_START, last_y + 1);
	}

	// leave a space after the question
	last_y = write_string(question, LINE_END, LINE_END, LINE_START, last_y + 2) + 2;

	for (int i = 0; i < num_options; i++)
	{
		char str[8 + strlen(options[i]) + 1];
		sprintf(str, "<%c> - %s", choice_symbols[i], options[i]);
		last_y = write_string(str, LINE_END, LINE_END, LINE_START, last_y + 2);
	}
}
