#include "card.h"

Card::Card(int suit, int rank) {
    m_suit = suit;
    m_rank = rank;
    if (rank > 10) m_cardValue = 10;
    else m_cardValue = rank;
}

Card::~Card() {}

vector< vector<string> > Card::suit_design = { 
{
    "        *        ",
    "      *****      ",
    "    *********    ",
    "  *************  ",
    "*****************",
    "*****************",
    " *************** ",
    "       ***       ",
    "      *****      "
}, {
    "                 ",
    "  *****   *****  ",
    " ******* ******* ",
    "*****************",
    "*****************",
    "  *************  ",
    "    *********    ",
    "      *****      ",
    "        *        "
}, {
    "        *        ",
    "      *****      ",
    "    *********    ",
    "  *************  ",
    "*****************",
    "  *************  ",
    "    *********    ",
    "      *****      ",
    "        *        "
}, {
    "      *****      ",
    "    *********    ",
    "     *******     ",
    "  *************  ",
    "*****************",
    " ******* ******* ",
    "  ***** * *****  ",
    "       ***       ",
    "      *****      "
}};

void Card::printCard(vector<Card>& cards, string faceUpOrDown) {
    
    int maxCardsPerLine = 4;
    
    for (int x = 0; x < cards.size(); x += maxCardsPerLine) {
        for (int y = 0; y < maxCardsPerLine && x + y <= cards.size() - 1; y++) {
            for (int i = 0; i < 8; i++)  cout << " __";
            cout << "    ";
            if (y == maxCardsPerLine - 1 || x + y == cards.size() - 1) cout << endl;
        }
        for (int y = 0; y < maxCardsPerLine && x + y <= cards.size() - 1; y++) {
            if (faceUpOrDown == "down" && y == 1) {
                cout << "|" << right << setw(24) << "|" << "   ";
            } else {
                cout << "| " << left << setw(22);
                cards[x + y].printRank();
                cout << "|" << "   ";
            }
            if (y == maxCardsPerLine - 1 || x + y == cards.size() - 1) cout << endl;
        }
        for (int row = 0; row < suit_design[0].size(); row++) {
            for (int y = 0; y < maxCardsPerLine && x + y <= cards.size() - 1; y++) {
                if (faceUpOrDown == "down" && y == 1) {
                    cout << "|" << right << setw(24) << "|" << "   ";
                } else {
                    cout << left << setw(4) << "|";
                    for (int col = 0; col < suit_design[cards[x + y].getSuit() - 1][row].size(); col++) {
                        cout << suit_design[cards[x + y].getSuit() - 1][row][col];
                    }
                    cout  << right << setw(4) << "|" << "   ";
                }
            }
            cout << endl;
        }
        for (int y = 0; y < maxCardsPerLine && x + y <= cards.size() - 1; y++) {
            if (faceUpOrDown == "down" && y == 1) {
                cout << "|" << right << setw(24) << "|" << "   ";
            } else {
                cout << "|" << right << setw(22);
                cards[x + y].printRank();
                cout << " |" << "   ";
            }
            if (y == maxCardsPerLine - 1 || x + y == cards.size() - 1) cout << endl;
        }
        for (int y = 0; y < maxCardsPerLine && x + y <= cards.size() - 1; y++) {
            for (int i = 0; i < 8; i++)  cout << " --";
            cout << "    ";
            if (y == maxCardsPerLine - 1 || x + y == cards.size() - 1) cout << endl;
        }
    }
}

void Card::printRank() {
    if (m_rank == 1) cout << "A";
    else if (m_rank == 11) cout << "J";
    else if (m_rank == 12) cout << "Q";
    else if (m_rank == 13) cout << "K";
    else cout << m_rank;
}
