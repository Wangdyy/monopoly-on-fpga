/****************************************************************************************
 * Gamestate.h
 * This file contains the struct defininition of the Gamestate
 *****************************************************************************************/
#pragma once
#include "Squares.h"
#include "Players.h"

#define MAX_PLAYERS 4
#define MAX_SQUARES 40

typedef struct gamestate
{
    square board[40];
    player players[4];
    int turn;
    /*Doubles not implemented, does not lead to extra turn*/
    int doubles;
    /*Houses and hotels not implemented*/
    int houses;
    int hotels;
    /*Current this is only used for paying utility rent*/
    int lastDiceRoll;
} gamestate;

typedef struct diceRoll
{
    int die1;
    int die2;
    bool doubles;
} diceRoll;
