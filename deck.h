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
        static std::random_device rd;
        static std::mt19937 gen(rd());

        for (unsigned int i = 0; i < size - 1; i++) {
            static std::uniform_int_distribution<unsigned int> distribution(i, size - 1);
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