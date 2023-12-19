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
    void giveRole(int mode);
    void resolveRound(int type, const std::vector<int>& totalBet, bool& ended);
    void bettingStage(int &hasBet, std::vector<int>& totalBet);
    void firstDraw(Card& card);
    void dealerDeals(Card& card);
    void playingStage(int& playerStands, bool& playerHasStayed, bool& ended, int player, int& nrMoves, Card& card, const std::vector<int>& totalBet);
    void endMatch(const std::vector<int>& totalBet);
    void gamePlay(int mode);
    void handleWinner(int winnerIndex, const std::vector<int>& totalBet, bool& ended);
};
