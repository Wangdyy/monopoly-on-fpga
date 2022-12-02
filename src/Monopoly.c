// 320*240
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "Squares.h"
#include "Players.h"
#include "Gamestate.h"
#include "helper_functions.h"
#include "monopoly_graphics.c"
#include "key_released.c"

#define OWNER_TO_PLAYER(player) (player + 1)

/*Function defs*/

/**************************************
 * Game related
 **************************************/

void initGame(gamestate *game)
{
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
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        game->players[i].owner = i;
        game->players[i].money = 1500;
        game->players[i].position = Go;
        game->players[i].jailTime = 0;
        game->players[i].inJail = false;
        game->players[i].bankrupt = false;
        game->players[i].owned_properties_count = 0;
    }
    game->turn = 0;
    game->doubles = 0;
    game->houses = 32;
    game->hotels = 12;
    game->lastDiceRoll = 0;
}

void gameStart(gamestate *game)
{
    // TODO: Roll dice to determine turn order
    // TODO: Ask for player names
    printf("Not implemented yet!\n");
}

bool checkForGameOver(gamestate *game)
{
    int playersLeft = 0;
    int winningPlayer = -1;

    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        if (!game->players[i].bankrupt)
        {
            playersLeft++;
            winningPlayer = i + 1;
        }
    }

    if (playersLeft > 1)
    {
        return false;
    }
    else
    {
        printf("Game Over! The winner is player %d.\n", winningPlayer);

        char winStmt[128];
        sprintf(winStmt, "Game Over! The winner is player %d.", winningPlayer);
        drawseq_normal_confirm(winningPlayer, game, winStmt);

        return true;
    }
}

diceRoll rollDice(gamestate *game)
{
    diceRoll roll;
    roll.die1 = rand() % 6 + 1;
    roll.die2 = rand() % 6 + 1;
    if (roll.die1 == roll.die2)
    {
        roll.doubles = true;
    }
    else
    {
        roll.doubles = false;
    }
    printf("You rolled a %d and a %d\n", roll.die1, roll.die2);
    game->lastDiceRoll = roll.die1 + roll.die2;
    if (roll.doubles)
    {
        game->doubles++;
    }
    return roll;
}

void playerTurn(player *player, gamestate *game)
{
    if (player->bankrupt)
    {
        return;
    }
    printf("/**************************************\n");
    printf("It is player %d's turn!\n", OWNER_TO_PLAYER(game->players[game->turn].owner));
    printf("You are currently located at %s\n", game->board[player->position].name);
    printf("You currently have $%d\n", player->money);
    printf("**************************************/\n");

    drawseq_turn_start(OWNER_TO_PLAYER(player->owner), game);

    if (player->inJail)
    {
        playerInJail(player, game);
    }
    else
    {
        drawseq_normal_confirm(OWNER_TO_PLAYER(player->owner), game, "Roll dice to move.");
        diceRoll roll = rollDice(game);
        drawseq_roll_dice(OWNER_TO_PLAYER(player->owner), game, roll);

        moveToSquare(player, roll, game);
    }
}

/*Turn end returns true if game ends*/
bool turnEnd(gamestate *game)
{
    game->turn = (game->turn + 1) % MAX_PLAYERS;
    game->doubles = 0;
    return checkForGameOver(game);
}

void moveToSquare(player *player, struct diceRoll roll, gamestate *game)
{
    int diceTotal = roll.die1 + roll.die2;
    int newPositionRaw = player->position + diceTotal;

    // this function call changes position of player
    drawseq_move_player(OWNER_TO_PLAYER(player->owner), game, diceTotal);

    if (newPositionRaw >= MAX_SQUARES)
    {
        passGo(player, game);
    }

    landOnSquare(player, &game->board[player->position], game);
}

void landOnSquare(player *player, square *square, gamestate *game)
{
    printf("player %d landed on %s\n", OWNER_TO_PLAYER(player->owner), square->name);
    if (square->type == Property)
    {
        doPropertySquare(player, square, game);
    }
    else if (square->type == Action)
    {
        doActionSquare(player, square, game);
    }
    else
    {
        printf("Error: Square type not recognized\n");
    }
}

