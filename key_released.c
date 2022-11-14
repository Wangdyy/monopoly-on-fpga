#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define QUEUE_TYPE KeyReleased

///////////////////////////////////////////////////////////////////////////////
// copied for cpulator testing //
#define MAX_PLAYERS 4
#define MAX_SQUARES 40

enum SquareNames{Go, MediteraneanAvenue, CommunityChest1, BalticAvenue, IncomeTax, ReadingRailRoad, 
OrientalAvenue, Chance1, VermontAvenue, ConnecticutAvenue, JustVisiting, 
StCharlesPlace, ElectricCompany, StatesAvenue, VirginiaAvenue, PennsylvaniaRailRoad, 
StJamesPlace, CommunityChest2, TennesseeAvenue, NewYorkAvenue, FreeParking, 
KentuckyAvenue, Chance2, IndianaAvenue, IllinoisAvenue, BAndORailRoad, 
AtlanticAvenue, VentnorAvenue, WaterWorks, MarvinGardens, GoToJail, 
PacificAvenue, NorthCarolinaAvenue, CommunityChest3, PennsylvaniaAvenue, ShortLine, 
Chance3, ParkPlace, LuxuryTax, Boardwalk};

enum SquareType {Property, Action};

enum PropertyType{Colored, RailRoad, Utility};

enum ActionType{ChanceAction, CommunityChestAction, IncomeTaxAction, LuxuryTaxAction, GoToJailAction, GoAction, FreeParkingAction, JailAction};

enum Colors{Brown, LightBlue, Pink, Orange, Red, Yellow, Green, DarkBlue};

enum Owners{Player1, Player2, Player3, Player4, Bank};

typedef struct ColoredProperty {
    enum Colors color;
    int houseCost;
    int hotelCost;
    int houseCount;
    int hotelCount;
    int rent[6];
} coloredProperty;

typedef struct propertySquare {
    enum PropertyType type;
    enum Owners owner;
    int price;
    bool mortgaged;
    coloredProperty coloredPropety;
} propertySquare;

typedef struct square{
    char name[20];
    enum SquareType type;
    enum SquareNames squareName;
    union Square{
        propertySquare property;
        enum ActionType action;
    } data;
} square;

typedef struct player{
    char name[20]; /*Not implementing name yet, just called players 1-4*/
    enum Owners owner;
    int money;
    enum SquareNames position;
    int jailTime;
    bool inJail;
    bool bankrupt;
    square* owned_properties[28];
    int owned_properties_count;
} player;

typedef struct gamestate{
    square board[40];
    player players[4];
    int player_count;
    int turn;
    /*Doubles not implemented, does not lead to extra turn*/
    int doubles; //TODO: Reset to 0 after player turn ends
    bool gameOver;
    /*Houses and hotels not implemented*/
    int houses;
    int hotels;
    /*Current this is only used for paying utility rent*/
    int lastDiceRoll; //TODO: Save last dice roll in game loop
} gamestate;

typedef struct diceRoll{
    int die1;
    int die2;
    bool doubles;
} diceRoll;

