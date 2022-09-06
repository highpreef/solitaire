#ifndef TABLEAUCARDSTACK_H
#define TABLEAUCARDSTACK_H

#include "AbstractCardStack.h"

class TableauCardStack : public AbstractCardStack
{
public:
    TableauCardStack();
    ~TableauCardStack() override;
    bool canAdd(const Card& card) override;
    int getVisibleCardCount();
};

TableauCardStack::TableauCardStack() = default;

TableauCardStack::~TableauCardStack() = default;

bool TableauCardStack::canAdd(const Card& card) {
    if (isEmpty()) {
        return card.getRank() == Card::Rank::KING;
    }
    else {
        Card& topCard = peek();
        return topCard.getSuit() != card.getSuit() && topCard.getRank() - 1 == card.getRank();
    }
}

int TableauCardStack::getVisibleCardCount(){
    int count = 0;
    for (auto & i : getCards()) {
        if (i.isFaceUp()) {
            count++;
        }
    }
    return count;
}

#endif