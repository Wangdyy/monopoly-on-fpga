#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "stdbool.h"
#include "gamestate.h"
#include "players.h"
#include "squares.h"
#include "interface.h"
#include "display.h"

// #define DELAY_ON	// activate delays in player movement on fpga
#define QUEUE_TYPE KeyReleased

typedef enum key_released
{
	// ENTER,
	// UP,
	// LEFT,
	// DOWN,
	// RIGHT,
	NUM_1,
	NUM_2,
	NUM_3,
	NUM_4,
	NUM_5,
	NUM_6,
	NUM_7,
	NUM_8,
	NUM_9,
	NUM_0,
	SYM_DASH,
	SYM_EQ,
	CHAR_Q,
	CHAR_W,
	CHAR_E,
	CHAR_R,
	CHAR_T,
	CHAR_Y,
	CHAR_U,
	CHAR_I,
	CHAR_O,
	CHAR_P,
	SYM_LS,
	SYM_RS,
	CHAR_A,
	CHAR_S,
	CHAR_D,
	CHAR_F,
	CHAR_G,
	CHAR_H,
	CHAR_J,
	CHAR_K,
	CHAR_L,
	SYM_SEMI,
	SYM_APOS,
	CHAR_Z,
	CHAR_X,
	CHAR_C,
	CHAR_V,
	CHAR_B,
	CHAR_N,
	CHAR_M,
	SYM_COMMA,
	SYM_DOT,
	SYM_SLASH,
	NUM_KEYS
} KeyReleased;

// Implementing the Queue data structure //
typedef struct queue
{
	unsigned int size, start, end;
	QUEUE_TYPE *elems;
} Queue;

Queue create_queue(unsigned int max_size)
{
	Queue q;

	q.size = max_size;
	q.start = 0;
	q.end = 0;

	q.elems = (QUEUE_TYPE *)malloc(sizeof(QUEUE_TYPE) * (max_size + 1));
	if (!q.elems)
	{
		printf("Unable to allocate queue of size %d\n", max_size);
		exit(-1);
	}
	return q;
}

void queue_enqueue(Queue *q, QUEUE_TYPE c)
{
	if (q->start == (q->end + 1) % (q->size + 1))
	{
		printf("Cannot insert any more elements into queue\n");
		exit(-1);
	}

	q->elems[q->end] = c;
	q->end = (q->end + 1) % (q->size + 1);
}

QUEUE_TYPE queue_dequeue(Queue *q)
{
	if (q->start == q->end)
	{
		printf("Cannot dequeue element since queue is empty\n");
		exit(-1);
	}

	QUEUE_TYPE ret = q->elems[q->start];
	q->start = (q->start + 1) % (q->size + 1);
	return ret;
}

void destroy_queue(Queue *q)
{
	free(q->elems);
}

///////////////////////////////////////////////////////////////////////////////
// Processing PS2 Keyboard Inputs //
KeyReleased map_keycode_to_key(char make_code)
{
	/* 	take advantage of the pattern that the two-byte break code of all keys
		relevant to us are in the form of '<E0> F0 (MAKE_CODE)'
	*/
	switch (make_code)
	{
		// case 0x5A:
		// 	return ENTER;

		// case 0x75:
		// 	return UP;

		// case 0x6B:
		// 	return LEFT;

		// case 0x72:
		// 	return DOWN;

		// case 0x74:
		// 	return RIGHT;

	case 0x16:
		return NUM_1;

	case 0x1E:
		return NUM_2;

	case 0x26:
		return NUM_3;

	case 0x25:
		return NUM_4;

	case 0x2E:
		return NUM_5;

	case 0x36:
		return NUM_6;

	case 0x3D:
		return NUM_7;

	case 0x3E:
		return NUM_8;

	case 0x46:
		return NUM_9;

	case 0x45:
		return NUM_0;

	case 0x4E:
		return SYM_DASH;

	case 0x55:
		return SYM_EQ;

	case 0x15:
		return CHAR_Q;

	case 0x1D:
		return CHAR_W;

	case 0x24:
		return CHAR_E;

	case 0x2D:
		return CHAR_R;

	case 0x2C:
		return CHAR_T;

	case 0x35:
		return CHAR_Y;

	case 0x3C:
		return CHAR_U;

	case 0x43:
		return CHAR_I;

	case 0x44:
		return CHAR_O;

	case 0x4D:
		return CHAR_P;

	case 0x54:
		return SYM_LS;

	case 0x5B:
		return SYM_RS;

	case 0x1C:
		return CHAR_A;

	case 0x1B:
		return CHAR_S;

	case 0x23:
		return CHAR_D;

	case 0x2B:
		return CHAR_F;

	case 0x34:
		return CHAR_G;

	case 0x33:
		return CHAR_H;

	case 0x3B:
		return CHAR_J;

	case 0x42:
		return CHAR_K;

	case 0x4B:
		return CHAR_L;

	case 0x4C:
		return SYM_SEMI;

	case 0x52:
		return SYM_APOS;

	case 0x1A:
		return CHAR_Z;

	case 0x22:
		return CHAR_X;

	case 0x21:
		return CHAR_C;

	case 0x2A:
		return CHAR_V;

	case 0x32:
		return CHAR_B;

	case 0x31:
		return CHAR_N;

	case 0x3A:
		return CHAR_M;

	case 0x41:
		return SYM_COMMA;

	case 0x49:
		return SYM_DOT;

	case 0x4A:
		return SYM_SLASH;

	default:
		return NUM_KEYS;
	}
}

