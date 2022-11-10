//320*240
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

#include "Squares.h"
#include "Players.h"
#include "Gamestate.h"
#include "helper_functions.h"

/*Function defs*/

/**************************************
 * Game related
 **************************************/
bool checkForGameOver(gamestate* game){
    if (game->player_count == 1){
        printf("Game Over!\n");
        return true;
    }
    return false;
}

struct diceRoll rollDice(){
    struct diceRoll roll;
    roll.die1 = rand() % 6 + 1;
    roll.die2 = rand() % 6 + 1;
    if (roll.die1 == roll.die2){
        roll.doubles = true;
    }
    else{
        roll.doubles = false;
    }
    return roll;
}

void moveToSquare(player* player, struct diceRoll diceRoll, gamestate* game){
    printf("Not implemented yet!\n");
}

void landOnSquare(player* player, square* square, gamestate* game){
    printf("%s landed on %s\n", player->name, square->name);
    if (square->type == Property) {
        doPropertySquare(player, square, game);
    }
    else if (square->type == Action) {
        doActionSquare(player, square, game);
    } else {
        printf("Error: Square type not recognized\n");
    }
}

void doActionSquare(player* player, square* square, gamestate* game){
    switch (square->data.action) {
        case (GoToJailAction):
            goToJail(player);
            break;
        case (IncomeTaxAction):
            payIncomeTax(player);
            break;
        case (LuxuryTaxAction):
            payLuxuryTax(player);
            break;
        case (ChanceAction):
            printf("Not implemented yet!\n");
            break;
        case (CommunityChestAction):
            printf("Not implemented yet!\n");
            break;
        case (GoAction):
            printf("You've passed go!\n");
            break;
        case (FreeParkingAction):
            printf("Nothing happens...\n");
            break;
        case (JailAction):
            printf("Just visiting...nothing happens\n");
            break;
        default:
            printf("Error: Action Square type not recognized\n");
            break;
    }
}

void doPropertySquare(player* player, square* square, gamestate* game){
    /*Either: 
    1. Buy property if no one owns it
    2. Pay rent if someone else owns it
    3. Do nothing if they own it*/
    printf("Not implemented yet!\n");
}

/**************************************
 * Action Squares
 **************************************/
void payIncomeTax(player* player){
    /*Players should get to decide whether to pay 200 or 10% of net worth
    but for now, we will only implement paying 200*/
    printf("Paying $200 income tax...\n");
    payMoney(player, 200);
}

void payLuxuryTax(player* player){
    printf("Paying $100 luxury tax...\n");
    payMoney(player, 100);
}

void goToJail(player* player){
    printf("Going to jail...\n");
    player->position = JustVisiting;
    player->inJail = true;
}

/**************************************
 * Property Squares
 **************************************/
void payRent(player* player, propertySquare* property, gamestate* game){
    switch(property->type){
        case (Colored):
            payColorSetRent(player, property);
            break;
        case (Utility):
            payUtilityRent(player, property);
            break;
        case (RailRoad):
            payRailroadRent(player, property);
            break;
        default:
            printf("Error: Property type not recognized\n");
            break;
    }
}

void payColorSetRent(player* player, propertySquare* property, gamestate* game){
    printf("Not implemented yet!\n");
}

void payUtilityRent(player* player, propertySquare* property, gamestate* game){
    enum utility Owner = property->owner;
}

void payRailroadRent(player* player, propertySquare* propert, gamestate* game){
    printf("Not implemented yet!\n");
}

void buyProperty(player* player, propertySquare* property){
    printf("Not implemented yet!\n");
}

void sellProperty(player* player, propertySquare* property){
    printf("Not implemented yet!\n");
}

/**************************************
 * Payment
 **************************************/
int payMoney(player* player, int amount){
    if (player->money < amount){
        printf("You don't have enough money to pay!\n");
        if (sellAssets(player, amount)){
            printf("You sold enough assets to pay!\n");
            player->money -= amount;
            printf("Player %d paid $%d", player->owner + 1, amount);
            return amount;
        }
        else{
            printf("You don't have enough money to pay!\n");
            amount = player->money;
            player->money = 0;
            printf("Player %d paid $%d", player->owner + 1, amount);
            return amount;
        }
    } else {
        player->money -= amount;
        printf("Player %d paid $%d", player->owner + 1, amount);
        return amount;
    }
}

void receiveMoney(player* player, int amount){
    player->money += amount;
    printf("Player %d received $%d", player->owner + 1, amount);
}

bool sellAssets(player* player, int amount){
    printf("Not implemented yet!\n");
    return false;
}



/**************************************
 * Main
 **************************************/
int main (void){
    printf("Welcome to Monopoly!\n");
    return 0;
}