#ifndef game_h
#define game_h

#include "header.h"
#include "player.h"

struct CompareRecord {
    bool operator()(Player* player1, Player* player2) {
        if (player1->getRecord()[0] != player2->getRecord()[0])
            return player1->getRecord()[0] < player2->getRecord()[0];
        if (player1->getRecord()[1] != player2->getRecord()[1])
            return player1->getRecord()[1] < player2->getRecord()[1];
        return player1->getRecord()[1] + player1->getRecord()[2] > player2->getRecord()[1] + player2->getRecord()[2];
    }
};

class Game {
    
public:
    Game(int, int);
    ~Game();
    
    void createCards(); // initialize Cards
    void shuffleCards();
    void setDealer(int, bool);
    void setPlayerBet();
    void playGame();
    void initialHand(); //initialHand
    void deal(Player&);
    void checkInsurance();
    void checkResult();
    void printResult();
    void finalOutcome();
    bool isValid();
    
private:
    int m_rounds;
    int m_numPlayers;
    int m_minBet;
    int m_dealerIndex;
    int m_deckIndex;
    Player* m_dealer;
    vector<Card> m_deckOfCards;
    vector<Player> m_players;

    
};

#endif
