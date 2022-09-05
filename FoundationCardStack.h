#ifndef FOUNDATIONCARDSTACK_H
#define FOUNDATIONCARDSTACK_H

#include "AbstractCardStack.h"

class FoundationCardStack : public AbstractCardStack
{
public:
    FoundationCardStack();
    ~FoundationCardStack();
    bool canAdd(const Card& card) override;
};

FoundationCardStack::FoundationCardStack() {
}

FoundationCardStack::~FoundationCardStack() {
}

bool FoundationCardStack::canAdd(const Card& card) {
    if (isEmpty()) {
        return card.getRank() == Card::Rank::ACE;
    }
    else {
        Card& topCard = peek();
        return topCard.getSuit() == card.getSuit() && topCard.getRank() + 1 == card.getRank();
    }
}

#endif