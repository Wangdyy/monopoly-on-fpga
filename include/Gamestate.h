/****************************************************************************************
 * Gamestate.h
 * This file contains the struct defininition of the Gamestate
*****************************************************************************************/
#pragma once
#include "Squares.h"
#include "Players.h"

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
