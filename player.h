#ifndef player_h
#define player_h

#include "header.h"
#include "card.h"

class Player {
    
public:
    Player(int);
    ~Player();
    
    void updateBalance(int);
    void setBet(int);
    void setOut(bool);
    void setDealer(bool);
    void addCard(Card);
    void printCards(string);
    void updateRecord();
    void reset();
    
    int getPlayerNum() const;
    int getBalance() const;
    int getBet() const;
    int getNumCards() const;
    int getCardTotal();
    int* getRecord();
    
    bool isDealer() const;
    bool busts() const;
    bool isOut() const; // rename?
    bool surrenders() const;
    bool firstCardIsAce();
    bool hasSpecialCards();
    void wantDouble();
    void wantSurrender();
    
private:
    int m_playerNum;
    int m_balance;
    int m_bet;
    int m_cardTotal;
    int m_record[3] = {0, 0, 0}; // {balance, #win, #lose}
    bool m_dealer;
    bool m_surrender;
    bool m_out;
    vector<int> m_cardTotalWithAces;
    vector<Card> m_cards;
};

#endif
