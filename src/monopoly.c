// 320*240
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "squares.h"
#include "players.h"
#include "gamestate.h"
#include "helpers.h"
#include "display.h"
#include "interface.h"

#define GRAPHICS_ENABLED
#define OWNER_TO_PLAYER(player) (player + 1)
#ifdef GRAPHICS_ENABLED
#define DRAWSEQ_NORMAL_CONFIRM(curr_player, game, question, chance, community_chest) drawseq_normal_confirm(curr_player, game, question, chance, community_chest)
#define DRAWSEQ_TURN_START(curr_player, game) drawseq_turn_start(curr_player, game)
#define DRAWSEQ_ROLL_DICE(curr_player, game, diceRoll) drawseq_roll_dice(curr_player, game, diceRoll)
#define DRAWSEQ_MOVE_PLAYER(curr_player, game, diceRoll, old_pos, new_pos) drawseq_move_player(curr_player, game, diceRoll, old_pos, new_pos)
#define DRAWSEQ_DIALOGUE_YES_NO(curr_player, game, question) drawseq_dialogue_yes_no(curr_player, game, question)
#else
#define DRAWSEQ_NORMAL_CONFIRM(curr_player, game, question) printf("%s\n", question)
#define DRAWSEQ_TURN_START(curr_player, game)
#define DRAWSEQ_ROLL_DICE(curr_player, game, diceRoll)
#define DRAWSEQ_MOVE_PLAYER(curr_player, game, diceRoll, old_pos, new_pos)
#define DRAWSEQ_DIALOGUE_YES_NO(curr_player, game, question) userInput(curr_player, game, question)
#endif

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int userInput(int curr_player, gamestate *game, char *question)
{
    printf("%s\n", question);
    char input;
    scanf(" %c", &input);
    if (input == 'y' || input == 'Y')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/****************************************************************************************
 * Stores square data object to be copied into the gamestate
 *****************************************************************************************/
const square square_Go = {"Go", Action, Go, .data.action = GoAction};
const square square_MediterraneanAvenue = {"Mediterranean Avenue", Property, MediteraneanAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 60, .mortgageValue = 30, .mortgaged = false, .coloredProperty = {.color = Brown, .houseCost = 50, .hotelCost = 50, .houseCount = 0, .hotelCount = 0, .rent = {2, 10, 30, 90, 160, 250}}}};
const square square_CommunityChest1 = {"Community Chest", Action, CommunityChest1, .data.action = CommunityChestAction};
const square square_BalticAvenue = {"Baltic Avenue", Property, BalticAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 60, .mortgageValue = 30, .mortgaged = false, .coloredProperty = {.color = Brown, .houseCost = 50, .hotelCost = 50, .houseCount = 0, .hotelCount = 0, .rent = {4, 20, 60, 180, 320, 450}}}};
const square square_IncomeTax = {"Income Tax", Action, IncomeTaxAction, .data.action = IncomeTaxAction};
const square square_ReadingRailRoad = {"Reading Rail Road", Property, ReadingRailRoad, .data.property = {.type = RailRoad, .owner = Bank, .price = 200, .mortgageValue = 100, .mortgaged = false}};
const square square_OrientalAvenue = {"Oriental Avenue", Property, OrientalAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 100, .mortgageValue = 50, .mortgaged = false, .coloredProperty = {.color = LightBlue, .houseCost = 50, .hotelCost = 50, .houseCount = 0, .hotelCount = 0, .rent = {6, 30, 90, 270, 400, 550}}}};
const square square_Chance1 = {"Chance", Action, Chance1, .data.action = ChanceAction};
const square square_VermontAvenue = {"Vermont Avenue", Property, VermontAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 100, .mortgageValue = 50, .mortgaged = false, .coloredProperty = {.color = LightBlue, .houseCost = 50, .hotelCost = 50, .houseCount = 0, .hotelCount = 0, .rent = {6, 30, 90, 270, 400, 550}}}};
const square square_ConnecticutAvenue = {"Connecticut Avenue", Property, ConnecticutAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 120, .mortgageValue = 60, .mortgaged = false, .coloredProperty = {.color = LightBlue, .houseCost = 50, .hotelCost = 50, .houseCount = 0, .hotelCount = 0, .rent = {8, 40, 100, 300, 450, 600}}}};
const square square_JustVisiting = {"Just Visiting", Action, JustVisiting, .data.action = FreeParkingAction};
const square square_StCharlesPlace = {"St. Charles Place", Property, StCharlesPlace, .data.property = {.type = Colored, .owner = Bank, .price = 140, .mortgageValue = 70, .mortgaged = false, .coloredProperty = {.color = Pink, .houseCost = 100, .hotelCost = 100, .houseCount = 0, .hotelCount = 0, .rent = {10, 50, 150, 450, 625, 750}}}};
const square square_ElectricCompany = {"Electric Company", Property, ElectricCompany, .data.property = {.type = Utility, .owner = Bank, .price = 150, .mortgageValue = 75, .mortgaged = false}};
const square square_StatesAvenue = {"States Avenue", Property, StatesAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 140, .mortgageValue = 70, .mortgaged = false, .coloredProperty = {.color = Pink, .houseCost = 100, .hotelCost = 100, .houseCount = 0, .hotelCount = 0, .rent = {10, 50, 150, 450, 625, 750}}}};
const square square_VirginiaAvenue = {"Virginia Avenue", Property, VirginiaAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 160, .mortgageValue = 80, .mortgaged = false, .coloredProperty = {.color = Pink, .houseCost = 100, .hotelCost = 100, .houseCount = 0, .hotelCount = 0, .rent = {12, 60, 180, 500, 700, 900}}}};
const square square_PennsylvaniaRailRoad = {"Pennsylvania Rail Road", Property, PennsylvaniaRailRoad, .data.property = {.type = RailRoad, .owner = Bank, .price = 200, .mortgageValue = 100, .mortgaged = false}};
const square square_StJamesPlace = {"St. James Place", Property, StJamesPlace, .data.property = {.type = Colored, .owner = Bank, .price = 180, .mortgageValue = 90, .mortgaged = false, .coloredProperty = {.color = Orange, .houseCost = 100, .hotelCost = 100, .houseCount = 0, .hotelCount = 0, .rent = {14, 70, 200, 550, 750, 950}}}};
const square square_CommunityChest2 = {"Community Chest", Action, CommunityChest2, .data.action = CommunityChestAction};
const square square_TennesseeAvenue = {"Tennessee Avenue", Property, TennesseeAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 180, .mortgageValue = 90, .mortgaged = false, .coloredProperty = {.color = Orange, .houseCost = 100, .hotelCost = 100, .houseCount = 0, .hotelCount = 0, .rent = {14, 70, 200, 550, 750, 950}}}};
const square square_NewYorkAvenue = {"New York Avenue", Property, NewYorkAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 200, .mortgageValue = 100, .mortgaged = false, .coloredProperty = {.color = Orange, .houseCost = 100, .hotelCost = 100, .houseCount = 0, .hotelCount = 0, .rent = {16, 80, 220, 600, 800, 1000}}}};
const square square_FreeParking = {"Free Parking", Action, FreeParking, .data.action = FreeParkingAction};
const square square_KentuckyAvenue = {"Kentucky Avenue", Property, KentuckyAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 220, .mortgageValue = 110, .mortgaged = false, .coloredProperty = {.color = Red, .houseCost = 150, .hotelCost = 150, .houseCount = 0, .hotelCount = 0, .rent = {18, 90, 250, 700, 875, 1050}}}};
const square square_Chance2 = {"Chance", Action, Chance2, .data.action = ChanceAction};
const square square_IndianaAvenue = {"Indiana Avenue", Property, IndianaAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 220, .mortgageValue = 110, .mortgaged = false, .coloredProperty = {.color = Red, .houseCost = 150, .hotelCost = 150, .houseCount = 0, .hotelCount = 0, .rent = {18, 90, 250, 700, 875, 1050}}}};
const square square_IllinoisAvenue = {"Illinois Avenue", Property, IllinoisAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 240, .mortgageValue = 120, .mortgaged = false, .coloredProperty = {.color = Red, .houseCost = 150, .hotelCost = 150, .houseCount = 0, .hotelCount = 0, .rent = {20, 100, 300, 750, 925, 1100}}}};
const square square_BAndO_RailRoad = {"B & O Rail Road", Property, BAndORailRoad, .data.property = {.type = RailRoad, .owner = Bank, .price = 200, .mortgageValue = 100, .mortgaged = false}};
const square square_AtlanticAvenue = {"Atlantic Avenue", Property, AtlanticAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 260, .mortgageValue = 130, .mortgaged = false, .coloredProperty = {.color = Yellow, .houseCost = 150, .hotelCost = 150, .houseCount = 0, .hotelCount = 0, .rent = {22, 110, 330, 800, 975, 1150}}}};
const square square_VentnorAvenue = {"Ventnor Avenue", Property, VentnorAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 260, .mortgageValue = 130, .mortgaged = false, .coloredProperty = {.color = Yellow, .houseCost = 150, .hotelCost = 150, .houseCount = 0, .hotelCount = 0, .rent = {22, 110, 330, 800, 975, 1150}}}};
const square square_WaterWorks = {"Water Works", Property, WaterWorks, .data.property = {.type = Utility, .owner = Bank, .price = 150, .mortgageValue = 75, .mortgaged = false}};
const square square_MarvinGardens = {"Marvin Gardens", Property, MarvinGardens, .data.property = {.type = Colored, .owner = Bank, .price = 280, .mortgageValue = 140, .mortgaged = false, .coloredProperty = {.color = Yellow, .houseCost = 150, .hotelCost = 150, .houseCount = 0, .hotelCount = 0, .rent = {24, 120, 360, 850, 1025, 1200}}}};
const square square_GoToJail = {"Go To Jail", Action, GoToJail, .data.action = GoToJailAction};
const square square_PacificAvenue = {"Pacific Avenue", Property, PacificAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 300, .mortgageValue = 150, .mortgaged = false, .coloredProperty = {.color = Green, .houseCost = 200, .hotelCost = 200, .houseCount = 0, .hotelCount = 0, .rent = {26, 130, 390, 900, 1100, 1275}}}};
const square square_NorthCarolinaAvenue = {"North Carolina Avenue", Property, NorthCarolinaAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 300, .mortgageValue = 150, .mortgaged = false, .coloredProperty = {.color = Green, .houseCost = 200, .hotelCost = 200, .houseCount = 0, .hotelCount = 0, .rent = {26, 130, 390, 900, 1100, 1275}}}};
const square square_CommunityChest3 = {"Community Chest", Action, CommunityChest3, .data.action = CommunityChestAction};
const square square_PennsylvaniaAvenue = {"Pennsylvania Avenue", Property, PennsylvaniaAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 320, .mortgageValue = 160, .mortgaged = false, .coloredProperty = {.color = Green, .houseCost = 200, .hotelCost = 200, .houseCount = 0, .hotelCount = 0, .rent = {28, 150, 450, 1000, 1200, 1400}}}};
const square square_ShortLine = {"Short Line", Property, ShortLine, .data.property = {.type = RailRoad, .owner = Bank, .price = 200, .mortgageValue = 100, .mortgaged = false}};
const square square_Chance3 = {"Chance", Action, Chance3, .data.action = ChanceAction};
const square square_ParkPlace = {"Park Place", Property, ParkPlace, .data.property = {.type = Colored, .owner = Bank, .price = 350, .mortgageValue = 175, .mortgaged = false, .coloredProperty = {.color = DarkBlue, .houseCost = 200, .hotelCost = 200, .houseCount = 0, .hotelCount = 0, .rent = {35, 175, 500, 1100, 1300, 1500}}}};
const square square_LuxuryTax = {"Luxury Tax", Action, LuxuryTax, .data.action = LuxuryTaxAction};
const square square_Boardwalk = {"Boardwalk", Property, Boardwalk, .data.property = {.type = Colored, .owner = Bank, .price = 400, .mortgageValue = 200, .mortgaged = false, .coloredProperty = {.color = DarkBlue, .houseCost = 200, .hotelCost = 200, .houseCount = 0, .hotelCount = 0, .rent = {50, 200, 600, 1400, 1700, 2000}}}};
const square *board_ptr[] = {&square_Go, &square_MediterraneanAvenue, &square_CommunityChest1, &square_BalticAvenue, &square_IncomeTax, &square_ReadingRailRoad, &square_OrientalAvenue, &square_Chance1, &square_VermontAvenue, &square_ConnecticutAvenue, &square_JustVisiting, &square_StCharlesPlace, &square_ElectricCompany, &square_StatesAvenue, &square_VirginiaAvenue, &square_PennsylvaniaRailRoad, &square_StJamesPlace, &square_CommunityChest2, &square_TennesseeAvenue, &square_NewYorkAvenue, &square_FreeParking, &square_KentuckyAvenue, &square_Chance2, &square_IndianaAvenue, &square_IllinoisAvenue, &square_BAndO_RailRoad, &square_AtlanticAvenue, &square_VentnorAvenue, &square_WaterWorks, &square_MarvinGardens, &square_GoToJail, &square_PacificAvenue, &square_NorthCarolinaAvenue, &square_CommunityChest3, &square_PennsylvaniaAvenue, &square_ShortLine, &square_Chance3, &square_ParkPlace, &square_LuxuryTax, &square_Boardwalk};
/*Function defs*/

