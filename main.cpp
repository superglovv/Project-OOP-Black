#include "game.h"

int main() {
    std::vector<Player> players(2);
    Game game(players);

    game.startGame();
    return 0;
}