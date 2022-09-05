#ifndef WASTECARDSTACK_H
#define WASTECARDSTACK_H

#include "AbstractCardStack.h"

class WasteCardStack : public AbstractCardStack
{
public:
    WasteCardStack();
    ~WasteCardStack();
    bool canAdd(const Card& card) override;
};

WasteCardStack::WasteCardStack() {
}

WasteCardStack::~WasteCardStack() {
}

bool WasteCardStack::canAdd(const Card& card) {
    return true;
}

#endif