/**************************************
 * Game related
 **************************************/

void initGame(gamestate *game)
{
    /*Init board*/
    for (int i = 0; i < MAX_SQUARES; i++)
    {
        memcpy(&game->board[i], board_ptr[i], sizeof(square));
    }
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
        char winStmt[128];
        sprintf(winStmt, "Game Over! The winner is player %d.", winningPlayer);
        DRAWSEQ_NORMAL_CONFIRM(winningPlayer, game, winStmt, false, false);

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

    DRAWSEQ_TURN_START(OWNER_TO_PLAYER(player->owner), game);

    if (player->inJail)
    {
        playerInJail(player, game);
    }
    else
    {
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner), game, "Roll dice to move.", false, false);
        diceRoll roll = rollDice(game);
        DRAWSEQ_ROLL_DICE(OWNER_TO_PLAYER(player->owner), game, roll);

        moveToSquare(player, roll, game);
    }

    if (DRAWSEQ_DIALOGUE_YES_NO(player->owner, game, "Would you like to buy a house or hotel? (y/n)"))
    {
        checkForMonopoly(player, game);
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
    int oldPosition = player->position;
    int newPositionRaw = player->position + roll.die1 + roll.die2;
    player->position = newPositionRaw % MAX_SQUARES;

    DRAWSEQ_MOVE_PLAYER(OWNER_TO_PLAYER(player->owner), game, roll, oldPosition, newPositionRaw);
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
        chance(player, game);
        break;
    case (CommunityChestAction):
        communityChest(player, game);
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
        if (player->money >= square->data.property.price)
        {
            char query[256];
            sprintf(query,
                    "%s is unowned. Would you like to buy it for $%d?",
                    square->name,
                    square->data.property.price);

            if (DRAWSEQ_DIALOGUE_YES_NO(OWNER_TO_PLAYER(player->owner), game, query))
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

            DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                                   game,
                                   query, false, false);
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
    DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                           game,
                           "You must pay $200 income tax.", false, false);

    payMoney(player, 200, game);
}

