//
// Created by DAVID on 06/09/2022.
//

#ifndef SOLITAIRE_SOLITAIRE_H
#define SOLITAIRE_SOLITAIRE_H

#include <iostream>
#include <array>
#include <deque>
#include <cctype>
#include "Cursor.h"
#include "Deck.h"
#include "FoundationCardStack.h"
#include "TableauCardStack.h"
#include "WasteCardStack.h"
#include "StockCardStack.h"
#include "Key.h"

class Solitaire {
public:
    Solitaire();
    void deal();
    void bufferCard(char from, char to);
    void pop(char from);
    void move();
    bool isWon();
    void print();
    void moveCursor(Key key);
    void select();
    bool isMovingCard() const;
private:
    void init();
    Cursor cursor;
    bool movingCard = false;
    char from{}, to{};

    Deck deck;
    std::array<FoundationCardStack, 4> foundations;
    std::array<TableauCardStack, 7> tableaus;
    std::deque<Card> buffer;
    WasteCardStack waste;
    StockCardStack stock;
};

Solitaire::Solitaire() {
    init();
}

void Solitaire::init() {
    deck.shuffle();
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < i + 1; j++) {
            Card& card = deck.dealCard();
            tableaus[i].add(card, true);
        }
        tableaus[i].peek().flip();
    }
}

void Solitaire::deal() {
    if (!stock.isEmpty() && stock.peek().isFaceUp()) {
        Card& card = stock.peek();
        if (card.isFaceUp()) {
            card.flip();
        }
        stock.getCards().pop_back();
        waste.add(card, true);
    }
    if (deck.isEmpty()) {
        while (!waste.isEmpty()) {
            Card& card = waste.peek();
            waste.getCards().pop_back();
            deck.add(card);
        }
        std::cout << "Deck is empty. Shuffling waste." << std::endl;
        return;
    }
    Card& card = deck.dealCard();
    card.flip();
    stock.add(card, true);
}

void Solitaire::bufferCard(char from, char to) {
    while (buffer.size() > 0)
        buffer.pop_back();

    if (from == 's') {
        if (stock.isEmpty()) {
            std::cout << "Stock is empty" << std::endl;
            return;
        }
        buffer.push_back(stock.peek());
    } else {
        if (tableaus[from - '0'].isEmpty()) {
            std::cout << "Tableau " << from << " is empty" << std::endl;
            return;
        }
        if (to == 'f') {
            buffer.push_back(tableaus[from - '0'].peek());
        } else {
            for (size_t i = 0; i < tableaus[from - '0'].size(); i++) {
                if (tableaus[from - '0'].getCards()[i].isFaceUp()) {
                    buffer.push_back(tableaus[from - '0'].getCards()[i]);
                }
            }
        }
    }
    return;
}

void Solitaire::pop(char from) {
    if (from == 's') {
        stock.getCards().pop_back();
    } else {
        tableaus[from - '0'].getCards().pop_back();
        if (buffer.empty() && !tableaus[from - '0'].isEmpty() && !tableaus[from - '0'].peek().isFaceUp()) {
            tableaus[from - '0'].peek().flip();
        }
    }
}

void Solitaire::move() {
    if ((from != 's' && !isdigit(from)) || (to != 'f' && !isdigit(to))) {
        std::cout << "Invalid input" << std::endl;
        return;
    }

    bufferCard(from, to);
    if (buffer.empty())
        return;

    Card& card = buffer.front();
    buffer.pop_front();

    if (isdigit(to) && to - '0' < static_cast<int>(tableaus.size()) && tableaus[to - '0'].add(card, false)) {
        pop(from);
        while (!buffer.empty()) {
            Card& card = buffer.front();
            buffer.pop_front();
            tableaus[to - '0'].add(card, true);
            pop(from);
        }
    } else if (buffer.empty() && to == 'f') {
        for (size_t i = 0; i < foundations.size(); i++) {
            if (foundations[i].add(card, false)) {
                pop(from);
                break;
            }
        }
    } else {
        std::cout << "Invalid move" << std::endl;
    }
}

bool Solitaire::isWon() {
    for (size_t i = 0; i < foundations.size(); i++) {
        if (foundations[i].size() != 13) {
            return false;
        }
    }
    return true;
}

void Solitaire::print() {
    Cursor::State state = cursor.getState();
    int column = cursor.getColumn();
    bool lastCard = cursor.isLastCard();

    std::cout<<"=============================================\n";
    for (int i = 0; i < 4; i++) {
        if (state == Cursor::State::FOUNDATION && column == i) {
            std::cout << ">";
        }
        if (!foundations[i].isEmpty())
            std::cout << foundations[i].peek();
        else
            std::cout << "[ ]";
        std::cout << "\t";

    }
    std::cout<< std::endl << "=============================================\n" << std::endl;

    std::cout<<"--------------------------------------------\n";
    std::cout<<"Stock: ";
    if (state == Cursor::State::STOCK && column == 0) {
        std::cout << ">";
    }
    if (!stock.isEmpty()) {
        std::cout << stock.peek();
    } else {
        std::cout << "[ ]";
    }
    std::cout<<"\n--------------------------------------------\n";

    std::cout<< "| 0 | \t | 1 | \t | 2 | \t | 3 | \t | 4 | \t | 5 | \t | 6 |\n";
    std::cout<< "----- \t ----- \t ----- \t ----- \t ----- \t ----- \t -----\n";

    int max = 0;

    for (int i = 0; i < 7; i++) {
        if (static_cast<int>(tableaus[i].getCards().size()) > max) {
            max = tableaus[i].getCards().size();
        }
    }
    int highlight = 0;
    if (tableaus[column].size() > 0) {
        int firstSideUp = 0;
        for (size_t i = 0; i < tableaus[column].size(); i++) {
            if (tableaus[column].getCards()[i].isFaceUp()) {
                firstSideUp = static_cast<int>(i);
                break;
            }
        }
        highlight = lastCard ? static_cast<int>(tableaus[column].size() - 1) : firstSideUp;

        if (movingCard) {
            highlight += 1;
            if (highlight >= max) {
                max += 1;
            }
        }
    }

    for (int i = 0; i < max; i++) {
        for (int j = 0; j < 7; j++) {
            if (state == Cursor::State::TABLEAU && column == j && i == highlight) {
                std::cout << ">";
            }
            if (static_cast<int>(tableaus[j].getCards().size()) > i) {
                std::cout << " " << tableaus[j].getCards()[i];
            } else {
                std::cout << " " << "[ ]";
            }
            std::cout << "\t ";
        }
        std::cout << std::endl;
    }
}

void Solitaire::moveCursor(Key key) {
    cursor.move(key, tableaus);
}

void Solitaire::select() {
    char value;
    Cursor::State state = cursor.getState();
    int column = cursor.getColumn();

    if (state == Cursor::State::FOUNDATION) {
        value = 'f';
    } else if (state == Cursor::State::TABLEAU) {
        value = column + 48;
    } else if (state == Cursor::State::STOCK) {
        value = 's';
    }

    if (!isMovingCard()) {
        from = value;
        movingCard = true;
    } else {
        to = value;
        movingCard = false;
        move();
    }
}

bool Solitaire::isMovingCard() const {
    return movingCard;
}

#endif //SOLITAIRE_SOLITAIRE_H
