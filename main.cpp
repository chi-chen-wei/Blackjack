#include "header.h"
#include "game.h"

int main() {
    
    int rounds = 0, numPlayers = 0;
    
    cout << "Enter # of rounds you'd like to play: ";
    cin >> rounds;
    
    while (numPlayers < 2 || numPlayers > 4) {
        cout << "Enter # of players playing: ";
        cin >> numPlayers;
        if (numPlayers < 2) {
            cout << "There must be at least 2 players!" << endl;
        } else if (numPlayers > 4) {
            cout << "There must be at most 4 players!" << endl;
        }
    }
    
    Game game = Game(rounds, numPlayers);
    for (int i = 1; i <= rounds && game.isValid(); i++) {
        cout << "<< Round " << i << " >>" <<endl;
        game.playGame();
    }
    game.finalOutcome();
    
    return 0;
}