void payLuxuryTax(player *player, gamestate *game)
{
    DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                           game,
                           "You must pay $200 luxury tax.", false, false);

    payMoney(player, 100, game);
}

void goToJail(player *player, gamestate *game)
{
    DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                           game,
                           "Go to jail! Do not pass Go. Do not collect $200.", false, false);

    player->position = JustVisiting;
    player->inJail = true;
}

void communityChest(player *player, gamestate *game)
{
    int communitychestcard = rand() % 17;
    switch (communitychestcard)
    {
    case (0):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Advance to Go (Collect $200)", false, true);
        landOnSquare(player, &game->board[Go], game);
        passGo(player, game);
        break;
    case (1):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Bank error in your favor. Collect $200.", false, true);
        receiveMoney(player, 200, game);
        break;
    case (2):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Doctor's fees. Pay $50.", false, true);
        payMoney(player, 50, game);
        break;
    case (3):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "From sale of stock you get $50.", false, true);
        receiveMoney(player, 50, game);
        break;
    case (4):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Get Out of Jail Free. This card may be kept until needed, or sold.", false, true);
        player->getOutOfJailFreeCards++;
        break;
    case (5):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Go to Jail. Go directly to jail. Do not pass Go. Do not collect $200.", false, true);
        goToJail(player, game);
        break;
    case (6):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Grand Opera Night. Collect $50 from every player for opening night seats.", false, true);
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if (game->players[i].owner != player->owner && game->players[i].bankrupt == false)
            {
                payPlayer(&game->players[i], player, 50, game);
            }
        }
        break;
    case (7):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Holiday Fund matures. Receive $100.", false, true);
        receiveMoney(player, 100, game);
        break;
    case (8):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Income tax refund. Collect $20.", false, true);
        receiveMoney(player, 20, game);
        break;
    case (9):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "It is your birthday. Collect $10 from every player.", false, true);
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if (game->players[i].owner != player->owner && game->players[i].bankrupt == false)
            {
                payPlayer(&game->players[i], player, 10, game);
            }
        }
        break;
    case (10):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Life insurance matures - Collect $100.", false, true);
        receiveMoney(player, 100, game);
        break;
    case (11):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Pay hospital fees of $100.", false, true);
        payMoney(player, 100, game);
        break;
    case (12):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Pay school fees of $50.", false, true);
        payMoney(player, 50, game);
        break;
    case (13):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Receive $25 consultancy fee.", false, true);
        receiveMoney(player, 25, game);
        break;
    case (14):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "You are assessed for street repairs - $40 per house, $115 per hotel.", false, true);
        int totalHouses = 0;
        int totalHotels = 0;
        for (int i = 0; i < MAX_SQUARES; i++)
        {
            if (game->board[i].type == Property)
            {
                if (game->board[i].data.property.owner == player->owner)
                {
                    if (game->board[i].data.property.coloredProperty.hotelCount == 1)
                    {
                        totalHotels++;
                    }
                    else
                    {
                        totalHouses += game->board[i].data.property.coloredProperty.houseCount;
                    }
                }
            }
        }
        payMoney(player, (totalHouses * 40) + (totalHotels * 115), game);
        break;
    case (15):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "You have won second prize in a beauty contest - Collect $10.", false, true);
        receiveMoney(player, 10, game);
        break;
    case (16):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "You inherit $100.", false, true);
        receiveMoney(player, 100, game);
        break;
    }
}

