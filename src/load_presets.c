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
