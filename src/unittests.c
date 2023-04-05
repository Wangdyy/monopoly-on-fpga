#include "munit.h"
#include <stdio.h>
#include "stdbool.h"
#include "squares.h"
#include "players.h"
#include "gamestate.h"
#include "helpers.h"
#include "display.h"
#include "interface.h"
#include "presets.h"

MunitResult my_test(const MunitParameter params[], void *fixture)
{
    char *str = (char *)fixture;
    munit_assert_string_equal(str, "Hello, world!");
    return MUNIT_OK;
}

static void *
test_setup(const MunitParameter params[], void *user_data)
{
    return strdup("Hello, world!");
}

static void
test_tear_down(void *fixture)
{
    free(fixture);
}

MunitResult initGame_test(const MunitParameter params[], void *fixture)
{
    gamestate *game = (gamestate *)fixture;
    initGame(game);
    square Parkplace = game->board[37];
    munit_assert_string_equal(Parkplace.name, "Park Place");
    munit_assert_int(game->players[0].money, ==, 1500);
    return MUNIT_OK;
}

MunitResult checkForGameOver_test(const MunitParameter params[], void *fixture)
{
    gamestate *game = (gamestate *)fixture;
    initGame(game);
    for (int i = 0; i < MAX_PLAYERS - 1; i++)
    {
        game->players[i].bankrupt = true;
    }
    munit_assert_true(checkForGameOver(game));
    return MUNIT_OK;
}

MunitResult rollDice_test(const MunitParameter params[], void *fixture)
{
    gamestate *game = (gamestate *)fixture;
    initGame(game);
    diceRoll diceroll = rollDice(game);
    munit_assert_int(diceroll.die1, >=, 1);
    munit_assert_int(diceroll.die1, <=, 6);
    munit_assert_int(diceroll.die2, >=, 1);
    munit_assert_int(diceroll.die2, <=, 6);
    return MUNIT_OK;
}

MunitResult payIncomeTax_test(const MunitParameter params[], void *fixture)
{
    gamestate *game = (gamestate *)fixture;
    initGame(game);
    payIncomeTax(&game->players[0], game);
    munit_assert_int(game->players[0].money, ==, 1300);
    return MUNIT_OK;
}

MunitResult goToJail_test(const MunitParameter params[], void *fixture)
{
    gamestate *game = (gamestate *)fixture;
    initGame(game);
    goToJail(&game->players[1], game);
    munit_assert_true(game->players[1].inJail);
    return MUNIT_OK;
}

MunitResult payRent_test(const MunitParameter params[], void *fixture)
{
    gamestate *game = (gamestate *)fixture;
    initGame(game);
    game->board[KentuckyAvenue].data.property.owner = Player2;
    payRent(&game->players[3], &game->board[KentuckyAvenue], game);
    munit_assert_int(game->players[3].money, ==, 1500 - game->board[KentuckyAvenue].data.property.coloredProperty.rent[0]);
    munit_assert_int(game->players[1].money, ==, 1500 + game->board[KentuckyAvenue].data.property.coloredProperty.rent[0]);
    return MUNIT_OK;
}

MunitResult payProperty_test(const MunitParameter params[], void *fixture)
{
    gamestate *game = (gamestate *)fixture;
    initGame(game);
    buyProperty(&game->players[0], &game->board[VentnorAvenue], game);
    munit_assert_int(game->players[0].money, ==, 1500 - game->board[VentnorAvenue].data.property.price);
    munit_assert_int(game->board[VentnorAvenue].data.property.owner, ==, Player1);
    return MUNIT_OK;
}

MunitResult sellProperty_test(const MunitParameter params[], void *fixture)
{
    gamestate *game = (gamestate *)fixture;
    initGame(game);
    game->board[BAndORailRoad].data.property.owner = Player1;
    sellProperty(&game->players[0], &game->board[BAndORailRoad], game);
    munit_assert_int(game->players[0].money, ==, 1500 + game->board[BAndORailRoad].data.property.price);
    munit_assert_int(game->board[BAndORailRoad].data.property.owner, ==, Bank);
    return MUNIT_OK;
}

