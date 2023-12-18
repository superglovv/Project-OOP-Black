#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <random>
#include "player.h"
#include "deck.h"
#include <memory>

class Game {
private:
    std::vector<std::shared_ptr<Player>> players;
public:
    explicit Game(std::vector<std::shared_ptr<Player>>& players);

    ~Game() = default;

    void startGame(int mode);

private:
    void gamePlay(int mode);
    void handleWinner(int winnerIndex, const std::vector<int>& totalBet, bool& ended);
};
