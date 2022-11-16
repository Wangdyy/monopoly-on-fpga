#pragma once
#include "Squares.h"
#include "Players.h"
#include "Gamestate.h"
/*Function decl*/

/**************************************
 * Game related
 **************************************/
void initGame(gamestate *game);

void gameStart(gamestate *game);

/*Return True if game should end*/
bool checkForGameOver(gamestate *game);

diceRoll rollDice(gamestate *game);

void playerTurn(player *player, gamestate *game);

/*Turn end returns true if game ends*/
bool turnEnd(gamestate *game);

void moveToSquare(player *player, struct diceRoll diceRoll, gamestate *game);

void landOnSquare(player *player, square *square, gamestate *game);

void doActionSquare(player *player, square *square, gamestate *game);

void doPropertySquare(player *player, square *square, gamestate *game);

/**************************************
 * Action Squares
 **************************************/
void payIncomeTax(player *player);

void payLuxuryTax(player *player);

void goToJail(player *player);

/**************************************
 * Property Squares
 **************************************/
void payRent(player *player, square *square, gamestate *game);

void payColorSetRent(player *player, square *square, gamestate *game);

void payUtilityRent(player *player, square *square, gamestate *game);

void payRailroadRent(player *player, square *square, gamestate *game);

void buyProperty(player *player, square *square);

void sellProperty(player *player, square *square);

/**************************************
 * Payment
 **************************************/
void payPlayer(player *payer, player *payee, int amount);

/*Returns how much money was actually paid, useful in checking how much
rent was actually paid, also bankrupts them if they can't sell assets*/
int payMoney(player *player, int amount);

void receiveMoney(player *player, int amount);

/*Returns true if after selling assets the player can pay the amount, false otherwise */
bool sellAssets(player *player, int amount);

/**************************************
 * Player in jail
 **************************************/
void playerInJail(player *player, gamestate *game);

/*Called when player forced to pay jail fine, if they can't, they go bankrupt*/
bool payJailFine(player *player);

/**************************************
 * Miscellaneous
 **************************************/
void passGo(player *player);

void bankruptPlayer(player *player);

void waitForNextTurn();

// void buyHouse(player* player, propertySquare* property);

// void sellHouse(player* player, propertySquare* property);

// void buyHotel(player* player, propertySquare* property);

// void sellHotel(player* player, propertySquare* property);

// void mortgageProperty(player* player, propertySquare* property);

// void unmortgageProperty(player* player, propertySquare* property);

// void tradeProperty(player* player, propertySquare* property);

// void communityChest(player* player);

// void chance(player* player);