void print_key(KeyReleased k)
{
	switch (k)
	{
		// case ENTER:
		// 	printf("Enter");
		// 	break;

		// case UP:
		// 	printf("Up");
		// 	break;

		// case LEFT:
		// 	printf("Left");
		// 	break;

		// case DOWN:
		// 	printf("Down");
		// 	break;

		// case RIGHT:
		// 	printf("Right");
		// 	break;

	case NUM_1:
		printf("1");
		break;

	case NUM_2:
		printf("2");
		break;

	case NUM_3:
		printf("3");
		break;

	case NUM_4:
		printf("4");
		break;

	case NUM_5:
		printf("5");
		break;

	case NUM_6:
		printf("6");
		break;

	case NUM_7:
		printf("7");
		break;

	case NUM_8:
		printf("8");
		break;

	case NUM_9:
		printf("9");
		break;

	case NUM_0:
		printf("0");
		break;

	case SYM_DASH:
		printf("-");
		break;

	case SYM_EQ:
		printf("=");
		break;

	case CHAR_Q:
		printf("q");
		break;

	case CHAR_W:
		printf("w");
		break;

	case CHAR_E:
		printf("e");
		break;

	case CHAR_R:
		printf("r");
		break;

	case CHAR_T:
		printf("t");
		break;

	case CHAR_Y:
		printf("y");
		break;

	case CHAR_U:
		printf("u");
		break;

	case CHAR_I:
		printf("i");
		break;

	case CHAR_O:
		printf("o");
		break;

	case CHAR_P:
		printf("p");
		break;

	case SYM_LS:
		printf("[");
		break;

	case SYM_RS:
		printf("]");
		break;

	case CHAR_A:
		printf("a");
		break;

	case CHAR_S:
		printf("s");
		break;

	case CHAR_D:
		printf("d");
		break;

	case CHAR_F:
		printf("f");
		break;

	case CHAR_G:
		printf("g");
		break;

	case CHAR_H:
		printf("h");
		break;

	case CHAR_J:
		printf("j");
		break;

	case CHAR_K:
		printf("k");
		break;

	case CHAR_L:
		printf("l");
		break;

	case SYM_SEMI:
		printf(";");
		break;

	case SYM_APOS:
		printf("'");
		break;

	case CHAR_Z:
		printf("z");
		break;

	case CHAR_X:
		printf("x");
		break;

	case CHAR_C:
		printf("c");
		break;

	case CHAR_V:
		printf("v");
		break;

	case CHAR_B:
		printf("b");
		break;

	case CHAR_N:
		printf("n");
		break;

	case CHAR_M:
		printf("m");
		break;

	case SYM_COMMA:
		printf(",");
		break;

	case SYM_DOT:
		printf(".");
		break;

	case SYM_SLASH:
		printf("/");
		break;

	default:
		printf("Invalid");
		break;
	}
}

void print_key_released_queue(Queue q)
{
	int i = q.start;

	while (i != q.end)
	{
		print_key(q.elems[i]);
		printf(" ");
		i = (i + 1) % (q.size + 1);
	}

	printf("\n");
}

