//
// Created by DAVID on 06/09/2022.
//

#ifndef SOLITAIRE_WASTECARDSTACK_H
#define SOLITAIRE_WASTECARDSTACK_H

#include "AbstractCardStack.h"

class WasteCardStack : public AbstractCardStack
{
public:
    WasteCardStack();
    ~WasteCardStack() override;
    bool canAdd(const Card& card) override;
};

WasteCardStack::WasteCardStack() = default;

WasteCardStack::~WasteCardStack() = default;

bool WasteCardStack::canAdd(const Card& card) {
    return true;
}

#endif //SOLITAIRE_WASTECARDSTACK_H
