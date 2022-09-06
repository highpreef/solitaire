//
// Created by DAVID on 06/09/2022.
//

#ifndef SOLITAIRE_FOUNDATIONCARDSTACK_H
#define SOLITAIRE_FOUNDATIONCARDSTACK_H

#include "AbstractCardStack.h"

class FoundationCardStack : public AbstractCardStack
{
public:
    FoundationCardStack();
    ~FoundationCardStack() override;
    bool canAdd(const Card& card) override;
};

FoundationCardStack::FoundationCardStack() = default;

FoundationCardStack::~FoundationCardStack() = default;

bool FoundationCardStack::canAdd(const Card& card) {
    if (isEmpty()) {
        return card.getRank() == Card::Rank::ACE;
    }
    else {
        Card& topCard = peek();
        return topCard.getSuit() == card.getSuit() && topCard.getRank() + 1 == card.getRank();
    }
}

#endif //SOLITAIRE_FOUNDATIONCARDSTACK_H
