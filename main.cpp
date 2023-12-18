#include "game.h"
#include <vector>

enum Choose {
    Single,
    Multi
};

int main() {
    std::vector<std::shared_ptr<Player>> players;

    int chooseMode;
    std::cout << " Choose to play single-player against bot or multiplayer (choose 'Single' (0) or 'Multi' (1)): " <<  std::endl;
    std::cin >> chooseMode;

    int mode = 1;
    switch (static_cast<Choose>(chooseMode)){
        case Single:
            players.push_back(std::make_shared<Dealer>());
            mode = 0;
            break;
        case Multi:
            players.push_back(std::make_shared<Dealer>());
            players.push_back(std::make_shared<Player>());
            break;
    }


    if (players.size() < 2){
        players.push_back(std::make_shared<CrazyBot>("BOT 1"));
    }

    Game game(players);

    game.startGame(mode);
    return 0;
}