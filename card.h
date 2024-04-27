#ifndef CARD_H
#define CARD_H

#include "header.h"

enum Suit {
    Spade = 1,
    Heart = 2,
    Diamond = 3,
    Club = 4
};

class Card {
    
public:
    Card(int, int);
    ~Card();
    
    int getSuit() { return m_suit; }
    int getRank() { return m_rank; }
    int getCardValue() { return m_cardValue; }
    
    static void printCard(vector<Card>&, string);
    
private:
    int m_suit;
    int m_rank;
    int m_cardValue;
    
    static vector< vector<string> > suit_design;

    void printRank();
};

#endif
