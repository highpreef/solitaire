#ifndef ABSTRACTCARDSTACK_H
#define ABSTRACTCARDSTACK_H

#include "Card.h"
#include <deque>

class AbstractCardStack
{
public:
    virtual ~AbstractCardStack();

    Card& peek();
    bool add(Card& card, bool force);
    bool isEmpty() const;
    size_t size() const;
    std::deque<Card>& getCards();

protected:
    virtual bool canAdd(const Card& card) = 0;

private:
    std::deque<Card> cards;
};

AbstractCardStack::~AbstractCardStack() {
}

bool AbstractCardStack::add(Card& card, bool force) {
    if (force || canAdd(card)) {
        cards.push_back(card);
        return true;
    }
    return false;
}

Card& AbstractCardStack::peek() {
    return cards.back();
}

bool AbstractCardStack::isEmpty() const {
    return cards.empty();
}

size_t AbstractCardStack::size() const {
    return cards.size();
}

std::deque<Card>& AbstractCardStack::getCards() {
    return cards;
}

#endif