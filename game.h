#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <random>
#include "player.h"
#include "deck.h"

enum Choices {
    Hit,
    Stand
};

class Game {
private:
    std::vector<Player> players;
public:
    explicit Game(std::vector<Player>& players);

    ~Game() = default;

    void gamePlay() {
        Deck deck;
        deck.shuffle();

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> role_dist(0, 1);

        Role random_role1 = (role_dist(gen) == 0) ? Role::Player : Role::Dealer;
        Role random_role2 = (random_role1 == Role::Player) ? Role::Dealer : Role::Player;


        players[0].setRole(random_role1);
        players[1].setRole(random_role2);


        players[0].setScore(0);
        players[1].setScore(0);

        std::cout << "\n" << players[0].getName() << "'s Info:" << std::endl;
        std::cout << players[0];

        std::cout << "\n" << players[1].getName() << "'s Info:" << std::endl;
        std::cout << players[1];

        std::cout << std::endl;

        std::cout << players[0].getName() << " gets: ";
        Card card = deck.deal();
        std::cout << " " << card <<  std::endl;
        if ((card.getRankValue() + 2) > 10){
            if ((card.getRankValue() + 2) == 14){
                if ((players[0].getScore()+11) <= 21){
                    players[0].setScore(players[0].getScore() + 1);
                } else {
                    if ((players[0].getScore()+1) <= 21){
                        players[0].setScore(players[0].getScore() - 9);
                    }
                }

            }players[0].setScore(players[0].getScore() + 10);

        } else players[0].setScore(players[0].getScore() + card.getRankValue() + 2);
        std::cout << players[0].getName() << " got the score: " << players[0].getScore() << std::endl;

        std::cout << players[1].getName() << " gets: ";
        card = deck.deal();
        std::cout << " " << card <<  std::endl;
        if ((card.getRankValue() + 2) > 10){
            if ((card.getRankValue() + 2) == 14){
                if ((players[1].getScore()+11) <= 21){
                    players[1].setScore(players[1].getScore() + 1);
                } else {
                    if ((players[1].getScore()+1) <= 21){
                        players[1].setScore(players[1].getScore() - 9);
                    }
                }

            }players[1].setScore(players[1].getScore() + 10);

        } else players[1].setScore(players[1].getScore() + card.getRankValue() + 2);
        std::cout << players[1].getName() << " got the score: " << players[1].getScore() << std::endl;
        int playerStands = 0; bool ended = false;
        int hasBet = 0;
        std::vector<int> totalBet(2);
        totalBet[0] = totalBet[1] = 50;
        for (int player = 1; player <= 2; player++) {
            bool playerHasStayed = false;

            for (int i=0; i<=1; i++) {
                if (hasBet <= 1) {
                    std::cout << "\nInitial bet: 50 credits; Wanna bet more?" << std::endl;
                    std::cout << "Current player: " << players[i].getName() << " (choose 'yes' (0) or 'no' (1)): "
                              << std::endl;
                    int bettingChoice;
                    std::cin >> bettingChoice;

                    int betAmount;

                    switch (static_cast<Choices>(bettingChoice)) {
                        case Hit:
                            std::cout << "How much do you want to bet, " << players[i].getName()
                                      << "? Available credits: " << players[i].getCredits() << std::endl;
                            std::cin >> betAmount;
                            totalBet[i] = totalBet[i] + betAmount;
                            break;
                        case Stand:
                            break;
                    }
                    std::cout << players[i].getName() << ", your total bet is: " << totalBet[i] << std::endl;
                }hasBet++;
            }


            std::cout << '\n' << totalBet[0] << ", " << totalBet[1] << '\n';
            std::cout << '\n';

            while (!playerHasStayed && !ended) {
                std::cout << players[player-1].getName() << ", choose 'hit' (0) or 'stay' (1): ";
                int choice;
                std::cin >> choice;

                switch (static_cast<Choices>(choice)) {
                    case Hit:
                        std::cout << players[player-1].getName() << " chose to hit." << std::endl;
                        std::cout << players[player-1].getName() << " gets: ";
                        card = deck.deal();
                        std::cout << " " << card << std::endl;
                        if ((card.getRankValue() + 2) > 10) {
                            if ((card.getRankValue() + 2) == 14) {
                                if ((players[player-1].getScore() + 11) <= 21) {
                                    players[player-1].setScore(players[player-1].getScore() + 1);
                                } else {
                                    if ((players[player-1].getScore() + 1) <= 21) {
                                        players[player-1].setScore(players[player-1].getScore() - 9);
                                    }
                                }

                            }
                            players[player-1].setScore(players[player-1].getScore() + 10);

                        } else players[player-1].setScore(players[player-1].getScore() + card.getRankValue() + 2);
                        std::cout << players[player-1].getName() << " got the score: " << players[player-1].getScore() << std::endl;
                        if (players[player-1].getScore() == 21){
                            playerHasStayed = true;
                        }


                        if(players[0].getScore() > 21 && players[1].getScore() <= 21 ){
                            std::cout << "\n!!! The winner is: " << players[1].getName() << " #1" << std::endl;
                            players[0].setCredits(players[0].getCredits()-totalBet[0]);
                            players[1].setCredits(players[1].getCredits()+totalBet[0]);
                            ended = true;
                        }else{
                            if(players[1].getScore() > 21 && players[0].getScore() <= 21){
                                std::cout << "\n!!! The winner is: " << players[0].getName() << "#2" << std::endl;
                                players[0].setCredits(players[0].getCredits()+totalBet[1]);
                                players[1].setCredits(players[1].getCredits()-totalBet[1]);
                                ended = true;
                            }
                        }



                        break;
                    case Stand:
                        std::cout << players[player-1].getName() << " chose to stay." << std::endl;
                        playerHasStayed = true;
                        break;
                    default:
                        std::cout << "Invalid choice for Player " << player << ". Please choose 'hit' (0) or 'stay' (1)." << std::endl;
                } playerStands++;

            }

        }
        std::cout << '\n' << totalBet[0] << ", " << totalBet[1] << '\n';


        if(players[1].getScore() < 21 && players[0].getScore() <21 && players[1].getScore()>players[0].getScore() && playerStands > 0 && !ended){
            std::cout << "\n!!! The winner is: " << players[1].getName() << " #3" << std::endl;
            players[0].setCredits(players[0].getCredits()-totalBet[0]);
            players[1].setCredits(players[1].getCredits()+totalBet[0]);
        }else if(players[1].getScore() < 21 && players[0].getScore() <21 && players[1].getScore()<players[0].getScore() && playerStands > 0 && !ended){
            std::cout << "\n!!! The winner is: " << players[0].getName() << " #4" << std::endl;
            players[0].setCredits(players[0].getCredits()+totalBet[1]);
            players[1].setCredits(players[1].getCredits()-totalBet[1]);
        }else if(players[1].reachedTarget() && players[0].reachedTarget() && players[1].getRole() == Role::Dealer){
            std::cout << "\n!!! The winner is: " << players[1].getName() << " #5" << std::endl;
            players[0].setCredits(players[0].getCredits()-totalBet[0]);
            players[1].setCredits(players[1].getCredits()+totalBet[0]);
        }else if(players[1].reachedTarget() && players[0].reachedTarget() && players[1].getRole() == Role::Dealer && !ended){
            std::cout << "\n!!! The winner is: " << players[0].getName() << " #6" << std::endl;
            players[0].setCredits(players[0].getCredits()+totalBet[1]);
            players[1].setCredits(players[1].getCredits()-totalBet[1]);
        }else if(players[1].reachedTarget() && playerStands >= 1){
            std::cout << "\n!!! The winner is: " << players[1].getName() << " #7" << std::endl;
            players[0].setCredits(players[0].getCredits()-totalBet[0]);
            players[1].setCredits(players[1].getCredits()+totalBet[0]);
        } else if(players[0].reachedTarget() && playerStands >= 1){
            std::cout << "\n!!! The winner is: " << players[0].getName() << " #8" << std::endl;
            players[0].setCredits(players[0].getCredits()+totalBet[1]);
            players[1].setCredits(players[1].getCredits()-totalBet[1]);
        }
        if(players[1].getScore() == players[0].getScore() && playerStands > 0) std::cout << "Draw!" <<std::endl;
        std::cout << "\nThe match has ended!" << std::endl;

        std::cout << '\n' << totalBet[0] << ", " << totalBet[1] << '\n';
        std::cout << "\n" << players[0].getName() << "'s Info:" << std::endl;
        std::cout << players[0];

        std::cout << "\n" << players[1].getName() << "'s Info:" << std::endl;
        std::cout << players[1];


    }

    void startGame(){
        bool hasStopped = false;
        Dealer dealer;
        Bot bot;
        Human human;

        dealer.display();
        bot.display();
        human.display();

        players[0].setupPlayer();
        players[1].setupPlayer();
        int nr = 1;
        gamePlay();

        while (!hasStopped){
            nr++;
            int choice2;
            std::cout << " Choose if you wanna continue (choose 'Go' (0) or 'Stop' (1)): " <<  std::endl;
            std::cin >> choice2;
            switch (static_cast<Choices>(choice2)){
                case Hit:
                    std::cout << "\nRound " << nr << " begins: " << std::endl;
                    gamePlay();
                    break;
                case Stand:
                    hasStopped = true;
                    break;
            }
        }
    }

};

Game::Game(std::vector<Player>& players) : players(players) {}



