/****************************************************************************************
 * Players.h
 * This file contains the struct defininition of the all players
*****************************************************************************************/


typedef struct player{
    char name[20];
    int money;
    int position;
    int jailTime;
    bool inJail;
    bool bankrupt;
    propertySquare* owned_properties[28];
    int owned_properties_count;
} player;