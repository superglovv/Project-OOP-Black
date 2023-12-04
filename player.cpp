#include "player.h"

Player::Player(std::string initial_name, int initial_credits, Role player_role, int player_score)
        : name(std::move(initial_name)), credits(initial_credits), role(player_role), score(player_score) {}

Player& Player::operator=(const Player& other) {
    if (this != &other) {
        name = other.name;
        credits = other.credits;
        role = other.role;
        score = other.score;
    }
    return *this;
}

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

void Player::setupPlayer() {
    std::string name_insert;
    std::cout << "Player's name: ";
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