///////////////////////////////////////////////////////////////////////////////
typedef enum key_released {
	ENTER,
	UP,
	LEFT,
	DOWN,
	RIGHT,
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
typedef struct queue {
	unsigned int size, start, end;
	QUEUE_TYPE *elems;
} Queue;

Queue create_queue(unsigned int max_size) {
	Queue q;
	
	q.size = max_size;
	q.start = 0;
	q.end = 0;

	q.elems = (QUEUE_TYPE*) malloc (sizeof(QUEUE_TYPE) * (max_size + 1));
	if (!q.elems) {
		printf("Unable to allocate queue of size %d\n", max_size);
		exit(-1);
	}
	return q;
}

void queue_enqueue(Queue *q, QUEUE_TYPE c) {
	if (q -> start == (q -> end + 1) % (q -> size + 1)) {
		printf("Cannot insert any more elements into queue\n");
		exit(-1);
	}

	q -> elems[q -> end] = c;
	q -> end = (q -> end + 1) % (q -> size + 1);
}

QUEUE_TYPE queue_dequeue(Queue *q) {
	if (q -> start == q -> end) {
		printf("Cannot dequeue element since queue is empty\n");
		exit(-1);
	}

	QUEUE_TYPE ret = q -> elems[q -> start];
	q -> start = (q -> start + 1) % (q -> size + 1);
	return ret;
}

void destroy_queue(Queue *q) {
	free(q -> elems);
}

///////////////////////////////////////////////////////////////////////////////
// Processing PS2 Keyboard Inputs //
KeyReleased map_keycode_to_key(char make_code) {
	/* 	take advantage of the pattern that the two-byte break code of all keys 
		relevant to us are in the form of '<E0> F0 (MAKE_CODE)'
	*/
	switch (make_code)
	{
	case 0x5A:
		return ENTER;
	
	case 0x75:
		return UP;
	
	case 0x6B:
		return LEFT;

	case 0x72:
		return DOWN;
	
	case 0x74:
		return RIGHT;

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

void print_key(KeyReleased k) {
	switch (k)
	{
	case ENTER:
		printf("Enter");
		break;
	
	case UP:
		printf("Up");
		break;
	
	case LEFT:
		printf("Left");
		break;

	case DOWN:
		printf("Down");
		break;
	
	case RIGHT:
		printf("Right");
		break;
	
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

void print_key_released_queue(Queue q) {
	int i = q.start;

	while (i != q.end) {
		print_key(q.elems[i]);
		printf(" ");
		i = (i + 1) % (q.size + 1);
	}

	printf("\n");
}

char read_next_char() {
	// base code taken from http://www-ug.eecg.toronto.edu/msl/handouts/DE1-SoC_Computer_Nios.pdf 
	volatile int * PS2_ptr = (int *) 0xFF200100; // PS/2 port address
	int data_row, data_valid;
	char data_char = 0x00;
	
	while (1) {
		data_row = *(PS2_ptr); // read the Data register in the PS/2 port
		data_valid = data_row & 0x8000; // extract the data_valid field
		
		if (data_valid) {
			data_char = data_row & 0xFF;
			return data_char;
		}
	}
}

KeyReleased read_next_key() {
	while (1) {
		char c = read_next_char();
		if (c != 0xF0) continue;

		return map_keycode_to_key(read_next_char());
	}
}
///////////////////////////////////////////////////////////////////////////////
// Graphics Interface & I/O functions

KeyReleased get_choice(int num_options) {
	while (true) {
		KeyReleased k = read_next_key();
		if (k < num_options) {
			return k;
		}
	}
}

void print_options(int num_options, char** options) {
	for (int i = 0; i < num_options; i++) {
		printf(" [");
		print_key(i);
		printf("] %s ", options[i]);
	}
}

///////////////////////////////////////////////////////////////////////////////
// substitutes for graphics functions
void display_start_screen(int num_options, char** options) {
	printf("Showing title screen: ");
	print_options(num_options, options);
	printf("\n");
}

void option_select_box(char *question, int num_options, char **options, bool chance, bool community_chest) {
	printf("%s  ", question);
	printf("There are %d options: " , num_options);
	
	for (int i = 0; i < num_options; i++) {
		printf(" [");
		print_key(i);
		printf("] %s ", options[i]);
	}
	printf("\n");
	if (chance) printf("This is a chance card.\n");
	if (community_chest) printf("This is a community chest card.\n");
}

void display_player_turn(int player) {
	printf("It is player %d's turn\n", player + 1);
}

void display_player_cash(int player, int cash) {
	printf("Player %d has %d in cash\n", player, cash);
}

void init_graphics(int num_players) {
	printf("Displaying base board\n");

	printf("Players shown at start location:\n");
	for (int i = 0; i < num_players; i++) printf("Player %d\n", i + 1);

	display_player_turn(0);
	
	for (int i = 0; i < num_players; i++) display_player_cash(i, 1500);
}

void dice_roll(int num1, int num2) {
	printf("Your dice results are %d and %d\n", num1, num2);
}

void move_player(int from, int to, bool to_jail, int player) {
	printf("Player %d just moved from %d to %d\n", player, from, to);
	if (to_jail) printf("Player %d is now in jail\n", player);
}

void free_player_from_jail(int player) {
	printf("Player %d is now just visiting jail\n", player);
}

void remove_player_from_game(int from, int player) {
	printf("Player %d has been removed from %d\n", player, from);
}

///////////////////////////////////////////////////////////////////////////////
// interface impl
int show_title_menu_get_choice(int num_options, char** options) {
	display_start_screen(num_options, options);
	return get_choice(num_options);
}

int show_dialogue_get_choice(char *question, int num_options, char** options, bool chance, bool community_chest) {
	option_select_box(question, num_options, options, chance, community_chest);
	return get_choice(num_options);
}

void show_dice_roll_animation(diceRoll dr) {
	dice_roll(dr.die1, dr.die2);
}

void show_move_player(enum SquareNames from, enum SquareNames to, bool to_jail, player *p) {
	move_player(from, to, to_jail, p -> owner);
}

void show_player_removed_from_game(player *p) {
	remove_player_from_game(p -> position, p -> owner);
}


///////////////////////////////////////////////////////////////////////////////
// Demo //
int main(){
	// while(1) {
	// 	KeyReleased next_key = read_next_key();
	// 	print_key(next_key);
	// 	printf("\n");
	// }
	// Queue q = create_queue(5);
	// int cnt = 0;
	// while(cnt < 5) {
	// 	KeyReleased next_key = read_next_key();
	// 	if (next_key == NUM_KEYS) continue;

	// 	queue_enqueue(&q, next_key);
	// 	print_key_released_queue(q);
	// 	cnt += 1;
	// }

	// printf("\nNow pop the objects one by one:\n");

	// for (int i = 0; i < 5; i++) {
	// 	print_key(queue_dequeue(&q));
	// }

	///////////////////////////////////////////////////////////////////////////
	// Graphic interface testing

	// char* start_options[2] = {"Start", "Quit"};
	// KeyReleased k = show_title_menu_get_choice(
	// 	sizeof(start_options) / sizeof(start_options[0]),
	// 	start_options );
	// printf(!k ? "can begin\n" : "quit now\n\n");
	
	// char* ramen_options[3] = {"Yes", "No", "Maybe"};
	// k = show_dialogue_get_choice(	"Do you like ramen?", 
	// 								sizeof(ramen_options) / sizeof(ramen_options[0]), 
	// 								ramen_options, 
	// 								false, 
	// 								false );
	// printf("'%s' was chosen\n\n", ramen_options[k]);

	show_players_start();
	return 0;
}