char read_next_char()
{
	// base code taken from http://www-ug.eecg.toronto.edu/msl/handouts/DE1-SoC_Computer_Nios.pdf
	volatile int *PS2_ptr = (int *)0xFF200100; // PS/2 port address
	int data_row, data_valid;
	char data_char = 0x00;

	while (1)
	{
		data_row = *(PS2_ptr);			// read the Data register in the PS/2 port
		data_valid = data_row & 0x8000; // extract the data_valid field

		if (data_valid)
		{
			data_char = data_row & 0xFF;
			return data_char;
		}
	}
}

KeyReleased read_next_key()
{
	while (1)
	{
		char c = read_next_char();
		if (c != 0xF0)
			continue;

		return map_keycode_to_key(read_next_char());
	}
}
///////////////////////////////////////////////////////////////////////////////
// Graphics Interface & I/O functions

KeyReleased get_choice(int num_options)
{
	while (true)
	{
		KeyReleased k = read_next_key();
		if (k < num_options)
		{
			return k;
		}
	}
}

void print_options(int num_options, char **options)
{
	for (int i = 0; i < num_options; i++)
	{
		printf(" <");
		print_key(i);
		printf("> - %s ", options[i]);
	}
}

///////////////////////////////////////////////////////////////////////////////
// interface constants
int MAX_OPTS_PER_PAGE = 6;
int PREV_OPT = 6; // since there are max 6 options per page,
int NEXT_OPT = 7; // prev and next will just use the next two buttons
int MAX_HOUSES_ON_PROPERTY = 4;
int MAX_HOTELS_ON_PROPERTY = 1;
int NUM_SQUARES = 40;
char *PROPERTY_SELECT_DIALOG_OPTIONS[] = {"Next", "Prev", "Confirm", "Cancel"};
int NUM_PROPERTY_SELECT_DIALOG_OPTIONS = sizeof(PROPERTY_SELECT_DIALOG_OPTIONS) / sizeof(char *);

///////////////////////////////////////////////////////////////////////////////
// interface impl
bool location_has_players[MAX_SQUARES][MAX_PLAYERS];

void delay_ms(int ms) {
	int start = clock();
	while(clock() - start < ms);
}

void fill_location_has_players_with_gamestate(gamestate *game)
{
	for (int i = 0; i < MAX_SQUARES; i++)
	{
		for (int j = 0; j < MAX_PLAYERS; j++)
		{
			location_has_players[i][j] = 0;
		}
	}

	for (int i = 0; i < MAX_PLAYERS; i++)
		location_has_players[game->players[i].position][i] = 1;
}

void fill_location_has_players_with_values(int *positions)
{
	for (int i = 0; i < MAX_SQUARES; i++)
	{
		for (int j = 0; j < MAX_PLAYERS; j++)
		{
			location_has_players[i][j] = 0;
		}
	}
	for (int i = 0; i < MAX_PLAYERS; i++)
		location_has_players[positions[i]][i] = 1;
}

void draw_player_pieces(gamestate *game)
{
	// draw the players on the board
	for (int square_i = 0; square_i < MAX_SQUARES; square_i++)
	{
		int players_cnt = 0;
		int players_here[4];

		if (location_has_players[square_i][0])
		{
			players_here[players_cnt++] = 1;
		}

		if (location_has_players[square_i][1])
		{
			players_here[players_cnt++] = 2;
		}

		if (location_has_players[square_i][2])
		{
			players_here[players_cnt++] = 3;
		}

		if (location_has_players[square_i][3])
		{
			players_here[players_cnt++] = 4;
		}

		//special case for jail
		if (square_i == 10){
			if (players_cnt == 1)
			{
				draw_1_player_jail(square_i, players_here[0], game->players[players_here[0]-1].inJail);
			}
			else if (players_cnt == 2)
			{
				draw_2_player_jail(square_i, players_here[0], game->players[players_here[0]-1].inJail, players_here[1], game->players[players_here[1]-1].inJail);
			}
			else if (players_cnt == 3)
			{
				draw_3_player_jail(square_i, players_here[0], game->players[players_here[0]-1].inJail, players_here[1], game->players[players_here[1]-1].inJail, players_here[2], game->players[players_here[2]-1].inJail);
			}
			else if (players_cnt == 4)
			{
				draw_4_player_jail(square_i, players_here[0], game->players[players_here[0]-1].inJail,  players_here[1], game->players[players_here[1]-1].inJail, players_here[2], game->players[players_here[2]-1].inJail, players_here[3], game->players[players_here[3]-1].inJail);
			}
			continue;
		}

		if (players_cnt == 1)
		{
			draw_1_player(square_i, players_here[0]);
		}
		else if (players_cnt == 2)
		{
			draw_2_player(square_i, players_here[0], players_here[1]);
		}
		else if (players_cnt == 3)
		{
			draw_3_player(square_i, players_here[0], players_here[1], players_here[2]);
		}
		else if (players_cnt == 4)
		{
			draw_4_player(square_i, players_here[0], players_here[1], players_here[2], players_here[3]);
		}
	}
}

