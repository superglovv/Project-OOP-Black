#ifndef DECK_H
#define DECK_H

#include <vector>
#include "card.h"
#include <random>

class Deck {
public:
    static Deck& getInstance(); // Singleton method

    ~Deck() = default;

    void shuffle();
    Card deal();
    std::size_t getDeckSize();

private:
    Deck();

    std::vector<Card> cards;
    static std::random_device rd;
    static std::mt19937 gen;
};

#endif