void chance(player *player, gamestate *game)
{
    int chancecard = rand() % 14;
    switch (chancecard)
    {
    case (0):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Advance to Go (Collect $200)", true, false);
        landOnSquare(player, &game->board[Go], game);
        passGo(player, game);
        break;
    case (1):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Advance to Illinois Ave. If you pass Go, collect $200.", true, false);
        if (player->position >= IllinoisAvenue)
        {
            passGo(player, game);
        }
        landOnSquare(player, &game->board[IllinoisAvenue], game);
        break;
    case (2):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Advance to St. Charles Place. If you pass Go, collect $200.", true, false);
        if (player->position >= StCharlesPlace)
        {
            passGo(player, game);
        }
        landOnSquare(player, &game->board[StCharlesPlace], game);
        break;
    case (3):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Advance token to the nearest Utility. If unowned, you may buy it from the Bank. If owned, throw dice and pay owner a total ten times the amount thrown.", true, false);
        enum SquareNames nearestUtility;
        if (WaterWorks - player->position % MAX_SQUARES < ElectricCompany - player->position % MAX_SQUARES)
        {
            nearestUtility = WaterWorks;
        }
        else
        {
            nearestUtility = ElectricCompany;
        }
        if (player->position >= nearestUtility)
        {
            passGo(player, game);
        }
        landOnSquare(player, &game->board[nearestUtility], game);
        break;
    case (4):
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Advance token to the nearest Railroad and pay owner twice the rental to which he/she is otherwise entitled. If Railroad is unowned, you may buy it from the Bank.", true, false);
        enum SquareNames nearestRailroad;
        if (ReadingRailRoad - player->position % MAX_SQUARES < BAndORailRoad - player->position % MAX_SQUARES &&
            ReadingRailRoad - player->position % MAX_SQUARES < ShortLine - player->position % MAX_SQUARES &&
            ReadingRailRoad - player->position % MAX_SQUARES < PennsylvaniaRailRoad - player->position % MAX_SQUARES)
        {
            nearestRailroad = ReadingRailRoad;
        }
        else if (BAndORailRoad - player->position % MAX_SQUARES < ShortLine - player->position % MAX_SQUARES &&
                 BAndORailRoad - player->position % MAX_SQUARES < PennsylvaniaRailRoad - player->position % MAX_SQUARES)
        {
            nearestRailroad = BAndORailRoad;
        }
        else if (ShortLine - player->position % MAX_SQUARES < PennsylvaniaRailRoad - player->position % MAX_SQUARES)
        {
            nearestRailroad = ShortLine;
        }
        else
        {
            nearestRailroad = PennsylvaniaRailRoad;
        }
        if (player->position >= nearestRailroad)
        {
            passGo(player, game);
        }
        landOnSquare(player, &game->board[nearestRailroad], game);
        break;
    case (5):
        // bank pays 50
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Bank pays you dividend of $50.", true, false);
        receiveMoney(player, 50, game);
        break;
    case (6):
        // get out of jail free
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Get out of jail free. This card may be kept until needed, or traded/sold.", true, false);
        player->getOutOfJailFreeCards++;
        break;
    case (7):
        // go back 3 spaces
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Go back 3 spaces.", true, false);
        player->position = (player->position - 3) % MAX_SQUARES;
        landOnSquare(player, &game->board[player->position], game);
        break;
    case (8):
        // go to jail
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Go to jail. Go directly to jail. Do not pass Go. Do not collect $200.", true, false);
        goToJail(player, game);
        break;
    case (9):
        // make general repairs on all your property
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Make general repairs on all your property. For each house pay $25. For each hotel pay $100.", true, false);
        int totalHouses = 0;
        int totalHotels = 0;
        for (int i = 0; i < MAX_SQUARES; i++)
        {
            if (game->board[i].type == Property)
            {
                if (game->board[i].data.property.owner == player->owner)
                {
                    if (game->board[i].data.property.coloredProperty.hotelCount == 1)
                    {
                        totalHotels++;
                    }
                    else
                    {
                        totalHouses += game->board[i].data.property.coloredProperty.houseCount;
                    }
                }
            }
        }
        payMoney(player, totalHouses * 25 + totalHotels * 100, game);
        break;
    case (10):
        // go to Reading Railroad
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Take a trip to Reading Railroad.", true, false);
        if (player->position >= ReadingRailRoad)
        {
            passGo(player, game);
        }
        landOnSquare(player, &game->board[ReadingRailRoad], game);
        break;
    case (11):
        // go to Boardwalk
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Take a walk on the Boardwalk. Advance token to Boardwalk.", true, false);
        if (player->position >= Boardwalk)
        {
            passGo(player, game);
        }
        landOnSquare(player, &game->board[Boardwalk], game);
        break;
    case (12):
        // elected chairman of the board
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "You have been elected chairman of the board. Pay each player $50.", true, false);
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if (game->players[i].owner != player->owner && game->players[i].bankrupt == false)
            {
                payPlayer(player, &game->players[i], 50, game);
            }
        }
        break;
    case (13):
        // your building loan matures
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "Your building loan matures. Collect $150.", true, false);
        receiveMoney(player, 150, game);
        break;
    }
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
    int rent = square->data.property.coloredProperty.rent[0];
    enum Colors setColor = square->data.property.coloredProperty.color;
    bool setOwned = false;
    // TODO: Add house and hotel rent
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
    DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner), game, payConfirm, false, false);

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
    DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner), game, payConfirm, false, false);

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
    DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner), game, payConfirm, false, false);

    printf("Paying player %d $%d rent...\n", OWNER_TO_PLAYER(railroadOwner), rent);
    payPlayer(player, &game->players[railroadOwner], rent, game);
}

