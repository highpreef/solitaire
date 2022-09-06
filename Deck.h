//
// Created by DAVID on 06/09/2022.
//

#ifndef SOLITAIRE_DECK_H
#define SOLITAIRE_DECK_H

#include <iostream>
#include <deque>
#include <random>
#include <algorithm>
#include "Card.h"

class Deck {
public:
    Deck();

    void shuffle();

    [[maybe_unused]] void printDeck();
    void add(Card card);
    Card& dealCard();
    [[nodiscard]] bool isEmpty() const;

    Deck(Deck&) = delete;
    Deck& operator=(Deck&) = delete;
private:
    std::deque<Card> cards;
};

Deck::Deck() {
    for (int suit = 0; suit < Card::SUIT_COUNT; suit++) {
        for (int rank = 0; rank < Card::RANK_COUNT; rank++) {
            cards.emplace_back(static_cast<Card::Suit>(suit), static_cast<Card::Rank>(rank));
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

[[maybe_unused]] void Deck::printDeck() {
    for (auto & card : cards) {
        std::cout << card << std::endl;
    }
}

#endif //SOLITAIRE_DECK_H
