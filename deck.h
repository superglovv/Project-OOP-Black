#ifndef DECK_H
#define DECK_H

#include <vector>
#include "card.h"

class Deck {
public:
    Deck();
    ~Deck() = default;

    void shuffle();
    Card deal();

private:
    std::vector<Card> cards;
};

#endif
