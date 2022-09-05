#ifndef SOLITAIRE_H
#define SOLITAIRE_H

#include <iostream>
#include <array>
#include "Deck.h"
#include "FoundationCardStack.h"
#include "TableauCardStack.h"
#include "WasteCardStack.h"
#include "StockCardStack.h"

class Solitaire {
public:
    Solitaire();
    void deal();
    void print();
private:
    void init();
    Deck deck;
    std::array<FoundationCardStack, 4> foundations;
    std::array<TableauCardStack, 7> tableaus;
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
        if (tableaus[i].getCards().size() > max) {
            max = tableaus[i].getCards().size();
        }
    }

    for (int i = 0; i < max; i++) {
        for (int j = 0; j < 7; j++) {
            if (tableaus[j].getCards().size() > i) {
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