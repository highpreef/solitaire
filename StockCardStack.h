#ifndef STOCKCARDSTACK_H
#define STOCKCARDSTACK_H

#include "AbstractCardStack.h"

class StockCardStack : public AbstractCardStack
{
public:
    StockCardStack();
    ~StockCardStack();
    bool canAdd(const Card& card) override;
};

StockCardStack::StockCardStack() {
}

StockCardStack::~StockCardStack() {
}

bool StockCardStack::canAdd(const Card& card) {
    return true;
}

#endif