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
    // munit_assert_int(Parkplace.name)
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