#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <deque>
#include <random>
#include <algorithm>
#include "Card.h"

class Deck {
public:
    Deck();

    void shuffle();
    void printDeck();
    void add(Card card);
    Card& dealCard();
    bool isEmpty() const;
private:
    Deck(Deck&) = delete;
    Deck& operator=(Deck&) = delete;
private:
    std::deque<Card> cards;
};

Deck::Deck() {
    for (int suit = 0; suit < Card::SUIT_COUNT; suit++) {
        for (int rank = 0; rank < Card::RANK_COUNT; rank++) {
            cards.push_back(Card(static_cast<Card::Suit>(suit), static_cast<Card::Rank>(rank)));
        }
    }
}

void Deck::shuffle() {
    static std::random_device rd;
    static std::mt19937 urng(rd());
    std::shuffle(cards.begin(), cards.end(), urng);
}

Card& Deck::dealCard() {
    Card& card = cards.back();
    cards.pop_back();
    return card;
}

bool Deck::isEmpty() const {
    return cards.empty();
}

void Deck::add(Card card) {
    cards.push_back(card);
}

void Deck::printDeck() {
    for (size_t i = 0; i < cards.size(); i++) {
        std::cout << cards[i] << std::endl;
    }
}

#endif