MunitResult mortgageProperty_test(const MunitParameter params[], void *fixture)
{
    gamestate *game = (gamestate *)fixture;
    initGame(game);
    mortgageProperty(&game->players[2], &game->board[PennsylvaniaAvenue], game);
    munit_assert_int(game->players[2].money, ==, 1500 + game->board[PennsylvaniaAvenue].data.property.mortgageValue);
    munit_assert_true(game->board[PennsylvaniaAvenue].data.property.mortgaged);
    return MUNIT_OK;
}

MunitResult unMortgageProperty_test(const MunitParameter params[], void *fixture)
{
    gamestate *game = (gamestate *)fixture;
    initGame(game);
    unmortgageProperty(&game->players[2], &game->board[NorthCarolinaAvenue], game);
    munit_assert_int(game->players[2].money, ==, 1500 - game->board[NorthCarolinaAvenue].data.property.mortgageValue * 1.1);
    munit_assert_false(game->board[NorthCarolinaAvenue].data.property.mortgaged);
    return MUNIT_OK;
}

MunitResult payPlayer_test(const MunitParameter params[], void *fixture)
{
    gamestate *game = (gamestate *)fixture;
    initGame(game);
    payPlayer(&game->players[0], &game->players[1], 100, game);
    munit_assert_int(game->players[0].money, ==, 1500 - 100);
    munit_assert_int(game->players[1].money, ==, 1500 + 100);
    return MUNIT_OK;
}

MunitResult payMoney_test(const MunitParameter params[], void *fixture)
{
    gamestate *game = (gamestate *)fixture;
    initGame(game);
    payMoney(&game->players[0], 257, game);
    munit_assert_int(game->players[0].money, ==, 1500 - 257);
    return MUNIT_OK;
}

MunitResult receiveMoney_test(const MunitParameter params[], void *fixture)
{
    gamestate *game = (gamestate *)fixture;
    initGame(game);
    receiveMoney(&game->players[0], 149, game);
    munit_assert_int(game->players[0].money, ==, 1500 + 149);
    return MUNIT_OK;
}

MunitResult payJailFine_test(const MunitParameter params[], void *fixture)
{
    gamestate *game = (gamestate *)fixture;
    initGame(game);
    payJailFine(&game->players[0], game);
    munit_assert_int(game->players[0].money, ==, 1500 - 50);
    return MUNIT_OK;
}

MunitResult passGo_test(const MunitParameter params[], void *fixture)
{
    gamestate *game = (gamestate *)fixture;
    initGame(game);
    passGo(&game->players[0], game);
    munit_assert_int(game->players[0].money, ==, 1500 + 200);
    return MUNIT_OK;
}

MunitResult bankruptPlayer_test(const MunitParameter params[], void *fixture)
{
    gamestate *game = (gamestate *)fixture;
    initGame(game);
    bankruptPlayer(&game->players[0], game);
    munit_assert_true(game->players[0].bankrupt);
    return MUNIT_OK;
}

MunitResult buyHouse_test(const MunitParameter params[], void *fixture)
{
    gamestate *game = (gamestate *)fixture;
    initGame(game);
    buyHouse(&game->players[0], &game->board[StCharlesPlace], game);
    munit_assert_int(game->players[0].money, ==, 1500 - game->board[StCharlesPlace].data.property.coloredProperty.houseCost);
    munit_assert_int(game->board[StCharlesPlace].data.property.coloredProperty.houseCount, ==, 1);
    return MUNIT_OK;
}

MunitResult buyHotel_test(const MunitParameter params[], void *fixture)
{
    gamestate *game = (gamestate *)fixture;
    initGame(game);
    buyHotel(&game->players[0], &game->board[StCharlesPlace], game);
    munit_assert_int(game->players[0].money, ==, 1500 - game->board[StCharlesPlace].data.property.coloredProperty.hotelCost);
    munit_assert_int(game->board[StCharlesPlace].data.property.coloredProperty.hotelCount, ==, 1);
    return MUNIT_OK;
}

