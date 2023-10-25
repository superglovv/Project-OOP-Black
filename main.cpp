#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <random>

class Card {
public:
    enum class Rank { Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace  };
    enum class Suit { Hearts, Diamonds, Clubs, Spades };

    Card(Rank rank, Suit suit) : rank(rank), suit(suit) {}
    ~Card() = default;

    [[nodiscard]] int getRankValue() const {
        return static_cast<int>(rank);
    }

    friend std::ostream& operator<<(std::ostream& os, const Card& card) {
        std::string rank_str;
        switch (card.rank) {
            case Rank::Two:   rank_str = "Two";   break;
            case Rank::Three: rank_str = "Three"; break;
            case Rank::Four:  rank_str = "Four";  break;
            case Rank::Five:  rank_str = "Five";  break;
            case Rank::Six:   rank_str = "Six";   break;
            case Rank::Seven: rank_str = "Seven"; break;
            case Rank::Eight: rank_str = "Eight"; break;
            case Rank::Nine:  rank_str = "Nine";  break;
            case Rank::Ten:   rank_str = "Ten";   break;
            case Rank::Jack:  rank_str = "Jack";  break;
            case Rank::Queen: rank_str = "Queen"; break;
            case Rank::King:  rank_str = "King";  break;
            case Rank::Ace:   rank_str = "Ace";   break;
        }

        std::string suit_str;
        switch (card.suit) {
            case Suit::Hearts:   suit_str = "Hearts";   break;
            case Suit::Diamonds: suit_str = "Diamonds"; break;
            case Suit::Clubs:    suit_str = "Clubs";    break;
            case Suit::Spades:   suit_str = "Spades";   break;
        }

        os << rank_str << " of " << suit_str;
        return os;
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
        unsigned int size = cards.size();
        std::random_device rd;
        std::mt19937 gen(rd());

        for (unsigned int i = 0; i < size - 1; i++) {
            std::uniform_int_distribution<unsigned int> distribution(i, size - 1);
            unsigned int j = distribution(gen);
            std::swap(cards[i], cards[j]);
        }
    }

