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

    static void swap(Game& first, Game& second) {
        using std::swap;
        swap(first.players, second.players);
    }

    Game(const Game& other) {
        for (const auto& player : other.players) {
            if (dynamic_cast<Dealer*>(player.get())) {
                std::cout << "Found a Dealer: " << player->getName() << ", Converting to Player." << std::endl;
                players.push_back(std::make_shared<Player>(player->getName(), player->getCredits(), player->getScore()));
            } else if (dynamic_cast<Player*>(player.get())) {
                std::cout << "Found a Player: " << player->getName() << ", Converting to Dealer." << std::endl;
                players.push_back(std::make_shared<Dealer>(player->getName(), player->getCredits(), player->getScore()));
            }
        }
    }

    Game& operator=(Game other) {
        swap(*this, other);
        return *this;
    }

    ~Game() = default;

    void startGame(int& mode, int& roundNr, bool& hasStopped);

private:
    void giveRole(int mode);
    void resolveRound(int type, const std::vector<int>& totalBet, bool& ended);
    void bettingStage(int &hasBet, std::vector<int>& totalBet, bool& bettingFinished);
    void firstDraw(Deck& deck, Card& card);
    void dealerDeals(Deck& deck, Card& card);
    void playingStage(int& playerStands, bool& playerHasStayed, bool& ended, int player, int& nrMoves, Card& card, Deck& deck, const std::vector<int>& totalBet);
    void endMatch(const std::vector<int>& totalBet);
    void gamePlay(int mode, const int& roundNr);
    void handleWinner(int winnerIndex, const std::vector<int>& totalBet, bool& ended);
};
