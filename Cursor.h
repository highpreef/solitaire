//
// Created by DAVID on 06/09/2022.
//

#ifndef SOLITAIRE_CURSOR_H
#define SOLITAIRE_CURSOR_H

#include "Solitaire.h"
#include "Key.h"
#include "TableauCardStack.h"

class Cursor {
public:
    enum State { TABLEAU, FOUNDATION, STOCK};
    Cursor();
    void move(Key key, std::array<TableauCardStack, 7>& tableaus);
    [[nodiscard]] State getState() const;
    [[nodiscard]] int getColumn() const;
    [[nodiscard]] bool isLastCard() const;
private:
    State state = TABLEAU;
    int col = 0;
    bool lastCard = true;
};

Cursor::Cursor() = default;

void Cursor::move(Key key, std::array<TableauCardStack, 7>& tableaus) {
    switch (key) {
        case Key::UP:
            if (state == TABLEAU) {
                if (lastCard && tableaus[col].getVisibleCardCount() > 1) {
                    lastCard = !lastCard;
                } else {
                    state = STOCK;
                    col = 0;
                }
            } else if (state == FOUNDATION) {
                state = TABLEAU;
                col = 0;
            } else if (state == STOCK) {
                state = FOUNDATION;
                col = 0;
            }
            break;
        case Key::DOWN:
            if (state == TABLEAU) {
                if (!lastCard && tableaus[col].getVisibleCardCount() > 1) {
                    lastCard = !lastCard;
                } else {
                    state = FOUNDATION;
                    col = 0;
                }
            } else if (state == FOUNDATION) {
                state = STOCK;
                col = 0;
            } else if (state == STOCK) {
                state = TABLEAU;
                col = 0;
            }
            break;
        case Key::LEFT:
            if (state == TABLEAU) {
                col = (col + 6) % 7;
            } else if (state == FOUNDATION) {
                col = (col + 3) % 4;
            } else if (state == STOCK) {
                state = TABLEAU;
                col = 0;
            }
            break;
        case Key::RIGHT:
            if (state == TABLEAU) {
                col = (col + 1) % 7;
            } else if (state == FOUNDATION) {
                col = (col + 1) % 4;
            } else if (state == STOCK) {
                state = TABLEAU;
                col = 0;
            }
            break;
        default:
            break;
    }
}

Cursor::State Cursor::getState() const {
    return state;
}

int Cursor::getColumn() const {
    return col;
}

bool Cursor::isLastCard() const {
    return lastCard;
}

#endif //SOLITAIRE_CURSOR_H
