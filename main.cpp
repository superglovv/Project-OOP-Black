#include "game.h"
#include <vector>

enum Choose {
    Single,
    Multi
};

enum Difficulty {
    Crazybot = 1,
    Paranoiabot =2,
    Cheater = 3,
    Sleepybot = 4
};

std::shared_ptr<Player> createPlayer(Difficulty difficulty) {
    switch (difficulty) {
        case Crazybot:
            return std::make_shared<CrazyBot>("BOT Krazy");
        case Paranoiabot:
            return std::make_shared<ParanoiaBot>("BOT Hirohito");
        case Cheater:
            return std::make_shared<CheaterBot>("BOT UMad?");
        case Sleepybot:
            return std::make_shared<SleepyBot>("BOT AmEEPY");
        default:
            throw std::invalid_argument("Invalid player difficulty");
    }
}

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
        std::cout << " Choose difficulty: \n 1) vs Crazy Bot \n 2) vs Paranoia Bot\n 3) vs UMad? Bot\n 4) vs AmEEPY Bot" <<  std::endl;
        std::cin >> chooseDifficulty;
        players.push_back(createPlayer(static_cast<Difficulty>(chooseDifficulty)));
    }

    Game game(players);

    int roundNr = 1; bool hasStopped = false;

    game.startGame(mode, roundNr, hasStopped);

    if (mode == 1){
        Game game2 = game;
        while (!hasStopped){
            if (roundNr % 2 == 0) { game2 = game; game2.startGame(mode, roundNr, hasStopped);}
            else {game = game2; game.startGame(mode, roundNr, hasStopped);}
        }
    }


    return 0;
}