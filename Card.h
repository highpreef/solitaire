#ifndef CARD_H
#define CARD_H

#include<iostream>
#include<windows.h>
const static int BLACK = 0;
const static int BLUE = 9;
const static int RED = 12;
const static int WHITE = 15;
const static char SUITS[] = { 'C', 'D', 'H', 'S' };
const static char RANKS[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};

class Card {
public:
    enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES, SUIT_COUNT};
    enum Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, RANK_COUNT};

    Card(Suit suit, Rank rank);

    void flip();
    bool isFaceUp() const;
    
    int getScore() const;
    Suit getSuit() const;
    Rank getRank() const;
    bool isBlack() const;
    bool isRed() const;

    friend std::ostream& operator<<(std::ostream& os, const Card& card);

private:
    Suit suit;
    Rank rank;
    bool faceUp;
};

Card::Card(Suit suit, Rank rank) : suit(suit), rank(rank), faceUp(false) {};

void Card::flip() {
    faceUp = !faceUp;
}

bool Card::isFaceUp() const {
    return faceUp;
}

int Card::getScore() const {
    if (rank == ACE)
        return 1;
    else if(rank == TEN)
		return 10;
	else if(rank == JACK)
		return 11;
	else if(rank == QUEEN)
		return 12;
	else if(rank == KING)
		return 13;
    else
        return rank - '0';
}

Card::Suit Card::getSuit() const {
    return suit;
}

Card::Rank Card::getRank() const {
    return rank;
}

bool Card::isBlack() const {
    return suit == CLUBS || suit == SPADES;
}

bool Card::isRed() const {
    return suit == DIAMONDS || suit == HEARTS;
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    if (card.isFaceUp()) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (card.isBlack())
            SetConsoleTextAttribute(hConsole, BLUE);
        else
            SetConsoleTextAttribute(hConsole, RED);
        os << RANKS[card.rank] << SUITS[card.suit];
        SetConsoleTextAttribute(hConsole, WHITE);
        return os;
    }
    os << "XX";
    return os;
}

#endif