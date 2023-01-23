#pragma once

#include "stdbool.h"

///////////////////////////////////////////////////////////////////////////////
// struct definitions
struct DrawSquare
{
    char *type;
    int x1;
    int x2;
    int y1;
    int y2;
    int color;
    int orientation;
};

///////////////////////////////////////////////////////////////////////////////
// prototypes

void set_square_structs();
void plot_pixel(int x, int y, short int color);
void draw_rectangle_with_border(int x1, int y1, int x2, int y2, int color);
void draw_circle(int x, int y, int r, int color);
void draw_arc(int x, int y, int radius, int start_degrees, int end_degrees, int thickness, int color);
void draw_horizontal(int x_start, int x_end, int y, int thickness, int color);
void draw_vertical(int x, int y_start, int y_end, int thickness, int color);

void draw_railroad(int x1, int y1, int x2, int y2, int orientation);
void draw_jail();
void draw_go();
void draw_chance(int x, int y, int orientation);
void draw_chest(int x1, int y1, int x2, int y2, int orientation);
void plot_bitmap_row(char hex, int x, int y, int colour);
void plot_monochrome_bitmap(char bitmap[], int x, int y, int width, int height, int colour);
void draw_dice(int x, int y, int num);
void draw_single_player(int x, int y, int player);

void init_graphics();
void draw_plain_board();
void draw_bank_balance(int player, int value);
void draw_dice_roll(int r1, int r2);
void draw_1_player(int square, int player);
void draw_2_player(int square, int player1, int player2);
void draw_3_player(int square, int player1, int player2, int player3);
void draw_4_player(int square, int player1, int player2, int player3, int player4);
void draw_owned_property(int player, int property);
void draw_houses(int property, int num_houses);

void clear_text_buffer();
void draw_text(char *text, int x_position, int y_position);
int write_string(char *line, int max_x, int max_y, int start_x, int start_y);
void draw_dialogue(char *question, int num_options, char **options, bool chance, bool community_chest);
void draw_player_turn(int player);
void draw_board_frame();
void draw_options_box(char *question,
                      int num_options,
                      char **options,
                      bool chance,
                      bool community_chest);

void wait_for_vsync();
