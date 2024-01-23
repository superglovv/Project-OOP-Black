#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "player.h"
#include "deck2.h"
#include <memory>
#include "game.h"

enum Choices {
    Hit,
    Stand
};

Game::Game(std::vector<std::shared_ptr<Player>>& players) : players(players) {}

void Game::giveRole(int mode) {
    if (mode == 0){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> role_dist(0, 1);

        Role random_role1 = (role_dist(gen) == 0) ? Role::Player : Role::Dealer;
        Role random_role2 = (random_role1 == Role::Player) ? Role::Dealer : Role::Player;


        players[0]->setRole(random_role1);
        players[1]->setRole(random_role2);
    }
}

void Game::resolveRound(int type, const std::vector<int>& totalBet, bool& ended) {
    //type = 2 este pentru aflarea castigatorului la finalul rundei, iar ramura else (sau 1 dupa cum am pus in joc) reprezinta
    //aflarea castigatorului in timpul rundei in cazul in care unul dintre players a depasit scorul de 21 (pierzand automat)
    if(type == 2){
        if (players[1]->getScore() < 21 && players[0]->getScore() < 21) {
            if (players[1]->getScore() > players[0]->getScore()) {
                handleWinner(1, totalBet, ended);
            } else if (players[1]->getScore() < players[0]->getScore()) {
                handleWinner(0, totalBet, ended);
            } else {
                std::cout << "Draw!" << std::endl;
            }
        } else if (players[1]->reachedTarget()) {
            if (players[1]->getRole() == Role::Dealer) {
                handleWinner(1, totalBet, ended);
            } else {
                std::cout << "Draw!" << std::endl;
            }
        } else if (players[0]->reachedTarget()) {
            if (players[0]->getRole() == Role::Dealer) {
                handleWinner(0, totalBet, ended);
            } else {
                std::cout << "Draw!" << std::endl;
            }
        }
    } else {
        if (players[0]->getScore() > 21 && players[1]->getScore() <= 21) {
            handleWinner(1, totalBet, ended);
        } else if (players[1]->getScore() > 21 && players[0]->getScore() <= 21) {
            handleWinner(0, totalBet, ended);
        }
    }
}

