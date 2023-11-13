
#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <utility>

class Card {
public:
    enum class Rank { Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };
    enum class Suit { Hearts, Diamonds, Clubs, Spades };

    Card(Rank rank, Suit suit);
    ~Card() = default;

    [[nodiscard]] int getRankValue() const;

    friend std::ostream& operator<<(std::ostream& os, const Card& card);

private:
    Rank rank;
    Suit suit;
};

#endif // CARD_H
