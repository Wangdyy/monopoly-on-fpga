#pragma once

#include "Gamestate.h"
#include "Squares.h"
#include "Players.h"
#include "stdbool.h"

void drawseq_turn_start(int curr_player, gamestate *game);

void drawseq_board_frame(gamestate *game);

int drawseq_dialogue_get_choice(int curr_player,
                                gamestate *game,
                                char *question,
                                int num_options,
                                char **options,
                                bool chance,
                                bool community_chest);

void drawseq_normal_confirm(int curr_player, gamestate *game, char *question);

bool drawseq_dialogue_yes_no(int curr_player, gamestate *game, char *question);

int drawseq_mortgage_property(player *curr_player_struct, gamestate *game);

void drawseq_roll_dice(int curr_player, gamestate *game, diceRoll dice_roll);

void drawseq_move_player(int curr_player, gamestate *game, diceRoll dice_roll);