#ifndef TABLEAUCARDSTACK_H
#define TABLEAUCARDSTACK_H

#include "AbstractCardStack.h"

class TableauCardStack : public AbstractCardStack
{
public:
    TableauCardStack();
    ~TableauCardStack();
    bool canAdd(const Card& card) override;
};

TableauCardStack::TableauCardStack() {
}

TableauCardStack::~TableauCardStack() {
}

bool TableauCardStack::canAdd(const Card& card) {
    if (isEmpty()) {
        return card.getRank() == Card::Rank::KING;
    }
    else {
        Card& topCard = peek();
        return topCard.getSuit() != card.getSuit() && topCard.getRank() - 1 == card.getRank();
    }
}

#endif