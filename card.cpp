#include "card.h"

Card::Card(Rank rank, Suit suit) : rank(rank), suit(suit) {}

[[nodiscard]] int Card::getRankValue() const {
    return static_cast<int>(rank);
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    std::string rank_str;
    switch (card.rank) {
        case Card::Rank::Two:   rank_str = "Two";   break;
        case Card::Rank::Three: rank_str = "Three"; break;
        case Card::Rank::Four:  rank_str = "Four";  break;
        case Card::Rank::Five:  rank_str = "Five";  break;
        case Card::Rank::Six:   rank_str = "Six";   break;
        case Card::Rank::Seven: rank_str = "Seven"; break;
        case Card::Rank::Eight: rank_str = "Eight"; break;
        case Card::Rank::Nine:  rank_str = "Nine";  break;
        case Card::Rank::Ten:   rank_str = "Ten";   break;
        case Card::Rank::Jack:  rank_str = "Jack";  break;
        case Card::Rank::Queen: rank_str = "Queen"; break;
        case Card::Rank::King:  rank_str = "King";  break;
        case Card::Rank::Ace:   rank_str = "Ace";   break;
    }

    std::string suit_str;
    switch (card.suit) {
        case Card::Suit::Hearts:   suit_str = "Hearts";   break;
        case Card::Suit::Diamonds: suit_str = "Diamonds"; break;
        case Card::Suit::Clubs:    suit_str = "Clubs";    break;
        case Card::Suit::Spades:   suit_str = "Spades";   break;
    }

    os << rank_str << " of " << suit_str;
    return os;
}