void buyProperty(player *player, square *square, gamestate *game)
{
    if (player->money < square->data.property.price)
    {
        char message[256];
        sprintf(message, "You do not have enough money to buy %s.\n", square->name);
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               message, false, false);

        return;
    }
    payMoney(player, square->data.property.price, game);
    square->data.property.owner = player->owner;
    player->owned_properties[player->owned_properties_count] = square;
    player->owned_properties_count++;

    char message[256];
    sprintf(message, "Player %d successfully bought %s for $%d.",
            OWNER_TO_PLAYER(player->owner),
            square->name,
            square->data.property.price);

    DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                           game,
                           message, false, false);
}

void sellProperty(player *player, square *square, gamestate *game)
{
    if (square->data.property.owner != player->owner)
    {
        char message[256];
        sprintf(message, "You do not own %s and cannot sell it.\n", square->name);
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               message, false, false);

        return;
    }
    char message[256];
    if (square->data.property.mortgaged)
    {
        square->data.property.mortgaged = false;
        sprintf(message, "You sold %s for $%d.", square->name, square->data.property.price - square->data.property.mortgageValue);
        receiveMoney(player, square->data.property.price - square->data.property.mortgageValue, game);
    }
    else
    {
        sprintf(message, "You sold %s for $%d.", square->name, square->data.property.price);
        receiveMoney(player, square->data.property.price, game);
    }
    square->data.property.owner = Bank;

    DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                           game,
                           message, false, false);

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

