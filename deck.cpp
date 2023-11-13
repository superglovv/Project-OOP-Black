#include "deck.h"
#include <random>

Deck::Deck() {
    for (int suit = static_cast<int>(Card::Suit::Hearts); suit <= static_cast<int>(Card::Suit::Spades); ++suit) {
        for (int rank = static_cast<int>(Card::Rank::Two); rank <= static_cast<int>(Card::Rank::Ace); ++rank) {
            cards.emplace_back(static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit));
        }
    }
}

void Deck::shuffle() {
    unsigned int size = cards.size();
    static std::random_device rd;
    static std::mt19937 gen(rd());

    for (unsigned int i = 0; i < size - 1; i++) {
        static std::uniform_int_distribution<unsigned int> distribution(i, size - 1);
        unsigned int j = distribution(gen);
        std::swap(cards[i], cards[j]);
    }
}

Card Deck::deal() {
    if (!cards.empty()) {
        Card top_card = cards.back();
        cards.pop_back();
        return top_card;
    } else {
        return {Card::Rank::Two, Card::Suit::Hearts};
    }
}

