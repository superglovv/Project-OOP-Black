#ifndef DECK_H
#define DECK_H

#include <vector>
#include "card.h"
#include <random>

class Deck {
public:
    Deck();
    ~Deck() = default;

    void shuffle();
    Card deal();

private:
    std::vector<Card> cards;
    static std::random_device rd;
    static std::mt19937 gen;

};

#endif