void mortgageProperty(player *player, square *square, gamestate *game)
{
    game->board[square->squareName].data.property.mortgaged = true;
    receiveMoney(player, square->data.property.mortgageValue, game);
}

void unmortgageProperty(player *player, square *square, gamestate *game)
{
    game->board[square->squareName].data.property.mortgaged = false;
    payMoney(player, (int)(square->data.property.mortgageValue * 1.1), game);
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
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "You do not have enough money to pay and must sell assets to continue.", false, false);

        if (sellAssets(player, amount, game))
        {
            DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                                   game,
                                   "You have sold enough assets to pay.", false, false);
        }
        else
        {
            printf("You don't have enough money to pay!\n");
            amount = player->money;
            player->money = 0;
            bankruptPlayer(player, game);
            printf("Player %d paid $%d\n", OWNER_TO_PLAYER(player->owner), amount);

            char bankruptInfo[128];
            sprintf(bankruptInfo,
                    "Player %d paid $%d before declaring bankruptcy.",
                    OWNER_TO_PLAYER(player->owner),
                    amount);
            DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                                   game,
                                   bankruptInfo, false, false);

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
    // TODO: Implement sell assets
    printf("Not implemented yet!\n");
    return false;
}

/**************************************
 * Player in jail
 **************************************/
void playerInJail(player *player, gamestate *game)
{
    player->jailTime++;

    char jailInfo[128];

    sprintf(jailInfo,
            "It is player %d's turn #%d in jail.",
            OWNER_TO_PLAYER(player->owner),
            player->jailTime);

    DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner), game, jailInfo, false, false);

    bool getOutOfJail = false;
    if (player->jailTime < 3 && player->money >= 50)
    {
        // Check if player would like to pay jail fine

        bool choice = DRAWSEQ_DIALOGUE_YES_NO(OWNER_TO_PLAYER(player->owner),
                                              game,
                                              "Would you like to pay $50 to get out of jail?");

        if (choice)
        {
            payMoney(player, 50, game);
            getOutOfJail = true;
        }
    }

    DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                           game,
                           "If you did not pay, you may still get out if you roll doubles.", false, false);

    diceRoll roll = rollDice(game);
    DRAWSEQ_ROLL_DICE(OWNER_TO_PLAYER(player->owner), game, roll);
    if (roll.doubles)
    {
        getOutOfJail = true;
    }
    if (!getOutOfJail && player->getOutOfJailFreeCards > 0)
    {
        bool choice = DRAWSEQ_DIALOGUE_YES_NO(OWNER_TO_PLAYER(player->owner),
                                              game,
                                              "Would you like to use a get out of jail free card?");

        if (choice)
        {
            player->getOutOfJailFreeCards--;
            getOutOfJail = true;
        }
    }
    if (!getOutOfJail && player->jailTime == 3)
    {
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "You have been in jail for three turns. You must pay $50 now to get out.", false, false);

        if (payJailFine(player, game))
        {
            getOutOfJail = true;
        }
    }
    if (getOutOfJail)
    {
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "You got out of jail!", false, false);

        DRAWSEQ_ROLL_DICE(OWNER_TO_PLAYER(player->owner), game, roll);

        player->jailTime = 0;
        player->inJail = false;
        moveToSquare(player, roll, game);
    }
    else
    {
        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                               game,
                               "You did not get out of jail.", false, false);
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
    DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                           game,
                           "You passes Go! You get $200.", false, false);

    receiveMoney(player, 200, game);
}

void bankruptPlayer(player *player, gamestate *game)
{
    DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner),
                           game,
                           "You are bankrupt and out of the game.", false, false);

    player->bankrupt = true;
    // return all properties to bank
    for (int i = 0; i < MAX_SQUARES; i++)
    {
        if (game->board[i].type == Property)
        {
            if (game->board[i].data.property.owner == player->owner)
            {
                game->board[i].data.property.owner = Bank;
                game->board[i].data.property.mortgaged = false;
                if (game->board[i].data.property.type == Colored)
                {
                    game->board[i].data.property.coloredProperty.houseCount = 0;
                    game->board[i].data.property.coloredProperty.hotelCount = 0;
                }
            }
        }
    }
}

void waitForNextTurn()
{
    printf("Press enter to continue...\n");
    while (getchar() != '\n')
        ;
    getchar();
}

/**************************************
 * Houses and Hotels
 **************************************/
