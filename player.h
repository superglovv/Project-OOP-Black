#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <random>

enum class Role { Player, Dealer };

class Player {
public:
    explicit Player(std::string initial_name = "Unknown", int initial_credits = 1000, Role player_role = Role::Player, int player_score = 0);
    Player& operator=(const Player& other);
    virtual ~Player() = default;

    [[nodiscard]] int getCredits() const;
    void setCredits(const int& new_credits);

    [[nodiscard]] int getScore() const;
    [[nodiscard]] int reachedTarget() const;

    void setupPlayer();
    void setScore(const int& new_score);

    [[nodiscard]] std::string getName() const;
    [[nodiscard]] Role getRole() const;
    void setRole(Role new_role);

    virtual void display() const;

    friend std::ostream& operator<<(std::ostream& os, const Player& player);

private:
    std::string name;
    int credits;
    Role role;
    int score;
};

class Dealer : public Player {
public:
    explicit Dealer(std::string initial_name = "Dealer", int initial_credits = 10000)
            : Player(std::move(initial_name), initial_credits, Role::Dealer) {}

    void display() const override {
        std::cout << "I AM DEALER\n";
    }
};

class Bot : public Player {
public:
    explicit Bot(std::string initial_name = "Bot", int initial_credits = 500)
            : Player(std::move(initial_name), initial_credits, Role::Player) {}

    void display() const override {
        std::cout << "I AM BOT\n";
    }
};

class Human : public Player {
public:
    explicit Human(std::string initial_name = "Human", int initial_credits = 1000)
            : Player(std::move(initial_name), initial_credits, Role::Player) {}

    void display() const override {
        std::cout << "I AM HUMAN\n";
    }
};