void draw_houses_and_hotels(gamestate *game) {
	for (int square_i = 0; square_i < MAX_SQUARES; square_i++) {
		if (game->board[square_i].type == Property) {
			propertySquare *p_prop = &(game->board[square_i].data.property);

			if (p_prop->type == Colored) {
				draw_houses(square_i, p_prop->coloredProperty.houseCount);

				if (p_prop->coloredProperty.hotelCount == 1) {
					draw_hotel(square_i);
				}
			}
		} 
	}
}

void draw_property_owners(gamestate *game) {
	for (int square_i = 0; square_i < MAX_SQUARES; square_i++) {
		if (game->board[square_i].type == Property) {
			propertySquare *p_prop = &(game->board[square_i].data.property);
			
			if (p_prop->owner != Bank) {
				draw_owned_property(p_prop->owner + 1, square_i);
			}			
		} 
	}
}

void draw_player_pieces_with_gamestate(gamestate *game)
{
	fill_location_has_players_with_gamestate(game);
	draw_player_pieces(game);
}

void draw_player_pieces_with_update(gamestate *game, int player, int pos)
{
	for (int i = 0; i < MAX_SQUARES; i++)
	{
		for (int j = 0; j < MAX_PLAYERS; j++)
		{
			location_has_players[i][j] = 0;
		}
	}

	for (int i = 0; i < MAX_PLAYERS; i++)
		if (i != player)
			location_has_players[game->players[i].position][i] = 1;
		else
			location_has_players[pos][i] = 1;

	draw_player_pieces(game);
}

void draw_all_player_cash(gamestate *game)
{
	draw_bank_balance(1, game->players[0].money);
	draw_bank_balance(2, game->players[1].money);
	draw_bank_balance(3, game->players[2].money);
	draw_bank_balance(4, game->players[3].money);
}

void draw_basic_setup_without_player_pieces(int curr_player, gamestate *game) {
	clear_text_buffer();
	draw_plain_board();
	draw_player_turn(curr_player);
	draw_property_owners(game);
	draw_houses_and_hotels(game);
	draw_all_player_cash(game);
}

void draw_basic_setup(int curr_player, gamestate *game)
{
	draw_basic_setup_without_player_pieces(curr_player, game);
	draw_player_pieces_with_gamestate(game);
}

void drawseq_turn_start(int curr_player, gamestate *game)
{
	draw_basic_setup(curr_player, game);
	wait_for_vsync();
}

int drawseq_dialogue_get_choice(int curr_player,
								gamestate *game,
								char *question,
								int num_options,
								char **options,
								bool chance,
								bool community_chest)
{
	int choice = -1;

	if (num_options <= MAX_OPTS_PER_PAGE)
	{
		draw_basic_setup(curr_player, game);
		draw_options_box(question, num_options, options, false, false, chance, community_chest);
		wait_for_vsync();
		return get_choice(num_options);
	}

	int before_page = -1, page = 0;
	int total_pages = (num_options - 1) / MAX_OPTS_PER_PAGE + 1;
	bool has_prev_page = false, has_next_page = false;

	while (choice == -1)
	{
		has_prev_page = page != 0;
		has_next_page = page != total_pages - 1;

		// skip redrawing if the choice before was illegal turning
		if (before_page != page)
		{
			int num_page_options = MAX_OPTS_PER_PAGE;
			char *page_options[MAX_OPTS_PER_PAGE];

			for (int i = 0; i < MAX_OPTS_PER_PAGE; i++)
			{
				int opt_i = page * MAX_OPTS_PER_PAGE + i;
				if (opt_i == num_options)
				{
					num_page_options = i;
					break;
				}
				page_options[i] = options[opt_i];
			}

			draw_basic_setup(curr_player, game);
			draw_options_box(question,
							 num_page_options,
							 page_options,
							 has_prev_page,
							 has_next_page,
							 chance,
							 community_chest);
			wait_for_vsync();
		}

		choice = get_choice(MAX_OPTS_PER_PAGE + 2);
		if (has_prev_page && choice == PREV_OPT)
		{
			choice = -1;
			before_page = page;
			page -= 1;
		}
		else if (has_next_page && choice == NEXT_OPT)
		{
			choice = -1;
			before_page = page;
			page += 1;
		}
		else if (choice == PREV_OPT || choice == NEXT_OPT)
		{
			// illegal page turning
			before_page = page;
			choice = -1;
		}
	}

	choice = page * MAX_OPTS_PER_PAGE + choice;
	return choice;
}

