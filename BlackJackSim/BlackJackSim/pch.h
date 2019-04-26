// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H

//#define HEART "H"
//#define CLUB "C"
//#define DIAMOND "D"
//#define SPADE "S"

typedef enum {
Two = 2,
Three = 3,
Four = 4,
Five = 5,
Six = 6,
Seven = 7,
Eight = 8,
Nine = 9,
Ten = 10,
Jack = 11,
Queen = 12,
King = 13,
Ace = 14
} RANK;



typedef struct Card {
	RANK rank;
	const char* Suit;
}CARD;


void showHelp();
void clearScreen();
void shuffle();
void beginGame();
void saveGame();
void loadGame();
void playGame();
void playerDraw();
void dealerDraw();
void gameScreen();
int gameLost(int walet);
void gameWin();
void playRound();
void startGame();
int getHandTotal(int handTotal);
#endif //PCH_H
