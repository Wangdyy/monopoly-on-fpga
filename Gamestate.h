/****************************************************************************************
 * Gamestate.h
 * This file contains the struct defininition of the Gamestate
*****************************************************************************************/

typedef struct gamestate{
    square* board[40];
    player* players[4];
    int player_count;
    int turn;
    int doubles;
    bool gameOver;
} gamestate;

typedef struct diceRoll{
    int die1;
    int die2;
    bool doubles;
} diceRoll;
