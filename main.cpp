#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>

class Card {
public:
    enum class Rank { Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace  };
    enum class Suit { Hearts, Diamonds, Clubs, Spades };

    Card(Rank rank, Suit suit) : rank(rank), suit(suit) {}
    ~Card() = default;

    int getRankValue() const {
        return static_cast<int>(rank);
    }

    [[nodiscard]] std::string display() const {
        std::string rank_str;
        switch (rank) {
            case Rank::Two:   rank_str = "Two";   break;
            case Rank::Three: rank_str = "Three"; break;
            case Rank::Four:  rank_str = "Four";  break;
            case Rank::Five:  rank_str = "Five";  break;
            case Rank::Six:  rank_str = "Six";  break;
            case Rank::Seven: rank_str = "Seven"; break;
            case Rank::Eight:  rank_str = "Eight";  break;
            case Rank::Nine:  rank_str = "Nine";  break;
            case Rank::Ten:  rank_str = "Ten";  break;
            case Rank::Jack: rank_str = "Jack"; break;
            case Rank::Queen:  rank_str = "Queen";  break;
            case Rank::King:  rank_str = "King";  break;
            case Rank::Ace:  rank_str = "Ace";  break;
        }

        std::string suit_str;
        switch (suit) {
            case Suit::Hearts:   suit_str = "Hearts";   break;
            case Suit::Diamonds: suit_str = "Diamonds"; break;
            case Suit::Clubs:    suit_str = "Clubs";    break;
            case Suit::Spades:   suit_str = "Spades";   break;
        }

        return rank_str + " of " + suit_str;
    }

private:
    Rank rank;
    Suit suit;
};


class Deck {
public:
    Deck() {
        for (int suit = static_cast<int>(Card::Suit::Hearts); suit <= static_cast<int>(Card::Suit::Spades); ++suit) {
            for (int rank = static_cast<int>(Card::Rank::Two); rank <= static_cast<int>(Card::Rank::Ace); ++rank) {
                cards.emplace_back(static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit));
            }
        }
    }
    ~Deck() = default;

    void shuffle() {
        int size = cards.size();
        std::random_device rd;
        std::mt19937 gen(rd());

        for (int i = 0; i < size - 1; i++) {
            std::uniform_int_distribution<int> distribution(i, size - 1);
            int j = distribution(gen);
            std::swap(cards[i], cards[j]);
        }
    }

    Card deal() {
        if (!cards.empty()) {
            Card top_card = cards.back();
            cards.pop_back();
            return top_card;
        } else {
            return Card(Card::Rank::Two, Card::Suit::Hearts);
        }
    }

private:
    std::vector<Card> cards;
};


enum class Role { Player, Dealer };

class Player {
public:
    Player(std::string initial_name = "Unknown", int initial_credits = 1000, Role player_role = Role::Player, int player_score = 0)
            : name(initial_name), credits(initial_credits), role(player_role), score(player_score) {}

    Player(const Player& other) {
        name = other.name;
        credits = other.credits;
        role = other.role;
        score = other.score;
    }

    ~Player() = default;

    int getCredits() const {
        return credits;
    }

    int getScore() const {
        return score;
    }

    void setScore (const int& new_score){
        score = new_score;
    }

    std::string getName() const {
        return name;
    }

    void setName(const std::string& new_name) {
        name = new_name;
    }

    Role getRole() const {
        return role;
    }

    void setRole(Role new_role){
        role = new_role;
    }

    void displayInfo() const {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Role: " << (role == Role::Player ? "Player" : "Dealer") << std::endl;
        std::cout << "Score: " << score << std::endl;
        std::cout << "Credits: " << credits << std::endl;

    }

private:
    int credits, score;
    std::string name;
    Role role;
};


