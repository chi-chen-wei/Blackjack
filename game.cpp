#include "game.h"

Game::Game(int rounds, int numPlayers) {
    m_rounds = rounds;
    m_numPlayers = numPlayers;
    m_minBet = 1000;
    srand(unsigned(time(0)));
    m_dealerIndex = rand() % numPlayers;
    for (int i = 0; i < numPlayers; i++) {
        Player player = Player(i);
        m_players.push_back(player);
    }
    createCards();
}

Game::~Game() {}

void Game::createCards() {
    for (int suit = 1; suit <= 4; suit++) {
        for (int rank = 1; rank <= 13; rank++) {
            m_deckOfCards.push_back(Card(suit, rank));
        }
    }
}

void Game::shuffleCards() {
    cout << "***************************************************" << endl
         << right << setw(30) << "Shuffling!" << endl
         << "***************************************************" << endl;
    srand(unsigned(time(0)));
    random_device rd;
    mt19937 g(rd());
    shuffle(m_deckOfCards.begin(), m_deckOfCards.end(), g);
    m_deckIndex = 0;
}

void Game::setDealer(int playerIndex, bool isDealer) {
    m_players[playerIndex].setDealer(isDealer);
    if (isDealer) m_dealer = &m_players[playerIndex];
}

void Game::setPlayerBet() {
    for (int i = 0; i < m_players.size(); i++) {
        if (!m_players[i].isOut() && !m_players[i].isDealer()) {
            start:
            int bet;
            cout << "Player " << m_players[i].getPlayerNum() << " please enter your bet (min bet: " << m_minBet << ") : ";
            cin >> bet;
            if (bet < m_minBet) {
                cout << "Your bet must be at least " << m_minBet << "!" << endl;
                goto start;
            } else if (bet > m_players[i].getBalance()) {
                cout << "Your bet can't exceed your current balance!" << endl;
                goto start;
            }
            m_players[i].setBet(bet);
        }
    }
}

void Game::playGame() {
    setDealer(m_dealerIndex, true);
    cout << "This round's dealer: Player " << m_dealerIndex + 1 << endl;
    
    setPlayerBet();
    shuffleCards();
    initialHand();
    
    if (m_dealer->firstCardIsAce())
        checkInsurance();
    
    cout << endl;
    for (int i = 0; i < m_numPlayers; i++) {
        if (!m_players[i].isOut() && !m_players[i].isDealer()) {
            m_players[i].printCards("up");
            deal(m_players[i]);
        }
    }
    
    m_dealer->printCards("up");
    while (m_dealer->getCardTotal() < 17) {
        m_dealer->addCard(m_deckOfCards[m_deckIndex++]);
        m_dealer->printCards("up");
    }
    deal(m_players[m_dealerIndex]);
    
    checkResult();
    printResult();
}

void Game::initialHand() {
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < m_numPlayers; i++) {
            if (!m_players[i].isOut() && !m_players[i].isDealer()) {
                m_players[i].addCard(m_deckOfCards[m_deckIndex++]);
                m_players[i].printCards("up");
            }
        }
        m_dealer->addCard(m_deckOfCards[m_deckIndex++]);
        m_dealer->printCards("down");
    }
}

void Game::deal(Player& player) {
    bool hit = true;
    while(!player.isOut() && !player.busts() && hit) {
        int action;
        start:
        cout << "Player " << player.getPlayerNum() << " choose your action: " << endl << "1: hit 2: stand ";
        if (player.getNumCards() == 2 && !player.isDealer()) {
            cout << "3: surrender ";
        }
        if (player.getNumCards() == 2 && player.getCardTotal() == 11 && !player.isDealer()) {
            cout << "4: double ";
        }
        cin >> action;
        switch(action) {
            case 1:
                player.addCard(m_deckOfCards[m_deckIndex++]);
                player.printCards("up");
                break;
            case 2:
                hit = false;
                break;
            case 3:
                if (player.getNumCards() == 2 && !player.isDealer()) {
                    player.wantSurrender();
                    hit = false;
                } else {
                    goto start;
                }
                break;
            case 4:
                if (player.getNumCards() == 2 && player.getCardTotal() == 11 && !player.isDealer()) {
                    player.wantDouble();
                    player.addCard(m_deckOfCards[m_deckIndex++]);
                    player.printCards("up");
                    hit = false;
                } else {
                    goto start;
                }
                break;
            default:
                goto start;
                break;
        }
        
    }
}

