#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <random>
#include <memory>

enum class Role { Player, Dealer };

class Player {
public:
    explicit Player(std::string initial_name = "Unknown", int initial_credits = 1000, Role player_role = Role::Player, int player_score = 0);
//    Player& operator=(const Player& other);
    virtual ~Player() = default;

    [[maybe_unused]] [[nodiscard]] virtual std::shared_ptr<Player> clone() const {
        return std::make_shared<Player>(*this);
    }

    [[nodiscard]] int getCredits() const;
    void setCredits(const int& new_credits);

    [[nodiscard]] int getScore() const;
    [[nodiscard]] int reachedTarget() const;

    void setupPlayer(int pnr);
    void setScore(const int& new_score);

    [[nodiscard]] std::string getName() const;
    [[nodiscard]] Role getRole() const;
    void setRole(Role new_role);

//    virtual int makeMove(int choice){
//        std::cin >> choice;
//        return choice;
//    };

//
//    virtual void display() const;

    friend std::ostream& operator<<(std::ostream& os, const Player& player);

private:
    std::string name;
    int credits;
    Role role;
    int score;
};

class Dealer : public Player {
public:
    explicit Dealer(std::string initial_name = "Dealer", int initial_credits = 1000, Role player_role = Role::Dealer, int player_score = 0)
            : Player(std::move(initial_name), initial_credits, player_role, player_score) {}

    [[nodiscard]] std::shared_ptr<Player> clone() const override {
        return std::make_shared<Dealer>(*this);
    }
//
//    static std::string roleToString(Role role) {
//        switch (role) {
//            case Role::Player:
//                return "Player";
//            case Role::Dealer:
//                return "Dealer";
//        }
//    }
//
//    void display() const override {
//        std::cout << "I AM " << name << ", THE DEALER (SHADY NOISES)\n";
//        std::cout << credits << "\n";
//        std::cout << roleToString(role) << "\n";
//        std::cout << score << "\n";
//    }
};

class CrazyBot : public Player {
public:
    explicit CrazyBot(std::string initial_name = "Unknown CrazyBot", int initial_credits = 1000, Role player_role = Role::Player, int player_score = 0)
    : Player(std::move(initial_name), initial_credits, player_role, player_score) {}

    [[nodiscard]] std::shared_ptr<Player> clone() const override {
        return std::make_shared<CrazyBot>(*this);
    }

    static int randomMove(int &choice) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(0, 1);

        choice = distribution(gen);

        return choice;
    }

//
//    static std::string roleToString(Role role) {
//        switch (role) {
//            case Role::Player:
//                return "Player";
//            case Role::Dealer:
//                return "Dealer";
//        }
//    }
//
//    void display() const override {
//        std::cout << "I AM " << name << ", THE BOT WITH LOTS OF MONEY\n";
//        std::cout << credits << "\n";
//        std::cout << roleToString(role) << "\n";
//        std::cout << score << "\n";
//    }
};

class Human : public Player {
public:
    explicit Human(std::string initial_name = "Human", int initial_credits = 1000, Role player_role = Role::Player, int player_score = 0)
    : Player(std::move(initial_name), initial_credits, player_role, player_score) {}

    [[nodiscard]] std::shared_ptr<Player> clone() const override {
        return std::make_shared<Human>(*this);
    }

//    static std::string roleToString(Role role) {
//        switch (role) {
//            case Role::Player:
//                return "Player";
//            case Role::Dealer:
//                return "Dealer";
//        }
//    }
//
//    void display() const override {
//        std::cout << "I AM " << name << "\n";
//        std::cout << credits << "\n";
//        std::cout << roleToString(role) << "\n";
//        std::cout << score << "\n";
//    }
};