int main() { bool sessionEnd = false;
    int nr = 1;
    while (!sessionEnd){
        Deck deck;
        deck.shuffle();


        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> role_dist(0, 1);

        Role random_role1 = (role_dist(gen) == 0) ? Role::Player : Role::Dealer;
        Role random_role2 = (random_role1 == Role::Player) ? Role::Dealer : Role::Player;


        std::vector<Player> players(2);
        players[0].setRole(random_role1);
        players[1].setRole(random_role2);
        std::string name_insert;
        std::cout << "First player's name: ";
        std::cin >> name_insert;
        players[0].setName(name_insert);
        std::cout << "\nSecond player's name: ";
        std::cin >> name_insert;
        players[1].setName(name_insert);

        std::cout << "\nPlayer 1 Info:" << std::endl;
        players[0].displayInfo();

        std::cout << "\nPlayer 2 Info:" << std::endl;
        players[1].displayInfo();

//    std::cout << "\nPlayer 3 Info:" << std::endl;
//    player3.displayInfo();



        std::cout << std::endl;

        enum Choices {
            Hit,
            Stand
        };

        enum Continue {
            Go,
            Stop
        };

        std::cout << "Player 1 gets: ";
        Card card = deck.deal();
        std::cout << " " << card.display() <<  std::endl;
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
        std::cout << "Player 1 got the score: " << players[0].getScore() << std::endl;

        std::cout << "Player 2 gets: ";
        card = deck.deal();
        std::cout << " " << card.display() <<  std::endl;
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
        std::cout << "Player 2 got the score: " << players[1].getScore() << std::endl;
        int playerStands = 0; bool ended = false;
        for (int player = 1; player <= 2; player++) {
            bool playerHasStayed = false;

            while (!playerHasStayed && !ended) {
                std::cout << "Player " << player << ", choose 'hit' (0) or 'stay' (1): ";
                int choice;
                std::cin >> choice;

                switch (static_cast<Choices>(choice)) {
                    case Hit:
                        std::cout << "Player " << player << " chose to hit." << std::endl;
                        std::cout << "Player " << player << " gets: ";
                        card = deck.deal();
                        std::cout << " " << card.display() << std::endl;
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
                        std::cout << "Player " << player << " got the score: " << players[player-1].getScore() << std::endl;
                        if (players[player-1].getScore() == 21){
                            playerHasStayed = true;
                        }

                        if(players[0].getScore() > 21 && players[1].getScore() <= 21 ){
                            std::cout << "The winner is Player 2 #3" << std::endl;
                            ended = true;
                        }else{
                            if(players[1].getScore() > 21 && players[0].getScore() <= 21){
                                std::cout << "The winner is Player 1 #4" << std::endl;
                                ended = true;
                            }
                        }



                        break;
                    case Stand:
                        std::cout << "Player " << player << " chose to stay." << std::endl;
                        playerHasStayed = true;
                        break;
                    default:
                        std::cout << "Invalid choice for Player " << player << ". Please choose 'hit' (0) or 'stay' (1)." << std::endl;
                } playerStands++;

            }

        }
        if(players[1].getScore() < 21 && players[0].getScore() <21 && players[1].getScore()>players[0].getScore() && playerStands > 0 && !ended){
            std::cout << "The winner is Player 2 #5" << std::endl;
        }else if(players[1].getScore() < 21 && players[0].getScore() <21 && players[1].getScore()<players[0].getScore() && playerStands > 0 && !ended){
            std::cout << "The winner is Player 1 #6" << std::endl;
        }else if(players[1].getScore() == 21 && players[0].getScore() == 21 && players[1].getRole() == Role::Dealer && !ended){
            std::cout << "The winner is Player 2 #7" << std::endl;
        }else if(players[1].getScore() == 21 && players[0].getScore() == 21 && players[1].getRole() == Role::Dealer && !ended) std::cout << "The winner is Player 1 #8" << std::endl;
        else if(players[1].getScore() == 21 && playerStands >= 1) std::cout << "The winner is Player 2 #8" << std::endl;
        else if(players[0].getScore() == 21 && playerStands >= 1) std::cout << "The winner is Player 1 #9" << std::endl;

        if(players[1].getScore() == players[0].getScore() && playerStands > 0) std::cout << "Draw!" <<std::endl;
        std::cout << "The match has ended!" ;

        nr++;
        int choice2;
        std::cout << " Choose if you wanna continue (choose 'Go' (0) or 'Stop' (1)): " <<  std::endl;
        std::cin >> choice2;
        switch (static_cast<Continue>(choice2)){
            case Go:
                std::cout << "\nRound " << nr << " begins: " << std::endl;
                break;
            case Stop:
                sessionEnd = true;
                break;
        }

    }
    return 0;
}