void checkForMonopoly(player *player, gamestate *game)
{
    for (int setColor = 0; setColor < NUM_COLORS; setColor++)
    {
        bool setOwned = false;
        switch (setColor)
        {
        case (Brown):
            if (game->board[MediteraneanAvenue].data.property.owner == player->owner &&
                game->board[BalticAvenue].data.property.owner == player->owner)
            {
                setOwned = true;
            }
            break;
        case (LightBlue):
            if (game->board[OrientalAvenue].data.property.owner == player->owner &&
                game->board[VermontAvenue].data.property.owner == player->owner &&
                game->board[ConnecticutAvenue].data.property.owner == player->owner)
            {
                setOwned = true;
            }
            break;
        case (Pink):
            if (game->board[StCharlesPlace].data.property.owner == player->owner &&
                game->board[StatesAvenue].data.property.owner == player->owner &&
                game->board[VirginiaAvenue].data.property.owner == player->owner)
            {
                setOwned = true;
            }
            break;
        case (Orange):
            if (game->board[StJamesPlace].data.property.owner == player->owner &&
                game->board[TennesseeAvenue].data.property.owner == player->owner &&
                game->board[NewYorkAvenue].data.property.owner == player->owner)
            {
                setOwned = true;
            }
            break;
        case (Red):
            if (game->board[KentuckyAvenue].data.property.owner == player->owner &&
                game->board[IndianaAvenue].data.property.owner == player->owner &&
                game->board[IllinoisAvenue].data.property.owner == player->owner)
            {
                setOwned = true;
            }
            break;
        case (Yellow):
            if (game->board[AtlanticAvenue].data.property.owner == player->owner &&
                game->board[VentnorAvenue].data.property.owner == player->owner &&
                game->board[MarvinGardens].data.property.owner == player->owner)
            {
                setOwned = true;
            }
            break;
        case (Green):
            if (game->board[PacificAvenue].data.property.owner == player->owner &&
                game->board[NorthCarolinaAvenue].data.property.owner == player->owner &&
                game->board[PennsylvaniaAvenue].data.property.owner == player->owner)
            {
                setOwned = true;
            }
            break;
        case (DarkBlue):
            if (game->board[ParkPlace].data.property.owner == player->owner &&
                game->board[Boardwalk].data.property.owner == player->owner)
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
            char query[256];
            sprintf(query, "You own a monopoly on %s! Would you like to buy houses or hotels?", colorStrings[setColor]);
            if (DRAWSEQ_DIALOGUE_YES_NO(OWNER_TO_PLAYER(player->owner), game, query))
            {
                buyHouseorHotelSet(player, setColor, game);
            }
        }
    }
}

