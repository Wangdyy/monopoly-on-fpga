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

void initGame(gamestate* game){
    /*Init board*/
    game->board[0] = square_Go;
    game->board[1] = square_MediterraneanAvenue;
    game->board[2] = square_CommunityChest1;
    game->board[3] = square_BalticAvenue;
    game->board[4] = square_IncomeTax;
    game->board[5] = square_ReadingRailRoad;
    game->board[6] = square_OrientalAvenue;
    game->board[7] = square_Chance1;
    game->board[8] = square_VermontAvenue;
    game->board[9] = square_ConnecticutAvenue;
    game->board[10] = square_JustVisiting;
    game->board[11] = square_StCharlesPlace;
    game->board[12] = square_ElectricCompany;
    game->board[13] = square_StatesAvenue;
    game->board[14] = square_VirginiaAvenue;
    game->board[15] = square_PennsylvaniaRailRoad;
    game->board[16] = square_StJamesPlace;
    game->board[17] = square_CommunityChest2;
    game->board[18] = square_TennesseeAvenue;
    game->board[19] = square_NewYorkAvenue;
    game->board[20] = square_FreeParking;
    game->board[21] = square_KentuckyAvenue;
    game->board[22] = square_Chance2;
    game->board[23] = square_IndianaAvenue;
    game->board[24] = square_IllinoisAvenue;
    game->board[25] = square_BAndO_RailRoad;
    game->board[26] = square_AtlanicAvenue;
    game->board[27] = square_VentnorAvenue;
    game->board[28] = square_WaterWorks;
    game->board[29] = square_MarvinGardens;
    game->board[30] = square_GoToJail;
    game->board[31] = square_PacificAvenue;
    game->board[32] = square_NorthCarolinaAvenue;
    game->board[33] = square_CommunityChest3;
    game->board[34] = square_PennsylvaniaAvenue;
    game->board[35] = square_ShortLine;
    game->board[36] = square_Chance3;
    game->board[37] = square_ParkPlace;
    game->board[38] = square_LuxuryTax;
    game->board[39] = square_Boardwalk;
    /*Init players*/
    for (int i = 0; i < MAX_PLAYERS; i++){
        game->players[i].owner = i;
        game->players[i].money = 1500;
        game->players[i].position = Go;
        game->players[i].jailTime = 0;
        game->players[i].inJail = false;
        game->players[i].bankrupt = false;
        game->players[i].owned_properties_count = 0;
    }
    game->player_count = 4;
    game->turn = 0;
    game->doubles = 0;
    game->gameOver = false;
    game->houses = 32;
    game->hotels = 12;
    game->lastDiceRoll = 0;
}

void gameStart(gamestate* game){
    //TODO: Roll dice to determine turn order
    //TODO: Ask for player names
    printf("Not implemented yet!\n");
}

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

