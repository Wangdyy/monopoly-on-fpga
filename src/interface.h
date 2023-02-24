#pragma once

#include "gamestate.h"
#include "squares.h"
#include "players.h"
#include "stdbool.h"

void drawseq_turn_start(int curr_player, gamestate *game);

int drawseq_dialogue_get_choice(int curr_player,
                                gamestate *game,
                                char *question,
                                int num_options,
                                char **options,
                                bool chance,
                                bool community_chest);

void drawseq_normal_confirm(int curr_player, gamestate *game, char *question);

bool drawseq_dialogue_yes_no(int curr_player, gamestate *game, char *question);

void drawseq_roll_dice(int curr_player, gamestate *game, diceRoll dice_roll);

void drawseq_move_player(int curr_player, gamestate *game, diceRoll dice_roll, int old_pos, int new_pos);

int drawseq_choose_owned_property(int curr_player, gamestate *game, int num_choices, int *choices);
void draw_basic_setup(int curr_player, gamestate *game);