    Card deal() {
        if (!cards.empty()) {
            Card top_card = cards.back();
            cards.pop_back();
            return top_card;
        } else {
            return {Card::Rank::Two, Card::Suit::Hearts};
        }
    }

private:
    std::vector<Card> cards;
};


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

    void setScore (const int& new_score){
        score = new_score;
    }

    [[nodiscard]] std::string getName() const {
        return name;
    }

    void setName(const std::string& new_name) {
        name = new_name;
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


int main() { bool sessionEnd = false;
    int nr = 1;
    std::vector<Player> players(2);
    std::string name_insert;
    std::cout << "First player's name: ";
    std::cin >> name_insert;
    players[0].setName(name_insert);
    std::cout << "\nSecond player's name: ";
    std::cin >> name_insert;
    players[1].setName(name_insert);
    int totalBet1 = 50, totalBet2 = 50;
    while (!sessionEnd){
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

        enum Choices {
            Hit,
            Stand
        };

        enum Continue {
            Go,
            Stop
        };

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
        for (int player = 1; player <= 2; player++) {
            bool playerHasStayed = false;

            enum Betting {
                Plus,
                Keep
            };




            if (hasBet == 0){
                std::cout << "\nInitial bet: 50 credits; Wanna bet more?" << std::endl;
                std::cout << "Current player: " << players[0].getName() << " (choose 'yes' (0) or 'no' (1)): " << std::endl;
                int bettingChoice;
                std::cin >> bettingChoice;

                int betAmount;

                switch (static_cast<Betting>(bettingChoice)){
                    case Plus:
                        std::cout << "How much do you want to bet, " << players[0].getName()  << "? Available credits: " << players[0].getCredits() << std::endl;
                        std::cin>>betAmount;
                        totalBet1 = totalBet1 + betAmount;
                        break;
                    case Keep:
                        break;
                } std::cout << players[0].getName()  << ", your total bet is: " << totalBet1 << std::endl;

                std::cout << "\nInitial bet: 50 credits; Wanna bet more?" << std::endl;
                std::cout << "Current player: " << players[1].getName() << " (choose 'yes' (0) or 'no' (1)): " << std::endl;
                std::cin >> bettingChoice;

                switch (static_cast<Betting>(bettingChoice)){
                    case Plus:
                        std::cout << "How much do you want to bet, " << players[1].getName()  << "? Available credits: " << players[1].getCredits() << std::endl;
                        std::cin>>betAmount;
                        totalBet2 = totalBet2 + betAmount;
                        break;
                    case Keep:
                        break;
                } std::cout << players[1].getName()  << ", your total bet is: " << totalBet2 << std::endl;
            }
            hasBet++;

            std::cout << '\n' << totalBet1 << ", " << totalBet2 << '\n';
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
                            players[0].setCredits(players[0].getCredits()-totalBet1);
                            players[1].setCredits(players[1].getCredits()+totalBet1);
                            ended = true;
                        }else{
                            if(players[1].getScore() > 21 && players[0].getScore() <= 21){
                                std::cout << "\n!!! The winner is: " << players[0].getName() << "#2" << std::endl;
                                players[0].setCredits(players[0].getCredits()+totalBet2);
                                players[1].setCredits(players[1].getCredits()-totalBet2);
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
        std::cout << '\n' << totalBet1 << ", " << totalBet2 << '\n';


        if(players[1].getScore() < 21 && players[0].getScore() <21 && players[1].getScore()>players[0].getScore() && playerStands > 0 && !ended){
            std::cout << "\n!!! The winner is: " << players[1].getName() << " #3" << std::endl;
            players[0].setCredits(players[0].getCredits()-totalBet1);
            players[1].setCredits(players[1].getCredits()+totalBet1);
            hasBet=0;
        }else if(players[1].getScore() < 21 && players[0].getScore() <21 && players[1].getScore()<players[0].getScore() && playerStands > 0 && !ended){
            std::cout << "\n!!! The winner is: " << players[0].getName() << " #4" << std::endl;
            players[0].setCredits(players[0].getCredits()+totalBet2);
            players[1].setCredits(players[1].getCredits()-totalBet2);
            hasBet=0;
        }else if(players[1].getScore() == 21 && players[0].getScore() == 21 && players[1].getRole() == Role::Dealer){
            std::cout << "\n!!! The winner is: " << players[1].getName() << " #5" << std::endl;
            players[0].setCredits(players[0].getCredits()-totalBet1);
            players[1].setCredits(players[1].getCredits()+totalBet1);
            hasBet=0;
        }else if(players[1].getScore() == 21 && players[0].getScore() == 21 && players[1].getRole() == Role::Dealer && !ended){
            std::cout << "\n!!! The winner is: " << players[0].getName() << " #6" << std::endl;
            players[0].setCredits(players[0].getCredits()+totalBet2);
            players[1].setCredits(players[1].getCredits()-totalBet2);
            hasBet=0;
        }else if(players[1].getScore() == 21 && playerStands >= 1){
            std::cout << "\n!!! The winner is: " << players[1].getName() << " #7" << std::endl;
            players[0].setCredits(players[0].getCredits()-totalBet1);
            players[1].setCredits(players[1].getCredits()+totalBet1);
            hasBet=0;
        } else if(players[0].getScore() == 21 && playerStands >= 1){
            std::cout << "\n!!! The winner is: " << players[0].getName() << " #8" << std::endl;
            players[0].setCredits(players[0].getCredits()+totalBet2);
            players[1].setCredits(players[1].getCredits()-totalBet2);
            hasBet=0;
        }
        if(players[1].getScore() == players[0].getScore() && playerStands > 0) std::cout << "Draw!" <<std::endl;
        std::cout << "\nThe match has ended!" << std::endl;

        std::cout << '\n' << totalBet1 << ", " << totalBet2 << '\n';
        std::cout << "\n" << players[0].getName() << "'s Info:" << std::endl;
        std::cout << players[0];

        std::cout << "\n" << players[1].getName() << "'s Info:" << std::endl;
        std::cout << players[1];

        nr++;
        int choice2;
        std::cout << " Choose if you wanna continue (choose 'Go' (0) or 'Stop' (1)): " <<  std::endl;
        std::cin >> choice2;
        switch (static_cast<Continue>(choice2)){
            case Go:
                std::cout << "\nRound " << nr << " begins: " << std::endl;
                totalBet1 = 50, totalBet2 = 50;
                break;
            case Stop:
                sessionEnd = true;
                break;
        }

    }
    return 0;
}