/*Either: 
    1. Buy property if no one owns it
    2. Pay rent if someone else owns it
    3. Do nothing if they own it
*/
void doPropertySquare(player* player, square* square, gamestate* game){
    if (square->data.property.owner == Bank){
        printf("This property is unowned!\n");
        if (player->money >= square->data.property.price){
            printf("Would you like to buy %s for $%d? (y/n)\n", square->name, square->data.property.price);
            char input = 'n';
            scanf(" %c", &input);
            if (input == 'y'){
                buyProperty(player, square);
            } else {
                printf("You chose not to buy %s\n", square->name);
            }
        }
        else{
            printf("You don't have enough money to buy this property\n");
            //Not implemented: Auctioning
        }
    }
    else if (square->data.property.owner != player->owner){
        payRent(player, square, game);
    }
    else{
        printf("You own this property!\n");
    }
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
    enum Colors setColor = square->data.property.coloredPropety.color;
    bool setOwned = false;
    switch (setColor) {
        case (Brown):
            if (game->board[MediteraneanAvenue].data.property.owner == owner &&
                game->board[BalticAvenue].data.property.owner == owner) {
                setOwned = true;
            }
            break;
        case (LightBlue):
            if (game->board[OrientalAvenue].data.property.owner == owner &&
                game->board[VermontAvenue].data.property.owner == owner &&
                game->board[ConnecticutAvenue].data.property.owner == owner) {
                setOwned = true;
            }
            break;
        case (Pink):
            if (game->board[StCharlesPlace].data.property.owner == owner &&
                game->board[StatesAvenue].data.property.owner == owner &&
                game->board[VirginiaAvenue].data.property.owner == owner) {
                setOwned = true;
            }
            break;
        case (Orange):
            if (game->board[StJamesPlace].data.property.owner == owner &&
                game->board[TennesseeAvenue].data.property.owner == owner &&
                game->board[NewYorkAvenue].data.property.owner == owner) {
                setOwned = true;
            }
            break;
        case (Red):
            if (game->board[KentuckyAvenue].data.property.owner == owner &&
                game->board[IndianaAvenue].data.property.owner == owner &&
                game->board[IllinoisAvenue].data.property.owner == owner) {
                setOwned = true;
            }
            break;
        case (Yellow):
            if (game->board[AtlanticAvenue].data.property.owner == owner &&
                game->board[VentnorAvenue].data.property.owner == owner &&
                game->board[MarvinGardens].data.property.owner == owner) {
                setOwned = true;
            }
            break;
        case (Green):
            if (game->board[PacificAvenue].data.property.owner == owner &&
                game->board[NorthCarolinaAvenue].data.property.owner == owner &&
                game->board[PennsylvaniaAvenue].data.property.owner == owner) {
                setOwned = true;
            }
            break;
        case (DarkBlue):
            if (game->board[ParkPlace].data.property.owner == owner &&
                game->board[Boardwalk].data.property.owner == owner) {
                setOwned = true;
            }
            break;
        default:
            printf("Error: Color not recognized\n");
            break;
    }
    if (setOwned) {
        printf("Player %d owns the set, rent is doubled!\n", OWNER_TO_PLAYER(owner));
        rent *= 2;
    }
    printf("Paying player %d $%d rent...\n", OWNER_TO_PLAYER(owner), rent);
    payPlayer(player, &game->players[owner], rent);
}

void payUtilityRent(player* player, square* square, gamestate* game){
    enum Owners utilityOwner = square->data.property.owner;
    enum Owners otherUtilityOwner;
    if (square->squareName == ElectricCompany) {
        otherUtilityOwner = game->board[WaterWorks].data.property.owner;
    } else if (square->squareName == WaterWorks) {
        otherUtilityOwner = game->board[ElectricCompany].data.property.owner;
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

void buyProperty(player* player, square* square){
    if (player->money < square->data.property.price) {
        printf("Error: Player %d does not have enough money to buy %s!\n", OWNER_TO_PLAYER(player->owner), square->name);
        return;
    }
    player->money -= square->data.property.price;
    square->data.property.owner = player->owner;
    printf("Player %d bought %s for $%d", OWNER_TO_PLAYER(player->owner), square->name, square->data.property.price);
    player->owned_properties[player->owned_properties_count] = square;
    player->owned_properties_count++;
}

void sellProperty(player* player, square* square){
    if (square->data.property.owner != player->owner) {
        printf("Error: Player %d does not own %s!\n", OWNER_TO_PLAYER(player->owner), square->name);
        return;
    }
    player->money += square->data.property.price;
    square->data.property.owner = Bank;
    printf("Player %d sold %s for $%d", OWNER_TO_PLAYER(player->owner), square->name, square->data.property.price);
    bool found = false;
    for (int i = 0; i < player->owned_properties_count; i++) {
        if (player->owned_properties[i] == square) {
            player->owned_properties[i] = NULL;
            found = true;
        }
        if (found && i < player->owned_properties_count - 1) {
            player->owned_properties[i] = player->owned_properties[i + 1];
        }
    }
    player->owned_properties_count--;
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
    //Selling to other players no implemented
    printf("Not implemented yet!\n");
    return false;
}

/**************************************
 * Main
 **************************************/
int main (void){
    printf("Welcome to Monopoly!\n");
    gamestate game;
    initGame(&game);
    gameStart(&game);
    return 0;
}