void doActionSquare(player *player, square *square, gamestate *game)
{
    switch (square->data.action)
    {
    case (GoToJailAction):
        goToJail(player, game);
        break;
    case (IncomeTaxAction):
        payIncomeTax(player, game);
        break;
    case (LuxuryTaxAction):
        payLuxuryTax(player, game);
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
void doPropertySquare(player *player, square *square, gamestate *game)
{
    if (square->data.property.owner == Bank)
    {
        printf("This property is unowned!\n");
        if (player->money >= square->data.property.price)
        {
            char query[256];
            sprintf(query,
                    "%s is unowned. Would you like to buy it for $%d?",
                    square->name,
                    square->data.property.price);

            if (drawseq_dialogue_yes_no(OWNER_TO_PLAYER(player->owner), game, query))
            {
                printf("You chose to buy the property.\n");
                buyProperty(player, square, game);
            }
            else
            {
                printf("You did not buy the property.\n");
            }
        }
        else
        {
            char query[256];
            sprintf(query,
                    "You don't have enough money to buy %s (need %d).\n",
                    square->name,
                    square->data.property.price);

            drawseq_normal_confirm(OWNER_TO_PLAYER(player->owner),
                                   game,
                                   query);

            printf("You don't have enough money to buy this property\n");
            // Not implemented: Auctioning
        }
    }
    else if (square->data.property.owner != player->owner)
    {
        payRent(player, square, game);
    }
    else
    {
        printf("You own this property!\n");
    }
}

/**************************************
 * Action Squares
 **************************************/
void payIncomeTax(player *player, gamestate *game)
{
    /*Players should get to decide whether to pay 200 or 10% of net worth
    but for now, we will only implement paying 200*/
    printf("Paying $200 income tax...\n");
    drawseq_normal_confirm(OWNER_TO_PLAYER(player->owner),
                           game,
                           "You must pay $200 income tax.");

    payMoney(player, 200, game);
}

void payLuxuryTax(player *player, gamestate *game)
{
    printf("Paying $100 luxury tax...\n");
    drawseq_normal_confirm(OWNER_TO_PLAYER(player->owner),
                           game,
                           "You must pay $200 luxury tax.");

    payMoney(player, 100, game);
}

void goToJail(player *player, gamestate *game)
{
    printf("Going to jail...\n");
    player->position = JustVisiting;
    player->inJail = true;
}

/**************************************
 * Property Squares
 **************************************/
void payRent(player *player, square *square, gamestate *game)
{
    switch (square->data.property.type)
    {
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

void payColorSetRent(player *player, square *square, gamestate *game)
{
    enum Owners owner = square->data.property.owner;
    int rent = square->data.property.coloredPropety.rent[0];
    enum Colors setColor = square->data.property.coloredPropety.color;
    bool setOwned = false;
    switch (setColor)
    {
    case (Brown):
        if (game->board[MediteraneanAvenue].data.property.owner == owner &&
            game->board[BalticAvenue].data.property.owner == owner)
        {
            setOwned = true;
        }
        break;
    case (LightBlue):
        if (game->board[OrientalAvenue].data.property.owner == owner &&
            game->board[VermontAvenue].data.property.owner == owner &&
            game->board[ConnecticutAvenue].data.property.owner == owner)
        {
            setOwned = true;
        }
        break;
    case (Pink):
        if (game->board[StCharlesPlace].data.property.owner == owner &&
            game->board[StatesAvenue].data.property.owner == owner &&
            game->board[VirginiaAvenue].data.property.owner == owner)
        {
            setOwned = true;
        }
        break;
    case (Orange):
        if (game->board[StJamesPlace].data.property.owner == owner &&
            game->board[TennesseeAvenue].data.property.owner == owner &&
            game->board[NewYorkAvenue].data.property.owner == owner)
        {
            setOwned = true;
        }
        break;
    case (Red):
        if (game->board[KentuckyAvenue].data.property.owner == owner &&
            game->board[IndianaAvenue].data.property.owner == owner &&
            game->board[IllinoisAvenue].data.property.owner == owner)
        {
            setOwned = true;
        }
        break;
    case (Yellow):
        if (game->board[AtlanticAvenue].data.property.owner == owner &&
            game->board[VentnorAvenue].data.property.owner == owner &&
            game->board[MarvinGardens].data.property.owner == owner)
        {
            setOwned = true;
        }
        break;
    case (Green):
        if (game->board[PacificAvenue].data.property.owner == owner &&
            game->board[NorthCarolinaAvenue].data.property.owner == owner &&
            game->board[PennsylvaniaAvenue].data.property.owner == owner)
        {
            setOwned = true;
        }
        break;
    case (DarkBlue):
        if (game->board[ParkPlace].data.property.owner == owner &&
            game->board[Boardwalk].data.property.owner == owner)
        {
            setOwned = true;
        }
        break;
    default:
        printf("Error: Color not recognized\n");
        break;
    }
    if (setOwned)
    {
        printf("Player %d owns the set, rent is doubled!\n", OWNER_TO_PLAYER(owner));
        rent *= 2;
    }

    char payConfirm[256];
    sprintf(payConfirm,
            "You landed on %s, which is owned by player %d. You must pay them $%d.",
            square->name,
            OWNER_TO_PLAYER(owner),
            rent);
    drawseq_normal_confirm(OWNER_TO_PLAYER(player->owner), game, payConfirm);

    printf("Paying player %d $%d rent...\n", OWNER_TO_PLAYER(owner), rent);
    payPlayer(player, &game->players[owner], rent, game);
}

void payUtilityRent(player *player, square *square, gamestate *game)
{
    enum Owners utilityOwner = square->data.property.owner;
    enum Owners otherUtilityOwner;
    if (square->squareName == ElectricCompany)
    {
        otherUtilityOwner = game->board[WaterWorks].data.property.owner;
    }
    else if (square->squareName == WaterWorks)
    {
        otherUtilityOwner = game->board[ElectricCompany].data.property.owner;
    }
    else
    {
        printf("Error: Utility square not recognized\n");
        return;
    }
    int rent;
    if (utilityOwner == otherUtilityOwner)
    {
        printf("Both utilities owned by player %d!\n", OWNER_TO_PLAYER(utilityOwner));
        rent = 10 * game->lastDiceRoll;
    }
    else
    {
        printf("Utility owned by player %d!\n", OWNER_TO_PLAYER(utilityOwner));
        rent = 4 * game->lastDiceRoll;
    }

    char payConfirm[256];
    sprintf(payConfirm,
            "You landed on %s, which is owned by player %d. You must pay them $%d.",
            square->name,
            OWNER_TO_PLAYER(utilityOwner),
            rent);
    drawseq_normal_confirm(OWNER_TO_PLAYER(player->owner), game, payConfirm);

    printf("Paying player %d $%d rent...\n", OWNER_TO_PLAYER(utilityOwner), rent);
    payPlayer(player, &game->players[utilityOwner], rent, game);
}

void payRailroadRent(player *player, square *square, gamestate *game)
{
    enum Owners railroadOwner = square->data.property.owner;
    int railRoadsOwned = 0;
    if (game->board[ReadingRailRoad].data.property.owner == railroadOwner)
    {
        railRoadsOwned++;
    }
    if (game->board[PennsylvaniaRailRoad].data.property.owner == railroadOwner)
    {
        railRoadsOwned++;
    }
    if (game->board[BAndORailRoad].data.property.owner == railroadOwner)
    {
        railRoadsOwned++;
    }
    if (game->board[ShortLine].data.property.owner == railroadOwner)
    {
        railRoadsOwned++;
    }
    int rent;
    switch (railRoadsOwned)
    {
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

    char payConfirm[256];
    sprintf(payConfirm,
            "You landed on %s, which is owned by player %d. You must pay them $%d.",
            square->name,
            OWNER_TO_PLAYER(railroadOwner),
            rent);
    drawseq_normal_confirm(OWNER_TO_PLAYER(player->owner), game, payConfirm);

    printf("Paying player %d $%d rent...\n", OWNER_TO_PLAYER(railroadOwner), rent);
    payPlayer(player, &game->players[railroadOwner], rent, game);
}

void buyProperty(player *player, square *square, gamestate *game)
{
    if (player->money < square->data.property.price)
    {
        char message[256];
        sprintf(message, "You do not have enough money to buy %s.\n", square->name);
        drawseq_normal_confirm(OWNER_TO_PLAYER(player->owner),
                               game,
                               message);

        printf("Error: Player %d does not have enough money to buy %s!\n", OWNER_TO_PLAYER(player->owner), square->name);
        return;
    }
    player->money -= square->data.property.price;
    square->data.property.owner = player->owner;
    player->owned_properties[player->owned_properties_count] = square;
    player->owned_properties_count++;

    char message[256];
    sprintf(message, "Player %d successfully bought %s for $%d.",
            OWNER_TO_PLAYER(player->owner),
            square->name,
            square->data.property.price);

    drawseq_normal_confirm(OWNER_TO_PLAYER(player->owner),
                           game,
                           message);

    printf("Player %d bought %s for $%d\n", OWNER_TO_PLAYER(player->owner), square->name, square->data.property.price);
}

void sellProperty(player *player, square *square, gamestate *game)
{
    if (square->data.property.owner != player->owner)
    {
        char message[256];
        sprintf(message, "You do not own %s and cannot sell it.\n", square->name);
        drawseq_normal_confirm(OWNER_TO_PLAYER(player->owner),
                               game,
                               message);

        printf("Error: Player %d does not own %s!\n", OWNER_TO_PLAYER(player->owner), square->name);
        return;
    }

    player->money += square->data.property.price;
    square->data.property.owner = Bank;
    printf("Player %d sold %s for $%d\n", OWNER_TO_PLAYER(player->owner), square->name, square->data.property.price);

    char message[256];
    sprintf(message, "You sold %s for $%d.", square->name, square->data.property.price);
    drawseq_normal_confirm(OWNER_TO_PLAYER(player->owner),
                           game,
                           message);

    bool found = false;
    for (int i = 0; i < player->owned_properties_count; i++)
    {
        if (player->owned_properties[i] == square)
        {
            player->owned_properties[i] = NULL;
            found = true;
        }
        if (found && i < player->owned_properties_count - 1)
        {
            player->owned_properties[i] = player->owned_properties[i + 1];
        }
    }
    player->owned_properties_count--;
}

/**************************************
 * Payment
 **************************************/
void payPlayer(player *payer, player *payee, int amount, gamestate *game)
{
    printf("Player %d is paying player %d $%d\n", OWNER_TO_PLAYER(payer->owner), OWNER_TO_PLAYER(payee->owner), amount);
    int moneyPaid = payMoney(payer, amount, game);
    receiveMoney(payee, moneyPaid, game);
}

int payMoney(player *player, int amount, gamestate *game)
{
    if (player->money < amount)
    {
        printf("You don't have enough money to pay!\n");
        drawseq_normal_confirm(OWNER_TO_PLAYER(player->owner),
                               game,
                               "You do not have enough money to pay and must sell assets to continue.");

        if (sellAssets(player, amount, game))
        {
            printf("You sold enough assets to pay!\n");
            drawseq_normal_confirm(OWNER_TO_PLAYER(player->owner),
                                   game,
                                   "You have sold enough assets to pay.");
        }
        else
        {
            printf("You don't have enough money to pay!\n");
            amount = player->money;
            player->money = 0;
            bankruptPlayer(player, game);
            printf("Player %d paid $%d\n", OWNER_TO_PLAYER(player->owner), amount);

            char *bankruptInfo[128];
            sprintf(bankruptInfo,
                    "Player %d paid $%d before declaring bankruptcy.",
                    OWNER_TO_PLAYER(player->owner),
                    amount);
            drawseq_normal_confirm(OWNER_TO_PLAYER(player->owner),
                                   game,
                                   bankruptInfo);

            return amount;
        }
    }
    player->money -= amount;
    printf("Player %d paid $%d\n", OWNER_TO_PLAYER(player->owner), amount);
    return amount;
}

void receiveMoney(player *player, int amount, gamestate *game)
{
    player->money += amount;
    printf("Player %d received $%d\n", OWNER_TO_PLAYER(player->owner), amount);
}

bool sellAssets(player *player, int amount, gamestate *game)
{
    // Selling to other players no implemented
    printf("Not implemented yet!\n");
    return false;
}

/**************************************
 * Player in jail
 **************************************/
void playerInJail(player *player, gamestate *game)
{
    player->jailTime++;
    printf("It is player %d's turn #%d in jail!\n", OWNER_TO_PLAYER(player->owner), player->jailTime);

    char jailInfo[128];

    sprintf(jailInfo,
            "It is player %d's turn #%d in jail.",
            OWNER_TO_PLAYER(player->owner),
            player->jailTime);

    drawseq_normal_confirm(OWNER_TO_PLAYER(player->owner), game, jailInfo);

    bool getOutOfJail = false;
    // TODO: Implement get out of jail free cards
    if (player->jailTime < 3 && player->money >= 50)
    {
        // Check if player would like to pay jail fine
        printf("Would you like to pay $50 to get out of jail? (y/n)\n");

        bool choice = drawseq_dialogue_yes_no(OWNER_TO_PLAYER(player->owner),
                                              game,
                                              "Would you like to pay $50 to get out of jail?");

        if (choice)
        {
            payMoney(player, 50, game);
            getOutOfJail = true;
        }
    }

    drawseq_normal_confirm(OWNER_TO_PLAYER(player->owner),
                           game,
                           "If you did not pay, you may still get out if you roll doubles.");

    diceRoll roll = rollDice(game);
    drawseq_roll_dice(OWNER_TO_PLAYER(player->owner), game, roll);

    if (roll.doubles || getOutOfJail)
    {
        printf("Player %d got out of jail!\n", OWNER_TO_PLAYER(player->owner));
        drawseq_normal_confirm(OWNER_TO_PLAYER(player->owner),
                               game,
                               "You got out of jail!");

        player->jailTime = 0;
        player->inJail = false;
        moveToSquare(player, roll, game);
    }
    else if (player->jailTime == 3)
    {
        printf("Player %d has been in jail for 3 turns and must pay $50 to get out!\n", OWNER_TO_PLAYER(player->owner));
        drawseq_normal_confirm(OWNER_TO_PLAYER(player->owner),
                               game,
                               "You have been in jail for three turns. You must pay $50 now to get out.");

        if (payJailFine(player, game))
        {
            printf("Player %d got out of jail!\n", OWNER_TO_PLAYER(player->owner));
            drawseq_normal_confirm(OWNER_TO_PLAYER(player->owner),
                                   game,
                                   "You got out of jail!");

            player->jailTime = 0;
            player->inJail = false;
            moveToSquare(player, roll, game);
        }
    }
}

bool payJailFine(player *player, gamestate *game)
{
    int moneyPaid = payMoney(player, 50, game);
    if (moneyPaid == 50)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/**************************************
 * Miscellaneous
 **************************************/
void passGo(player *player, gamestate *game)
{
    printf("Player %d passed go!\n", OWNER_TO_PLAYER(player->owner));
    drawseq_normal_confirm(OWNER_TO_PLAYER(player->owner),
                           game,
                           "You passes Go! You get $200.");

    receiveMoney(player, 200, game);
}

void bankruptPlayer(player *player, gamestate *game)
{
    printf("Player %d is bankrupt!\n", OWNER_TO_PLAYER(player->owner));
    drawseq_normal_confirm(OWNER_TO_PLAYER(player->owner),
                           game,
                           "You are bankrupt and out of the game.");

    player->bankrupt = true;
    // TODO: Return all properties to bank, or auction them off
    printf("Not implemented yet!\n");
}

void waitForNextTurn()
{
    printf("Press enter to continue...\n");
    while (getchar() != '\n')
        ;
    getchar();
}

/**************************************
 * Main
 **************************************/
int main(void)
{
    printf("Welcome to Monopoly!\n");
    /*Make it not random for debugging*/
    srand(time(NULL));
    gamestate game;
    initGame(&game);
    gameStart(&game);

    init_graphics();

    while (true)
    {
        playerTurn(&game.players[game.turn], &game);

        if (turnEnd(&game))
        {
            break;
        }
        // waitForNextTurn();
    }
    return 0;
}