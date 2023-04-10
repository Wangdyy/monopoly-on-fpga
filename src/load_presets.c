#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "stdbool.h"
#include "squares.h"
#include "players.h"
#include "gamestate.h"
#include "helpers.h"
#include "presets.h"

void everyThingOwnedByPlayer0(gamestate *game)
{
    for (int i = 0; i < MAX_SQUARES; i++)
    {
        if (game->board[i].type == Property)
        {
            game->board[i].data.property.owner = Player1;
        }
    }
}

void midGame(gamestate *game)
{
    ;
}

void endGame(gamestate *game)
{
    game->players[1].money = 50;
    game->players[2].money = 50;
    game->players[3].money = 50;
    for (int i = 0; i < MAX_SQUARES; i++)
    {
        if (game->board[i].type == Property)
        {
            if (game->board[i].data.property.type == Colored)
            {
                game->board[i].data.property.owner = Player1;
                game->board[i].data.property.coloredProperty.houseCount = 3;
            }
            else if (game->board[i].data.property.type == RailRoad)
                game->board[i]
                    .data.property.owner = Player2;
            else if (game->board[i].data.property.type == Utility)
                game->board[i]
                    .data.property.owner = Player3;
        }
    }
    game->board[ParkPlace].data.property.owner = Player4;
    game->board[Boardwalk].data.property.owner = Player4;
    game->board[ParkPlace].data.property.coloredProperty.houseCount = 4;
    game->board[ParkPlace].data.property.coloredProperty.hotelCount = 1;
    game->board[Boardwalk].data.property.coloredProperty.houseCount = 4;
    game->board[Boardwalk].data.property.coloredProperty.hotelCount = 1;
}