MunitResult sellHouse_test(const MunitParameter params[], void *fixture)
{
    gamestate *game = (gamestate *)fixture;
    initGame(game);
    game->board[StCharlesPlace].data.property.coloredProperty.houseCount = 1;
    sellHouse(&game->players[0], &game->board[StCharlesPlace], game);
    munit_assert_int(game->players[0].money, ==, 1500 + game->board[StCharlesPlace].data.property.coloredProperty.houseCost / 2);
    munit_assert_int(game->board[StCharlesPlace].data.property.coloredProperty.houseCount, ==, 0);
    return MUNIT_OK;
}

MunitResult sellHotel_test(const MunitParameter params[], void *fixture)
{
    gamestate *game = (gamestate *)fixture;
    initGame(game);
    game->board[StCharlesPlace].data.property.coloredProperty.hotelCount = 1;
    sellHotel(&game->players[0], &game->board[StCharlesPlace], game);
    munit_assert_int(game->players[0].money, ==, 1500 + game->board[StCharlesPlace].data.property.coloredProperty.hotelCost / 2);
    munit_assert_int(game->board[StCharlesPlace].data.property.coloredProperty.hotelCount, ==, 0);
    return MUNIT_OK;
}

static void *
game_setup(const MunitParameter params[], void *user_data)
{
    return malloc(sizeof(gamestate));
}

static void
game_tear_down(void *fixture)
{
    free(fixture);
}

MunitTest tests[] = {
    {
        "/my-test",             /* name */
        my_test,                /* test */
        test_setup,             /* setup */
        test_tear_down,         /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/initgame",            /* name */
        initGame_test,          /* test */
        game_setup,             /* setup */
        game_tear_down,         /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/checkforgameover",    /* name */
        checkForGameOver_test,  /* test */
        game_setup,             /* setup */
        game_tear_down,         /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/rolldice",            /* name */
        rollDice_test,          /* test */
        game_setup,             /* setup */
        game_tear_down,         /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/payincometax",        /* name */
        payIncomeTax_test,      /* test */
        game_setup,             /* setup */
        game_tear_down,         /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/gotojail",            /* name */
        goToJail_test,          /* test */
        game_setup,             /* setup */
        game_tear_down,         /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/payrent",             /* name */
        payRent_test,           /* test */
        game_setup,             /* setup */
        game_tear_down,         /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/payproperty",         /* name */
        payProperty_test,       /* test */
        game_setup,             /* setup */
        game_tear_down,         /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/sellproperty",        /* name */
        sellProperty_test,      /* test */
        game_setup,             /* setup */
        game_tear_down,         /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/mortgageproperty",    /* name */
        mortgageProperty_test,  /* test */
        game_setup,             /* setup */
        game_tear_down,         /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/unmortgageproperty",   /* name */
        unMortgageProperty_test, /* test */
        game_setup,              /* setup */
        game_tear_down,          /* tear_down */
        MUNIT_TEST_OPTION_NONE,  /* options */
        NULL                     /* parameters */
    },
    {
        "/payPlayer",           /* name */
        payPlayer_test,         /* test */
        game_setup,             /* setup */
        game_tear_down,         /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/paymoney",            /* name */
        payMoney_test,          /* test */
        game_setup,             /* setup */
        game_tear_down,         /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/receivemoney",        /* name */
        receiveMoney_test,      /* test */
        game_setup,             /* setup */
        game_tear_down,         /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/payjailfine",         /* name */
        payJailFine_test,       /* test */
        game_setup,             /* setup */
        game_tear_down,         /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/passgo",              /* name */
        passGo_test,            /* test */
        game_setup,             /* setup */
        game_tear_down,         /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/bankruptplayer",      /* name */
        bankruptPlayer_test,    /* test */
        game_setup,             /* setup */
        game_tear_down,         /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/buyHouse",            /* name */
        buyHouse_test,          /* test */
        game_setup,             /* setup */
        game_tear_down,         /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/sellHouse",           /* name */
        sellHouse_test,         /* test */
        game_setup,             /* setup */
        game_tear_down,         /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/buyHotel",            /* name */
        buyHotel_test,          /* test */
        game_setup,             /* setup */
        game_tear_down,         /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/sellHotel",           /* name */
        sellHotel_test,         /* test */
        game_setup,             /* setup */
        game_tear_down,         /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },

    /* Mark the end of the array with an entry where the test
     * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/my-tests",            /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[])
{
    return munit_suite_main(&suite, "Hello, world!", argc, (char **)argv);
}