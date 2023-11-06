#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <random>

enum class Role { Player, Dealer };

class Player {
public:
    explicit Player(std::string initial_name = "Unknown", int initial_credits = 1000, Role player_role = Role::Player, int player_score = 0)
            : name(std::move(initial_name)), credits(initial_credits), role(player_role), score(player_score) {}

    Player& operator=(const Player& other) {
        if (this != &other) {
            name = other.name;
            credits = other.credits;
            role = other.role;
            score = other.score;
        }
        return *this;
    }

    ~Player() = default;

    [[nodiscard]] int getCredits() const {
        return credits;
    }

    void setCredits (const int& new_credits){
        credits = new_credits;
    }

    [[nodiscard]] int getScore() const {
        return score;
    }

    [[nodiscard]] int reachedTarget() const {
        if (score == 21)
            return 1;
        return 0;
    }

    void setupPlayer(){
        std::string name_insert;
        std::cout << "Player's name: ";
        std::cin >> name_insert;
        name = name_insert;
    }

    void setScore (const int& new_score){
        score = new_score;
    }

    [[nodiscard]] std::string getName() const {
        return name;
    }


    [[nodiscard]] Role getRole() const {
        return role;
    }

    void setRole(Role new_role){
        role = new_role;
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& player) {
        os << "Name: " << player.name << std::endl;
        os << "Role: " << (player.role == Role::Player ? "Player" : "Dealer") << std::endl;
        os << "Score: " << player.score << std::endl;
        os << "Credits: " << player.credits << std::endl;
        return os;
    }

private:
    std::string name;
    int credits;
    Role role;
    int score;
};