#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <random>
#include <memory>
//#include "deck.h"
#include "deck2.h"
#include "card.h"
#include <stdexcept>
#include "exceptions.h"

enum class Role { Player, Dealer };

class Player {
protected:
    Player(std::string initial_name, int initial_credits, Role player_role, int player_score)
            : name(std::move(initial_name)), credits(initial_credits), role(player_role), score(player_score) {}
public:
    explicit Player(std::string initial_name = "Unknown", int initial_credits = 1000, int player_score = 0)
            : Player(std::move(initial_name), initial_credits, Role::Player, player_score) {}

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

    virtual void makeMove(int &choice, [[maybe_unused]] int nrMoves){
        std::cin >> choice;
        if (choice < 0 || choice > 1){
            throw InvalidMove();
        }
    };

    virtual void makeBet(int &bettingChoice, int &betAmount, [[maybe_unused]] int betcase){
        if (betcase == 0){
            std::cin >> bettingChoice;
            betAmount = 0;
        } else {
            std::cin >> betAmount;
            if (betAmount+50 > credits || betAmount < 0) {
                throw InvalidBet();
            }
        }
    };

    friend std::ostream& operator<<(std::ostream& os, const Player& player);

private:
    std::string name;
    int credits;
    Role role;
    int score;
};

class Dealer : public Player {
public:
    explicit Dealer(std::string initial_name = "Dealer", int initial_credits = 1000, int player_score = 0)
            : Player(std::move(initial_name), initial_credits, Role::Dealer, player_score) {}

    static Card dealCards(Deck& deck);

    [[nodiscard]] std::shared_ptr<Player> clone() const override {
        return std::make_shared<Dealer>(*this);
    }
};

class CrazyBot : public Player {
private:
    void makeMove(int &choice, [[maybe_unused]] int nrMoves) override;
    void makeBet(int &bettingChoice, int &betAmount, [[maybe_unused]] int betcase) override;

public:
    explicit CrazyBot(std::string initial_name = "Unknown CrazyBot", int initial_credits = 1000, int player_score = 0)
            : Player(std::move(initial_name), initial_credits, Role::Player, player_score) {}

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
};

class ParanoiaBot : public Player {
private:
    void makeMove(int &choice, [[maybe_unused]] int nrMoves) override;
    void makeBet(int &bettingChoice, int &betAmount, [[maybe_unused]] int betcase) override;

public:
    explicit ParanoiaBot(std::string initial_name = "Unknown CrazyBot", int initial_credits = 1000, int player_score = 0)
            : Player(std::move(initial_name), initial_credits, Role::Player, player_score) {}

    [[nodiscard]] std::shared_ptr<Player> clone() const override {
        return std::make_shared<ParanoiaBot>(*this);
    }
};

class SleepyBot : public Player {
private:
    void makeMove(int &choice, [[maybe_unused]] int nrMoves) override;
    void makeBet(int &bettingChoice, int &betAmount, [[maybe_unused]] int betcase) override;

public:
    explicit SleepyBot(std::string initial_name = "Unknown SleepyBot", int initial_credits = 1000, int player_score = 0)
            : Player(std::move(initial_name), initial_credits, Role::Player, player_score) {}

    [[nodiscard]] std::shared_ptr<Player> clone() const override {
        return std::make_shared<SleepyBot>(*this);
    }
};

class CheaterBot : public Player {
private:
    void makeMove(int &choice, [[maybe_unused]] int nrMoves) override;
    void makeBet(int &bettingChoice, int &betAmount, [[maybe_unused]] int betcase) override;
public:
    explicit CheaterBot(std::string initial_name = "Unknown CrazyBot", int initial_credits = 1000, int player_score = 0)
            : Player(std::move(initial_name), initial_credits, Role::Player, player_score) {}

    [[nodiscard]] std::shared_ptr<Player> clone() const override {
        return std::make_shared<CheaterBot>(*this);
    }

    void secretMove ();
};