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
void clearRound();
void playAgain();
void gameDraw();
void pairSplit();
void checkAces();
void checkSplitAces();
void checkDealAces();
#endif //PCH_H
