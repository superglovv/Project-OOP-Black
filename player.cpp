#include "player.h"

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

int CrazyBot::makeMove(int &choice) {
    return randomMove(choice);
}

void CrazyBot::makeBet(int &bettingChoice, int &betAmount, [[maybe_unused]] int betcase) {
    bettingChoice = 0;
    betAmount = 200;
}

//int ParanoiaBot::makeMove(int &choice) {
//    choice = 0;
//    return choice;
//}
