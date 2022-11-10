/****************************************************************************************
 * Gamestate.h
 * This file contains the struct defininition of the Gamestate
*****************************************************************************************/
#pragma once
#include "Squares.h"
#include "Players.h"

typedef struct gamestate{
    square* board[40];
    player* players[4];
    int player_count;
    int turn;
    int doubles;
    bool gameOver;
    int houses;
    int hotels;
    /*Current this is only used for paying utility rent*/
    int lastDiceRoll;
} gamestate;

typedef struct diceRoll{
    int die1;
    int die2;
    bool doubles;
} diceRoll;
