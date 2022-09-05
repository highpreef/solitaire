#ifndef SOLITAIRE_H
#define SOLITAIRE_H

#include <iostream>
#include <array>
#include <deque>
#include <ctype.h>
#include "Deck.h"
#include "FoundationCardStack.h"
#include "TableauCardStack.h"
#include "WasteCardStack.h"
#include "StockCardStack.h"

class Solitaire {
public:
    Solitaire();
    void deal();
    void bufferCard(char from);
    void pop(char from);
    void move();
    bool isWon();
    void print();
private:
    void init();
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
        card.flip();
        stock.getCards().pop_back();
        waste.add(card, true);
    }
    if (deck.isEmpty()) {
        while (!waste.isEmpty()) {
            Card& card = waste.peek();
            waste.getCards().pop_back();
            deck.add(card);
        }
    }
    Card& card = deck.dealCard();
    card.flip();
    stock.add(card, true);
}

void Solitaire::bufferCard(char from) {
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

        for (size_t i = 0; i < tableaus[from - '0'].size(); i++) {
            if (tableaus[from - '0'].getCards()[i].isFaceUp()) {
                buffer.push_back(tableaus[from - '0'].getCards()[i]);
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
    }
}

void Solitaire::move() {
    char from, to;
    std::cout << "From: ";
    std::cin >> from;
    std::cout << "To: ";
    std::cin >> to;

    if ((from != 's' && !isdigit(from)) || (to != 'f' && !isdigit(to))) {
        std::cout << "Invalid input" << std::endl;
        return;
    }

    bufferCard(from);
    if (buffer.size() == 0)
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
        if (!tableaus[from - '0'].isEmpty()) {
            tableaus[from - '0'].peek().flip();
        }
    } else if (buffer.size() == 0 && to == 'f') {
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
    std::cout<<"=============================================\n";
	for (int i = 0; i < 4; i++) {
        if (!foundations[i].isEmpty())
            std::cout << foundations[i].peek();
        else
            std::cout << "[ ]";
        std::cout << "\t";

    }
	std::cout<< std::endl << "=============================================\n" << std::endl;

    std::cout<<"--------------------------------------------\n";
	std::cout<<"Stock: ";
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

    for (int i = 0; i < max; i++) {
        for (int j = 0; j < 7; j++) {
            if (static_cast<int>(tableaus[j].getCards().size()) > i) {
                std::cout << tableaus[j].getCards()[i];
            } else {
                std::cout << "[ ]";
            }
            std::cout << "\t";
        }
        std::cout << std::endl;
    }
}


#endif