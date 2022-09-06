#ifndef CURSOR_H
#define CURSOR_H

#include "Solitaire.h"
#include "Key.h"

class Cursor {
public:
    enum State { TABLEAU, FOUNDATION, STOCK};
    Cursor();
    void move(Key key);
    State getState() const;
    int getColumn() const;
private:
    State state = TABLEAU;
    int col = 0;
};

Cursor::Cursor() {
}

void Cursor::move(Key key) {
    switch (key) {
        case Key::UP:
            if (state == TABLEAU) {
                state = STOCK;
            } else if (state == FOUNDATION) {
                state = TABLEAU;
            } else if (state == STOCK) {
                state = FOUNDATION;
            }
            col = 0;
            break;
        case Key::DOWN:
            if (state == TABLEAU) {
                state = FOUNDATION;
            } else if (state == FOUNDATION) {
                state = STOCK;
            } else if (state == STOCK) {
                state = TABLEAU;
            }
            col = 0;
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

#endif