void Game::bettingStage(int &hasBet, std::vector<int>& totalBet, bool& bettingFinished) {
    for (int i = 0; i <= 1; i++) {
        try {
            if (hasBet <= 1) {
                std::cout << "\nInitial bet: 50 credits; Wanna bet more?" << std::endl;
                std::cout << "Current player: " << players[i]->getName() << " (choose 'yes' (0) or 'no' (1)): "
                          << std::endl;
                int bettingChoice;

                int betAmount;
                players[i]->makeBet(bettingChoice, betAmount, 0);


                switch (static_cast<Choices>(bettingChoice)) {
                    case Hit:
                        std::cout << "How much do you want to bet: ";
                        players[i]->makeBet(bettingChoice, betAmount, 1);
                        totalBet[i] = totalBet[i] + betAmount;
                        std::cout << "(Chose to bet more)" << std::endl;
                        break;
                    case Stand:
                        std::cout << "(Chose to keep bet)" << std::endl;
                        break;
                }
                std::cout << players[i]->getName() << ", your total bet is: " << totalBet[i] << std::endl;
            }
            hasBet++;

        } catch (const InvalidBet &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    bettingFinished = true;
}

void Game::firstDraw(Deck& deck, Card& card) {
    for (int k=0; k<=1; k++){
        std::cout << players[k]->getName() << " gets: ";
        std::cout << " " << card <<  std::endl;
        if ((card.getRankValue() + 2) > 10){
            if ((card.getRankValue() + 2) == 14){
                if ((players[k]->getScore()+11) <= 21){
                    players[k]->setScore(players[k]->getScore() + 1);
                } else {
                    if ((players[k]->getScore()+1) <= 21){
                        players[k]->setScore(players[k]->getScore() - 9);
                    }
                }

            }players[k]->setScore(players[k]->getScore() + 10);

        } else players[k]->setScore(players[k]->getScore() + card.getRankValue() + 2);
        std::cout << players[k]->getName() << " got the score: " << players[k]->getScore() << std::endl;
        dealerDeals(deck, card);

    }
}

void Game::playingStage(int& playerStands, bool& playerHasStayed, bool& ended, int player, int& nrMoves, Card& card, Deck& deck,  const std::vector<int>& totalBet) {
    for (auto& item : players) {
        if (auto cheater = std::dynamic_pointer_cast<CheaterBot>(item)) {
            cheater->secretMove();
        }
    }
    while (!playerHasStayed && !ended) {
        std::cout << players[player-1]->getName() << ", choose 'hit' (0) or 'stay' (1): ";
        int choice = 0;
        nrMoves++;

        try {
            players[player-1]->makeMove(choice, nrMoves);
        }   catch (const InvalidMove &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }


        switch (static_cast<Choices>(choice)) {
            case Hit:
                std::cout << players[player-1]->getName() << " chose to hit." << std::endl;
                std::cout << players[player-1]->getName() << " gets: ";
                dealerDeals(deck, card);
                std::cout << " " << card << std::endl;
                if ((card.getRankValue() + 2) > 10) {
                    if ((card.getRankValue() + 2) == 14) {
                        if ((players[player-1]->getScore() + 11) <= 21) {
                            players[player-1]->setScore(players[player-1]->getScore() + 1);
                        } else {
                            if ((players[player-1]->getScore() + 1) <= 21) {
                                players[player-1]->setScore(players[player-1]->getScore() - 9);
                            }
                        }

                    }
                    players[player-1]->setScore(players[player-1]->getScore() + 10);

                } else players[player-1]->setScore(players[player-1]->getScore() + card.getRankValue() + 2);
                std::cout << players[player-1]->getName() << " got the score: " << players[player-1]->getScore() << std::endl;
                if (players[player-1]->getScore() == 21){
                    playerHasStayed = true;
                }
                resolveRound(1, totalBet, ended);

                break;
            case Stand:
                std::cout << players[player-1]->getName() << " chose to stay." << std::endl;
                playerHasStayed = true;
                break;
            } playerStands++;
    }
}

void Game::endMatch(const std::vector<int>& totalBet) {
    std::cout << "\nThe match has ended!" << std::endl;

    std::cout << '\n' << totalBet[0] << ", " << totalBet[1] << '\n';
    std::cout << "\n" << players[0]->getName() << "'s Info:" << std::endl;
    std::cout << *players[0];

    std::cout << "\n" << players[1]->getName() << "'s Info:" << std::endl;
    std::cout << *players[1];
}

void Game::dealerDeals(Deck& deck, Card& card) {
    for (auto& player : players) {
        if (auto dealer = std::dynamic_pointer_cast<Dealer>(player)) {
            card = dealer->dealCards(deck);
        }
    }
}

[[maybe_unused]] void Game::gamePlay(int mode, const int& roundNr) {
    Deck& deck = Deck::getInstance();
    std::cout << "Before deck.shuffle()\n";
    std::cout << "Deck size before shuffle: " << deck.getDeckSize() << std::endl;
    deck.shuffle();
    std::cout << "After deck.shuffle()\n";

    Card card(Card::Rank::Two, Card::Suit::Hearts);


    giveRole(mode);

    dealerDeals(deck,card);

    std::cout << "\n!!! Round " << roundNr << " stars !!!" << std::endl;

    for  (int k=0; k<=1; k++){
        players[k]->setScore(0);

        std::cout << "\n" << players[k]->getName() << "'s Info:" << std::endl;
        std::cout << *players[k];

    } std::cout << std::endl;

    firstDraw(deck, card);


    int playerStands = 0; bool ended = false;
    int hasBet = 0; bool bettingFinished = false;
    std::vector<int> totalBet(2);
    totalBet[0] = totalBet[1] = 50;
    for (int player = 1; player <= 2; player++) {
        bool playerHasStayed = false;
        if (!bettingFinished) bettingStage(hasBet, totalBet, bettingFinished);

        std::cout << '\n' << totalBet[0] << ", " << totalBet[1] << '\n';
        std::cout << '\n';

        int nrMoves = 0;
        playingStage(playerStands,playerHasStayed,ended,player,nrMoves,card, deck, totalBet);

    }
    std::cout << '\n' << totalBet[0] << ", " << totalBet[1] << '\n';

    if (playerStands <= 0 || ended) {
        return;
    }

    resolveRound(2, totalBet, ended);
    endMatch(totalBet);
}

[[maybe_unused]] void Game::handleWinner(int winnerIndex, const std::vector<int>& totalBet, bool& ended) {
    std::cout << "\n!!! The winner is: " << players[winnerIndex]->getName() << std::endl;

    if (winnerIndex == 0) {
        players[0]->setCredits(players[0]->getCredits() + totalBet[1]);
        players[1]->setCredits(players[1]->getCredits() - totalBet[1]);
    } else {
        players[0]->setCredits(players[0]->getCredits() - totalBet[0]);
        players[1]->setCredits(players[1]->getCredits() + totalBet[0]);
    }

    ended = true;
}

void Game::startGame(int& mode, int& roundNr, bool& hasStopped) {
    std::cout << "Sa se inteleaga: " << roundNr << "\n";


    if (mode == 1 && roundNr < 2){
        players[0]->setupPlayer(1);
        players[1]->setupPlayer(2);
    } else{
        if (mode == 0) players[0]->setupPlayer(1);
    }

    gamePlay(mode, roundNr);

    while (!hasStopped){
        int choice2;
        roundNr++;
        std::cout << " Choose if you wanna continue (choose 'Go' (0) or 'Stop' (1)): " <<  std::endl;
        std::cin >> choice2;
        switch (static_cast<Choices>(choice2)){
            case Hit:
                if (mode == 1){
                    return;
                }
                gamePlay(mode, roundNr);
                break;
            case Stand:
                hasStopped = true;
                std::cout << "Rezultate finale: \n\n0" << *players[0] << std::endl;
                std::cout << *players[1] << std::endl;
                break;
        }
    }
}