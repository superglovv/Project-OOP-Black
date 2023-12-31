#include "player.h"
#include <thread>
#include <chrono>

int Player::getCredits() const {
    return credits;
}

void Player::setCredits(const int& new_credits) {
    credits = new_credits;
}

int Player::getScore() const {
    return score;
}

int Player::reachedTarget() const {
    return (score == 21) ? 1 : 0;
}

void Player::setupPlayer(int pnr) {
    std::string name_insert;
    std::cout << "\nPlayer " << pnr << "'s name: ";
    std::cin >> name_insert;
    name = name_insert;
}

void Player::setScore(const int& new_score) {
    score = new_score;
}

std::string Player::getName() const {
    return name;
}

Role Player::getRole() const {
    return role;
}

void Player::setRole(Role new_role) {
    role = new_role;
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Name: " << player.name << std::endl;
    os << "Role: " << (player.role == Role::Player ? "Player" : "Dealer") << std::endl;
    os << "Score: " << player.score << std::endl;
    os << "Credits: " << player.credits << std::endl;
    return os;
}

//
//void Player::display() const {}

Card Dealer::dealCards(Deck& deck) {
    deck.shuffle();

    return deck.deal();
}

void CrazyBot::makeMove(int &choice, [[maybe_unused]] int nrMoves) {
    randomMove(choice);
}

void CrazyBot::makeBet(int &bettingChoice, int &betAmount, [[maybe_unused]] int betcase) {
    bettingChoice = 0;
    betAmount = 200;
}

void ParanoiaBot::makeMove(int &choice, [[maybe_unused]] int nrMoves) {
    if(nrMoves < 3) choice=0;
    else choice=1;
}

void ParanoiaBot::makeBet(int &bettingChoice, int &betAmount, [[maybe_unused]] int betcase) {
    bettingChoice = 0;
    betAmount = 350;
}

void CheaterBot::makeBet(int &bettingChoice, int &betAmount, [[maybe_unused]] int betcase) {
    bettingChoice = 0;
    betAmount = -50;
}

void CheaterBot::makeMove(int &choice, [[maybe_unused]] int nrMoves) {
    choice=1;
}

void CheaterBot::secretMove() {
    setScore(21);
}

void SleepyBot::makeBet(int &bettingChoice, [[maybe_unused]] int &betAmount, [[maybe_unused]] int betcase) {
    std::this_thread::sleep_for (std::chrono::seconds(3));
    std::cout << "zZzZ" << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds(3));
    std::cout << "I don't wanna bet!!" << std::endl;
    bettingChoice = 1;
}

void SleepyBot::makeMove(int &choice, [[maybe_unused]] int nrMoves) {
    if(nrMoves < 2){
        std::this_thread::sleep_for (std::chrono::seconds(3));
        std::cout << "zZzZ" << std::endl;
        std::this_thread::sleep_for (std::chrono::seconds(3));
        std::cout << "Gotta make a move already ?!!" << std::endl;
        choice=0;
    }
    else choice=1;
}