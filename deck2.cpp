#include "deck2.h"

std::random_device Deck::rd;
std::mt19937 Deck::gen(Deck::rd());

Deck::Deck() {
    for (int suit = static_cast<int>(Card::Suit::Hearts); suit <= static_cast<int>(Card::Suit::Spades); ++suit) {
        for (int rank = static_cast<int>(Card::Rank::Two); rank <= static_cast<int>(Card::Rank::Ace); ++rank) {
            cards.emplace_back(static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit));
        }
    }
}

Deck& Deck::getInstance() {
    static Deck instance;
    return instance;
}

void Deck::shuffle() {
    unsigned int size = cards.size();

    for (size_t i = 0; i < size - 1; i++) {
        std::uniform_int_distribution<size_t> distribution(i, size - 1);
        size_t j = distribution(gen);
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

std::size_t Deck::getDeckSize() {
    return cards.size();
}