void Game::checkInsurance() {
    for (int i = 0; i < m_numPlayers; i++) {
        if (!m_players[i].isOut() && !m_players[i].isDealer()) {
            start:
            int insurance;
            cout << "Player " << m_players[i].getPlayerNum() << " do you want to get insurance? 1: yes 2: no ";
            cin >> insurance;
            switch(insurance) {
                case 1:
                    if (m_dealer->getCardTotal() == 21) {
                        m_players[i].updateBalance(m_players[i].getBet());
                    } else {
                        m_players[i].updateBalance(-0.5 * m_players[i].getBet());
                    }
                    break;
                case 2:
                    break;
                default:
                    goto start;
                    break;
            }
        }
    }
}

void Game::checkResult() {
    int accumulate = 0;
    for (int i = 0; i < m_numPlayers; i++) {
        if (!m_players[i].isOut() && !m_players[i].isDealer()) {
            if (m_players[i].surrenders()) {
                
            } else if (m_players[i].hasSpecialCards()) {
                m_players[i].setBet(3 * m_players[i].getBet());
            } else if (m_dealer->busts()) {
                if (m_players[i].busts()) {
                    m_players[i].setBet(0);
                }
            } else {
                if (m_players[i].busts()) {
                    m_players[i].setBet(-m_players[i].getBet());
                } else {
                    if (m_players[i].getCardTotal() <= m_dealer->getCardTotal()) {
                        m_players[i].setBet(-m_players[i].getBet());
                    }
                }
            }
            accumulate += -m_players[i].getBet();
        }
    }
    m_dealer->setBet(accumulate);
}

void Game::printResult() {
    cout << endl;
    
    setDealer(m_dealerIndex, false);
    
    int maxGain = 0;
    for (int i = 0; i < m_numPlayers; i++) {
        m_players[i].updateBalance(m_players[i].getBet());
        m_players[i].updateRecord();
        if (m_players[i].getBet() > maxGain) {
            maxGain = m_players[i].getBet();
            m_dealerIndex = i;
        } else if (m_players[i].getBet() == maxGain) {
            if (m_players[i].getBalance() < m_players[m_dealerIndex].getBalance())
                m_dealerIndex = i;
        }
        if (m_players[i].getBalance() < m_minBet)
            m_players[i].setOut(true);
        
        if (m_players[i].isOut()) cout << "(Out!) ";
        cout << "<Player " << m_players[i].getPlayerNum() << "> ";
        if (m_players[i].getBet() > 0) cout << "+" << left << setw(7);
        else cout << left << setw(8);
        cout << m_players[i].getBet() << " remaining balance: " << m_players[i].getBalance() << " dollars" << endl;
        
        m_players[i].reset();
    }
    cout << endl;
}

bool Game::isValid() {
    int count = 0;
    for (int i = 0; i < m_numPlayers; i++)
        if (!m_players[i].isOut()) count++;
    if (count < 2) {
        cout << "Game over! Not enough players left." << endl;
        return false;
    } else {
        return true;
    }
}

void Game::finalOutcome() {
    priority_queue<Player*, vector<Player*>, CompareRecord> pq;
    for (int i = 0; i < m_numPlayers; i++) {
        pq.push(&m_players[i]);
    }
    
    cout << "Final result:" << endl;
    cout << left << setw(10) << " Rank"
    << setw(10) << "Player"
    << setw(11) << "Balance"
    << setw(7) << "Win"
    << setw(8) << "Lose" << endl;
    
    int rank = 0;
    while (!pq.empty()) {
        rank++;
        cout << right << setw(4) << rank
        << right << setw(12) << "<Player " << pq.top()->getPlayerNum() << ">"
        << right << setw(8) << pq.top()->getRecord()[0]
        << right << setw(7) << pq.top()->getRecord()[1]
        << right << setw(8) << pq.top()->getRecord()[2] << endl;
        pq.pop();
    }
}