void drawseq_normal_confirm(int curr_player, gamestate *game, char *question, bool chance, bool community_chest)
{
	char *options[1] = {"Confirm"};
	drawseq_dialogue_get_choice(curr_player, game, question, 1, options, chance, community_chest);
}

bool drawseq_dialogue_yes_no(int curr_player, gamestate *game, char *question)
{
	char *options[2] = {"Yes", "No"};
	return !drawseq_dialogue_get_choice(curr_player, game, question, 2, options, false, false);
}

void drawseq_roll_dice(int curr_player, gamestate *game, diceRoll dice_roll)
{
	draw_basic_setup(curr_player, game);
	draw_dice_roll(dice_roll.die1, dice_roll.die2);
	wait_for_vsync();
}

void drawseq_move_player(int curr_player, gamestate *game, diceRoll dice_roll, int old_pos, int new_pos)
{
	for (int i = 0; i < (new_pos + NUM_SQUARES - old_pos) % NUM_SQUARES; i++)
	{
		#ifdef DELAY_ON
		delay_ms(50);
		#endif

		draw_basic_setup_without_player_pieces(curr_player, game);
		draw_dice_roll(dice_roll.die1, dice_roll.die2);
		draw_player_pieces_with_update(game, curr_player - 1, (old_pos + i + 1) % NUM_SQUARES);
		wait_for_vsync();
	}
}

void draw_property_select_screen(int curr_player, gamestate *game, int num_choices, int *choices, int curr_choice)
{
	int highlight_id = 6;

	draw_basic_setup(curr_player, game);

	// highlight all eligible property
	for (int i = 0; i < num_choices; i++)
	{
		draw_owned_property(curr_player, choices[i]);
	}

	// current highlight
	draw_owned_property(highlight_id, choices[curr_choice]);

	// instructions in the middle
	draw_options_box("Choose an eligible property:",
					 NUM_PROPERTY_SELECT_DIALOG_OPTIONS,
					 PROPERTY_SELECT_DIALOG_OPTIONS,
					 false,
					 false,
					 false,
					 false);
}

int drawseq_choose_owned_property(int curr_player, gamestate *game, int num_choices, int *choices)
{
	if (num_choices == 0)
	{
		drawseq_normal_confirm(curr_player, game, "You have no eligible properties to choose from!", false, false);
		return -1;
	}

	// start from the first property, go around until one is chosen
	int chosen = 0;

	bool done = false;
	while (!done)
	{
		draw_property_select_screen(curr_player, game, num_choices, choices, chosen);
		wait_for_vsync();

		switch (get_choice(NUM_PROPERTY_SELECT_DIALOG_OPTIONS))
		{
		case 0:
			chosen = (chosen + 1) % num_choices;
			break;
		case 1:
			chosen = (chosen + num_choices - 1) % num_choices;
			break;
		case 2:
			return chosen;
		case 3:
			return -1;
		default:
			printf("Illegal choice received.\n");
			exit(1);
		}
	}
	return -1;
}
///////////////////////////////////////////////////////////////////////////////
// Demo //
// int main()
// {
// while (1)
// {
// 	KeyReleased next_key = read_next_key();
// 	print_key(next_key);
// 	printf("\n");
// }
// Queue q = create_queue(5);
// int cnt = 0;
// while (cnt < 5)
// {
// 	KeyReleased next_key = read_next_key();
// 	if (next_key == NUM_KEYS)
// 		continue;

// 	queue_enqueue(&q, next_key);
// 	print_key_released_queue(q);
// 	cnt += 1;
// }

// printf("\nNow pop the objects one by one:\n");

// for (int i = 0; i < 5; i++)
// {
// 	print_key(queue_dequeue(&q));
// }

// 	return 0;
// }
