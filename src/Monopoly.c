//320*240
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>

#include "Squares.h"
#include "Players.h"
#include "Gamestate.h"
#include "helper_functions.h"

#define OWNER_TO_PLAYER(player) (player + 1)

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
    printf("player %d landed on %s\n", OWNER_TO_PLAYER(player->owner), square->name);
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
void payRent(player* player, square* square, gamestate* game){
    switch(square->data.property.type){
        case (Colored):
            payColorSetRent(player, square, game);
            break;
        case (Utility):
            payUtilityRent(player, square, game);
            break;
        case (RailRoad):
            payRailroadRent(player, square, game);
            break;
        default:
            printf("Error: Property type not recognized\n");
            break;
    }
}

void payColorSetRent(player* player, square* square, gamestate* game){
    enum Owners owner = square->data.property.owner;
    int rent = square->data.property.coloredPropety.rent[0];
}

void payUtilityRent(player* player, square* square, gamestate* game){
    enum Owners utilityOwner = square->data.property.owner;
    enum Owners otherUtilityOwner;
    if (square->squareName == ElectricCompany) {
        enum Owners otherUtilityOwner = game->board[WaterWorks].data.property.owner;
    } else if (square->squareName == WaterWorks) {
        enum Owners otherUtilityOwner = game->board[ElectricCompany].data.property.owner;
    } else {
        printf("Error: Utility square not recognized\n");
        return;
    }
    int rent;
    if (utilityOwner == otherUtilityOwner) {
            printf("Both utilities owned by player %d!\n", OWNER_TO_PLAYER(utilityOwner));
            rent = 10 * game->lastDiceRoll;
    } else {
            printf("Utility owned by player %d!\n", OWNER_TO_PLAYER(utilityOwner));
            rent = 4 * game->lastDiceRoll;
    }
    printf("Paying player %d $%d rent...\n", OWNER_TO_PLAYER(utilityOwner), rent);
    payPlayer(player, &game->players[utilityOwner], rent);
}

void payRailroadRent(player* player, square* square, gamestate* game){
    enum Owners railroadOwner = square->data.property.owner;
    int railRoadsOwned = 0;
    if (game->board[ReadingRailRoad].data.property.owner == railroadOwner) {
        railRoadsOwned++;
    }
    if (game->board[PennsylvaniaRailRoad].data.property.owner == railroadOwner) {
        railRoadsOwned++;
    }
    if (game->board[BAndORailRoad].data.property.owner == railroadOwner) {
        railRoadsOwned++;
    }
    if (game->board[ShortLine].data.property.owner == railroadOwner) {
        railRoadsOwned++;
    }
    int rent;
    switch (railRoadsOwned) {
        case (1):
            rent = 25;
            break;
        case (2):
            rent = 50;
            break;
        case (3):
            rent = 100;
            break;
        case (4):
            rent = 200;
            break;
        default:
            printf("Error: Wrong Number of railroads owned\n");
            break;
    }
    printf("Paying player %d $%d rent...\n", OWNER_TO_PLAYER(railroadOwner), rent);
    payPlayer(player, &game->players[railroadOwner], rent);
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
void payPlayer(player* payer, player* payee, int amount){
    printf("Player %d is paying player %d $%d\n", OWNER_TO_PLAYER(payer->owner), OWNER_TO_PLAYER(payee->owner), amount);
    int moneyPaid = payMoney(payer, amount);
    receiveMoney(payee, moneyPaid);
}

int payMoney(player* player, int amount){
    if (player->money < amount){
        printf("You don't have enough money to pay!\n");
        if (sellAssets(player, amount)){
            printf("You sold enough assets to pay!\n");
        }
        else{
            printf("You don't have enough money to pay!\n");
            amount = player->money;
            player->money = 0;
            player->bankrupt = true;
            printf("Player %d paid $%d", OWNER_TO_PLAYER(player->owner), amount);
            printf("Player %d is bankrupt!\n", OWNER_TO_PLAYER(player->owner));
            return amount;
        }
    }
    player->money -= amount;
    printf("Player %d paid $%d", OWNER_TO_PLAYER(player->owner), amount);
    return amount;
}

void receiveMoney(player* player, int amount){
    player->money += amount;
    printf("Player %d received $%d", OWNER_TO_PLAYER(player->owner), amount);
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