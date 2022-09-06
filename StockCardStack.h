//
// Created by DAVID on 06/09/2022.
//

#ifndef SOLITAIRE_STOCKCARDSTACK_H
#define SOLITAIRE_STOCKCARDSTACK_H

#include "AbstractCardStack.h"

class StockCardStack : public AbstractCardStack
{
public:
    StockCardStack();
    ~StockCardStack() override;
    bool canAdd(const Card& card) override;
};

StockCardStack::StockCardStack() = default;

StockCardStack::~StockCardStack() = default;

bool StockCardStack::canAdd(const Card& card) {
    return true;
}

#endif //SOLITAIRE_STOCKCARDSTACK_H