void buyHouseorHotelSet(player *player, enum Colors setColor, gamestate *game)
{
    enum SquareNames squareName1 = 0, squareName2 = 0, squareName3 = 0;
    int propertiesInSet = 0;

    switch (setColor)
    {
    case (Brown):
        squareName1 = MediteraneanAvenue;
        squareName2 = BalticAvenue;
        propertiesInSet = 2;
        break;
    case (LightBlue):
        squareName1 = OrientalAvenue;
        squareName2 = VermontAvenue;
        squareName3 = ConnecticutAvenue;
        propertiesInSet = 3;
        break;
    case (Pink):
        squareName1 = StCharlesPlace;
        squareName2 = StatesAvenue;
        squareName3 = VirginiaAvenue;
        propertiesInSet = 3;
        break;
    case (Orange):
        squareName1 = StJamesPlace;
        squareName2 = TennesseeAvenue;
        squareName3 = NewYorkAvenue;
        propertiesInSet = 3;
        break;
    case (Red):
        squareName1 = KentuckyAvenue;
        squareName2 = IndianaAvenue;
        squareName3 = IllinoisAvenue;
        propertiesInSet = 3;
        break;
    case (Yellow):
        squareName1 = AtlanticAvenue;
        squareName2 = VentnorAvenue;
        squareName3 = MarvinGardens;
        propertiesInSet = 3;
        break;
    case (Green):
        squareName1 = PacificAvenue;
        squareName2 = NorthCarolinaAvenue;
        squareName3 = PennsylvaniaAvenue;
        propertiesInSet = 3;
        break;
    case (DarkBlue):
        squareName1 = ParkPlace;
        squareName2 = Boardwalk;
        propertiesInSet = 2;
        break;

    default:
        printf("Error: Color not recognized\n");
        break;
    }
    if (propertiesInSet == 2)
    {
        if (game->board[squareName1].data.property.coloredProperty.houseCount < 4 ||
            game->board[squareName2].data.property.coloredProperty.houseCount < 4)
        { // Buying houses
            for (int i = 0; i < 2; i++)
            {
                if (game->board[squareName1].data.property.coloredProperty.houseCount < 4)
                {
                    char query[256];
                    sprintf(query, "Would you like to buy a house on %s?", game->board[squareName1].name);
                    if (DRAWSEQ_DIALOGUE_YES_NO(OWNER_TO_PLAYER(player->owner), game, query))
                    {
                        if (player->money >= game->board[squareName1].data.property.coloredProperty.houseCost)
                        { // Check for money
                            if (MIN(game->board[squareName1].data.property.coloredProperty.houseCount, game->board[squareName2].data.property.coloredProperty.houseCount) != game->board[squareName1].data.property.coloredProperty.houseCount)
                            { // Check for house number difference
                                payMoney(player, game->board[squareName1].data.property.coloredProperty.houseCost, game);
                                game->board[squareName1].data.property.coloredProperty.houseCount++;
                            }
                            else
                            {
                                DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner), game, "You can't buy a house on a property with a different number of houses!", false, false);
                            }
                        }
                        else
                        {
                            DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner), game, "You don't have enough money to buy a house!", false, false);
                        }
                    }
                }
                enum SquareNames temp = squareName1;
                squareName1 = squareName2;
                squareName2 = temp;
            }
        }
        else
        { // Buying hotels
            for (int i = 0; i < 2; i++)
            {
                char query[256];
                sprintf(query, "Would you like to buy a hotel on %s?", game->board[squareName1].name);
                if (DRAWSEQ_DIALOGUE_YES_NO(OWNER_TO_PLAYER(player->owner), game, query))
                {
                    if (player->money >= game->board[squareName1].data.property.coloredProperty.hotelCost)
                    { // Check for money
                        if (game->board[squareName1].data.property.coloredProperty.hotelCount != 0)
                        { // Check for hotel number difference
                            payMoney(player, game->board[squareName1].data.property.coloredProperty.hotelCost, game);
                            game->board[squareName1].data.property.coloredProperty.hotelCount++;
                        }
                        else
                        {
                            DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner), game, "You can't buy a hotel on a property with a different number of hotel!", false, false);
                        }
                    }
                    else
                    {
                        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner), game, "You don't have enough money to buy a hotel!", false, false);
                    }
                }
                enum SquareNames temp = squareName1;
                squareName1 = squareName2;
                squareName2 = temp;
            }
        }
        if (propertiesInSet == 3)
        {
            if (game->board[squareName1].data.property.coloredProperty.houseCount < 4 ||
                game->board[squareName2].data.property.coloredProperty.houseCount < 4 ||
                game->board[squareName3].data.property.coloredProperty.houseCount < 4)
            { // Buying houses
                for (int i = 0; i < 3; i++)
                {
                    if (game->board[squareName1].data.property.coloredProperty.houseCount < 4)
                    {
                        char query[256];
                        sprintf(query, "Would you like to buy a house on %s?", game->board[squareName1].name);
                        if (DRAWSEQ_DIALOGUE_YES_NO(OWNER_TO_PLAYER(player->owner), game, query))
                        {
                            if (player->money >= game->board[squareName1].data.property.coloredProperty.houseCost)
                            { // Check for money
                                if (MIN(game->board[squareName1].data.property.coloredProperty.houseCount, MIN(game->board[squareName2].data.property.coloredProperty.houseCount, game->board[squareName3].data.property.coloredProperty.houseCount)) != game->board[squareName1].data.property.coloredProperty.houseCount)
                                { // Check for house number difference
                                    payMoney(player, game->board[squareName1].data.property.coloredProperty.houseCost, game);
                                    game->board[squareName1].data.property.coloredProperty.houseCount++;
                                }
                                else
                                {
                                    DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner), game, "You can't buy a house on a property with a different number of houses!", false, false);
                                }
                            }
                            else
                            {
                                DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner), game, "You don't have enough money to buy a house!", false, false);
                            }
                        }
                    }
                    enum SquareNames tmp = squareName1;
                    squareName1 = squareName2;
                    squareName2 = squareName3;
                    squareName3 = tmp;
                }
            }
        }
        else
        { // Buying hotels
            for (int i = 0; i < 3; i++)
            {
                char query[256];
                sprintf(query, "Would you like to buy a hotel on %s?", game->board[squareName1].name);
                if (DRAWSEQ_DIALOGUE_YES_NO(OWNER_TO_PLAYER(player->owner), game, query))
                {
                    if (player->money >= game->board[squareName1].data.property.coloredProperty.hotelCost)
                    { // Check for money
                        if (game->board[squareName1].data.property.coloredProperty.hotelCount != 0)
                        { // Check for hotel number difference
                            payMoney(player, game->board[squareName1].data.property.coloredProperty.hotelCost, game);
                            game->board[squareName1].data.property.coloredProperty.hotelCount++;
                        }
                        else
                        {
                            DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner), game, "You can't buy a hotel on a property with a different number of hotel!", false, false);
                        }
                    }
                    else
                    {
                        DRAWSEQ_NORMAL_CONFIRM(OWNER_TO_PLAYER(player->owner), game, "You don't have enough money to buy a hotel!", false, false);
                    }
                }
                enum SquareNames tmp = squareName1;
                squareName1 = squareName2;
                squareName2 = squareName3;
                squareName3 = tmp;
            }
        }
    }
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

#ifdef GRAPHICS_ENABLED
    init_graphics();
#endif
    while (true)
    {
        playerTurn(&game.players[game.turn], &game);

        if (turnEnd(&game))
        {
            break;
        }
#ifndef GRAPHICS_ENABLED
        waitForNextTurn();
#endif
    }
    return 0;
}
