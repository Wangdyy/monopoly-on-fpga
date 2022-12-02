/****************************************************************************************
 * Players.h
 * This file contains the struct defininition of the all players
 *****************************************************************************************/
#pragma once
#include "Squares.h"

typedef struct player
{
    char name[20]; /*Not implementing name yet, just called players 1-4*/
    enum Owners owner;
    int money;
    enum SquareNames position;
    int jailTime;
    bool inJail;
    bool bankrupt;
    square *owned_properties[28];
    int owned_properties_count;
} player;