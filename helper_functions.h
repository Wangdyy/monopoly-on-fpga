bool checkForGameOver(gamestate* game);
struct diceRoll rollDice();

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

void payTax(player* player);

void goToJail(player* player);

void payRent(player* player, propertySquare* property);
