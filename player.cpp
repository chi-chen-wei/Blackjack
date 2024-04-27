#include "player.h"

Player::Player(int playerIndex) {
    m_playerNum = playerIndex + 1;
    m_balance = 10000;
    m_bet = 0;
    m_cardTotal = 0;
    m_dealer = false;
    m_surrender = false;
    m_out = false;
}

Player::~Player() {}

void Player::updateBalance(int balance) {
    if (m_balance + balance < 0) m_balance = 0;
    else m_balance += balance;
}

void Player::setBet(int bet) {
    m_bet = bet;
}

void Player::setDealer(bool isDealer) {
    m_dealer = isDealer;
}

void Player::setOut(bool out) {
    m_out = out;
}

void Player::addCard(Card card) {
    m_cards.push_back(card);
    m_cardTotal += card.getCardValue();
    
    // check best total if Ace is on hand
    if (card.getRank() == 1) {
        m_cardTotalWithAces.push_back(m_cardTotal); // ace is 1
        m_cardTotalWithAces.push_back(m_cardTotal + 10); // ace is 11
    } else if (!m_cardTotalWithAces.empty()) { // add possible total
        auto size = m_cardTotalWithAces.size();
        m_cardTotalWithAces.push_back(m_cardTotalWithAces[size - 2] + card.getCardValue());
        m_cardTotalWithAces.push_back(m_cardTotalWithAces[size - 1] + card.getCardValue());
    }
    if (!m_cardTotalWithAces.empty()) { // select best total
        int min = 21;
        auto size = m_cardTotalWithAces.size();
        if (m_cardTotalWithAces[size - 2] > 21 && m_cardTotalWithAces[size - 1] > 21) {
            m_cardTotal = m_cardTotalWithAces[size - 2]; // total when busts
        } else {
            for (auto i = size - 2; i < m_cardTotalWithAces.size(); i++) {
                if (21 - m_cardTotalWithAces[i] >= 0 && 21 - m_cardTotalWithAces[i] < min) {
                    min = 21 - m_cardTotalWithAces[i];
                    m_cardTotal = m_cardTotalWithAces[i];
                }
            }
        }
    }
}

void Player::printCards(string faceUpOrDown) {
    cout << "<Player " << m_playerNum << ">";
    if (isDealer()) cout << " (Dealer)" << right << setw(20) << "total: ";
    else cout << right << setw(29) << "total: ";
    if (faceUpOrDown == "down") cout << m_cards[0].getCardValue() << endl;
    else cout << getCardTotal() << endl;
    Card::printCard(m_cards, faceUpOrDown);
}

void Player::updateRecord() {
    m_record[0] = m_balance;
    if (m_bet > 0) m_record[1]++;
    else if (m_bet < 0) m_record[2]++;
}

void Player::reset() {
    m_bet = 0;
    m_cardTotal = 0;
    m_surrender = false;
    m_cards.clear();
    m_cardTotalWithAces.clear();
}

int Player::getPlayerNum() const {
    return m_playerNum;
}

int Player::getBalance() const {
    return m_balance;
}

int Player::getBet() const {
    return m_bet;
}

int Player::getNumCards() const {
    return (int)m_cards.size();
}

int Player::getCardTotal() {
    return m_cardTotal;
}

int* Player::getRecord(){
    return m_record;
}

bool Player::isDealer() const {
    return m_dealer;
}

bool Player::busts() const {
    return m_cardTotal > 21;
}

bool Player::isOut() const {
    return m_out;
}

bool Player::surrenders() const {
    return m_surrender;
}

bool Player::firstCardIsAce() {
    return m_cards[0].getRank() == 1;
}

bool Player::hasSpecialCards() {
    if (m_cards.size() >= 5 && !busts()) return true;
    for (int card = 6; card <= 8; card++) {
        bool found = false;
        for (int i = 0; i < m_cards.size(); i++) {
            if (m_cards[i].getRank() == card)
                found = true;
        }
        if (found == false) return false;
    }
    return true;
}

void Player::wantDouble() { // to edit
    m_bet *= 2;
    /*
    if (m_cardTotal == 11) {
        int doubleBet;
        start:
        cout << "Player " << m_playerNum << " Do you want to double your bet? 1: yes 2: no ";
        cin >> doubleBet;
        switch(doubleBet) {
            case 1:
                m_bet *= 2;
                return true;
            case 2:
                return false;
            default:
                goto start;
                break;
        }
    }
    return false;
     */
}

void Player::wantSurrender() {
    m_surrender = true;
    m_bet *= (-0.5);
    /*
    int surrender;
    start:
    cout << "Player " << m_playerNum << " Do you want to surrender? 1: yes 2: no ";
    cin >> surrender;
    switch(surrender) {
        case 1:
            m_surrender = true;
            m_bet *= (-0.5);
            return true;
        case 2:
            return false;
        default:
            goto start;
            break;
    }
    return false;
     */
}
