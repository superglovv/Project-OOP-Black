#include "game.h"
#include <vector>

enum Choose {
    Single,
    Multi
};

enum Difficulty {
    Crazybot = 1,
    Paranoiabot =2
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
        int chooseDifficulty;
        std::cout << " Choose difficulty: \n 1) vs Crazy Bot \n 2) vs Paranoia Bot" <<  std::endl;
        std::cin >> chooseDifficulty;
        switch (static_cast<Difficulty>(chooseDifficulty)){
            case Crazybot:
                players.push_back(std::make_shared<CrazyBot>("BOT Krazy"));
                break;
            case Paranoiabot:
                players.push_back(std::make_shared<ParanoiaBot>("BOT Hirohito"));
                break;
            default:
                std::cerr << "!!! Invalid input !!!" << std::endl;
                exit(0);
        }
    }

    Game game(players);

    game.startGame(mode);
    return 0;
}