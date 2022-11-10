#pragma once
#include "Squares.h"
#include "Players.h"
#include "Gamestate.h"
/*Function decl*/

/**************************************
 * Game related
 **************************************/
void gameStart(gamestate* game);

bool checkForGameOver(gamestate* game);

struct diceRoll rollDice();

void moveToSquare(player* player, struct diceRoll diceRoll, gamestate* game);

void landOnSquare(player* player, square* square, gamestate* game);

void doActionSquare(player* player, square* square, gamestate* game);

void doPropertySquare(player* player, square* square, gamestate* game);

/**************************************
 * Action Squares
 **************************************/
void payIncomeTax(player* player);

void payLuxuryTax(player* player);

void goToJail(player* player);


/**************************************
 * Property Squares
 **************************************/
void payRent(player* player, square* square, gamestate* game);

void payColorSetRent(player* player, square* square, gamestate* game);

void payUtilityRent(player* player, square* square, gamestate* game);

void payRailroadRent(player* player, square* square, gamestate* game);

void buyProperty(player* player, propertySquare* property);

void sellProperty(player* player, propertySquare* property);

/**************************************
 * Payment
 **************************************/
void payPlayer(player* payer, player* payee, int amount);

/*Returns how much money was actually paid, useful in checking how much
rent was actually paid, also bankrupts them if they can't sell assets*/
int payMoney(player* player, int amount);

void receiveMoney(player* player, int amount);

/*Returns true if after selling assets the player can pay the amount, false otherwise */
bool sellAssets(player* player, int amount);

/**************************************
 * Miscellaneous
 **************************************/
void payJailFine(player* player);


// void buyHouse(player* player, propertySquare* property);

// void sellHouse(player* player, propertySquare* property);

// void buyHotel(player* player, propertySquare* property);

// void sellHotel(player* player, propertySquare* property);

// void mortgageProperty(player* player, propertySquare* property);

// void unmortgageProperty(player* player, propertySquare* property);
