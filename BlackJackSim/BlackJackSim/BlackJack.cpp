//Black Jack

#include "pch.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

const char* Heart = "H";
const char* Club = "C";
const char* Diamond = "D";
const char* Spade = "S";
string dHand[10];
string pHand[10];
const char* rankName[] = {
"","A","2","3","4","5","6","7","8","9","10","J","Q","K","A"
};


CARD standardDeck[] = { 
	{Two, Heart},
	{Three, Heart},
	{Four, Heart},
	{Five, Heart},
	{Six, Heart},
	{Seven, Heart},
	{Eight, Heart},
	{Nine, Heart},
	{Ten, Heart},
	{Jack, Heart },
	{Queen, Heart },
	{King, Heart },
	{Ace, Heart },
	{Two, Club },
	{Three, Club },
	{Four, Club },
	{Five, Club },
	{Six, Club },
	{Seven, Club },
	{Eight, Club },
	{Nine, Club },
	{Ten, Club },
	{Jack, Club },
	{Queen, Club },
	{King, Club },
	{Ace, Club },
	{Two, Diamond },
	{Three, Diamond },
	{Four, Diamond },
	{Five, Diamond },
	{Six, Diamond },
	{Seven, Diamond },
	{Eight, Diamond },
	{Nine, Diamond },
	{Ten, Diamond },
	{Jack, Diamond },
	{Queen, Diamond },
	{King, Diamond },
	{Ace, Diamond },
	{Two, Spade },
	{Three, Spade },
	{Four, Spade },
	{Five, Spade },
	{Six, Spade },
	{Seven, Spade },
	{Eight, Spade },
	{Nine, Spade },
	{Ten, Spade },
	{Jack, Spade },
	{Queen, Spade },
	{King, Spade },
	{Ace, Spade },
};

int games = 0, fgam = 00, sgam = 00, tgam = 00, lgam = 00;
int gwon = 0, fgwon = 0, sgwon = 0, tgwon = 0, lgwon = 0, quit = 0;
int fwalet = 0000, swalet = 0000, twalet = 0000, lwalet = 0000, walet =0, bet =0, currentBet, tempWalet;
int hand, handTotal, dealer, dealerTotal, cardCount =2;
string name, fnam = "AAA", snam = "AAA", tnam = "AAA", lnam = "AAA";
ofstream outFile;
ifstream inFile;

#define DSIZE (sizeof(standardDeck) / sizeof(CARD))
int DeckSize = DSIZE;
CARD* shoe[DSIZE];





int main()
{
	bool start = true;
	while (start)
	{
		char Ans;
		cout << "     2222222                          1111111\n"
			<< "    22222222222                      111111111\n"
			<< "  222222   222222                  11111111111\n"
			<< " 222222     222222              11111111111111\n"
			<< "222222     2222222                      111111\n"
			<< "          222222                        111111\n"
			<< "        222222                          111111\n"
			<< "      222222                            111111\n"
			<< "    222222                              111111\n"
			<< "  222222                                111111\n"
			<< "2222222222222222222222         1111111111111111111111111\n"
			<< "2222222222222222222222         1111111111111111111111111\n"
			<< endl << endl << endl << endl
			<< "Press P to Play\n"
			<< "Press L for Leaderboard\n"
			<< "Press H for Help\n"
			<< "Press Q to Quit.";

		cin >> Ans;
		Ans = toupper(Ans);
		switch (Ans)
		{
		case 'P':
			//Begin the game
			beginGame();
			//shuffle();
			//cout << rankName[shoe[1]->rank] << " , " << shoe[1]->Suit << endl << shoe[2]->rank << endl << shoe[3]->rank << endl;
			break;
		case 'L':
			//Display the leaderboard
			showLeaderboard();
			break;
		case 'H':
			//Display Help Screen
			showHelp();
			break;
		case 'Q':
			start = false;
			//Quit the Program
			break;
		}
	}
}
void beginGame()
{
	char ans;
	bool game = true;
	cout << "To start a New game press N\n or to load a game press L,\n Press Q to quit or H for help.";
	cin >> ans;
	ans = toupper(ans);
	while (game)
	{
		
			switch (ans)
			{
			case 'N':
				//Starts a new player profile accepting name and setting wallet amount to 1000.
				cout << "What is your name?";
				cin >> name;
				for (int i = 0; i < name.size(); i++) {
					name.at(i) = toupper(name.at(i));
				}
				walet = 1000;
				saveGame();
				break;
			case 'L':
				//Loads a player profile from saved .txt file and reads in wallet amount
				loadGame();
				break;
			case 'H':
				showHelp();
				break;
			case 'Q':
				//quits to main menu.
				game = false;
				saveGame();
				break;
			default:
				while (ans != 'N' && ans != 'L' && ans != 'H' && ans != 'Q')
					cout << "Valid choices are only N,L,H or Q."
					<< "Please enter your choice.";
				cin >> ans;
			}
			if (ans == 'N' || ans == 'L')
				playGame();
	}
}
void showLeaderboard()
{
	// Shows the leaderboard
	cout << setprecision(7) << fixed;

	cout << "**********************************************************************\n"
		<< "**                          Leaderboard                              **\n"
		<< "***********************************************************************\n"
		<< "***  Rank  ***  Name  ***  Games Played  ***  Games Won  *** Money  ***\n"
		<< "***  1st" << "\t" << fnam << "\t\t" << fgam << "\t" << fgwon << setw(7) << fwalet << "  ***\n"
		<< "***  1st" << "\t" << snam << "\t\t" << sgam << "\t" << sgwon << setw(7) << swalet << "  ***\n"
		<< "***  1st" << "\t" << tnam << "\t\t" << tgam << "\t" << tgwon << setw(7) << twalet << "  ***\n"
		<< "***  1st" << "\t" << lnam << "\t\t" << lgam << "\t" << lgwon << setw(7) << lwalet << "  ***\n"
		<< "****************************************************\n\n\n";
	return;
}

void updateLeaderboard() 
{
	 // Accepts your initials then moves your score up to the proper position, pushing down other scores if you beat them. 
		if (gwon > lgwon)
		{

			lnam = name;
			lgam = games;
			lgwon = gwon;
			lwalet = walet;

			if (gwon  > tgwon)
			{
				lnam = tnam;
				lgam = tgam;
				lgwon = tgwon;
				lwalet = twalet;

				tnam = name;
				tgam = games;
				tgwon = gwon;
				twalet = walet;

				if (gwon > sgwon)
				{

					tnam = snam;
					tgwon = sgwon;
					tgam = sgam;
					twalet = swalet;

					snam = name;
					sgam = games;
					sgwon = gwon;
					swalet = walet;

					if (gwon > fgwon)
					{

						snam = fnam;
						sgam = fgam;
						sgwon = fgwon;
						swalet = fwalet;

						fnam = name;
						fgam = games;
						fgwon = gwon;
						fwalet = walet;
					}
				}
			}
		}
		else
			cout << "Sorry you didnt score high enough to make it on the Leaderboard. ";
		showLeaderboard();
			return;
	
	}


void clearScreen()
{
	int n;
	for (n = 0; n < 10; n++)
		printf("\n\n\n\n\n\n\n\n\n\n");

}

void showHelp()
{
	clearScreen();
	cout << "In 21 (also referred to as Black Jack) your job is to beat the dealer. To do that you begin the game\n"
		<< "each being dealt 2 cards, your cards are face up so you can see and one of the dealers card is face up. \n"
		<< "The dealers second card is face down and the object is to either beat the dealer without going over 21. \n"
		<< "To do this you may Hit, Stand or Double Down. \n"
		<< "Numbered cards (2-10) are the value printed on the card. J,Q,K are also worth 10. \n"
		<< "A's are normally worth 11, however if your hand has a value higher than 11 they are worth 1. (ex AK is 21, K,2,A is 13. \n\n"
		<< "************ Playing the Game *************** \n"
		<< "Once the cards are dealt you have several options open to you.\n"
		<< "Press H to Hit. This will deal a new card from the deck and add it's value to your total.\n"
		<< "Press S to Stand. This will signal that you believe your hand will beat the dealers. \n"
		<< "Press D to Double Down. When you do this you will double your bet for exactly 1 more card, then stand."
		<< "Press P to Split. This is only allowed with doubles, you split the hand into 2 new hands placing a second bet for the second hand.\n"
		<< "In the event of a split hands will be played right to left (clockwise). \n\n"
		<< "Once you Stand the dealer will reveal their second card and hit or stand up until they reach 18 or bust. Then the higher hand will win the bet.\n"
		<< "In the case of a tie, a push will occur and you will get your initial bet back. ";
}		


void deckCreation() {
	for (int ind = 0; ind < DeckSize; ind++){
		shoe[ind] = &standardDeck[ind];
	}
}

void shuffle() {
	deckCreation();
	srand(time(NULL));
	for (int n = DeckSize-1; n > 0; --n) {
		int r = rand() % n;

		CARD* cardSwap = shoe[r];
		shoe[r] = shoe[n];
		shoe[n] = cardSwap;
	}

} 

void saveGame() { //writes a player to the player record
	ofstream outFile("PlayerRecord.txt");
	outFile << name << " " << games << " " << gwon << " " << walet << endl;
	outFile.close();
}

void loadGame() { //Reads in the player saved to the player record 
	ifstream inFile("PlayerRecord.txt");
	inFile >> name >> games >> gwon >> walet;
	inFile.close();
}

int getCardValue(int value) {
	if (value >= 11 && value <= 13) {
		return 10;
	}
	else if (value == 14) {
			return 11;
		}
	return value;
	}

int betting(int value) {
	if (value > 0 && value <= walet) {
	tempWalet = walet -value;
		return currentBet;
	}
	else if (value == 0 || value > walet) {
		cout << "Please enter a valid bet between 1 and " << walet;
	}
	return value;
}

void playGame() {

	bool play = true;
	while (play) {
		//clearScreen();
		

		shuffle();
		pHand[0] = rankName[shoe[0]->rank];
		pHand[1] = shoe[0]->Suit;
		dHand[0] = rankName[shoe[1]->rank];
		dHand[1] = shoe[1]->Suit;
		pHand[2] = rankName[shoe[2]->rank];
		pHand[3] = shoe[2]->Suit;
		dHand[2] = rankName[shoe[3]->rank];
		dHand[3] = shoe[3]->Suit;

		handTotal = getCardValue(shoe[0]->rank) + getCardValue(shoe[2]->rank);
		dealerTotal = getCardValue(shoe[1]->rank) + getCardValue(shoe[3]->rank);
		cout << "You currently have $" << walet << "how much would you like to bet?";
		cin >> bet;
		betting(bet);

		cout << "*************************************\n"
			<< "**            DEALER               **\n"
			<< "**       " << "Current Total: " << setw(2) << dealerTotal << "         **\n"
			<< "**    " << dHand[0] << dHand[1] << "  " << dHand[2] << dHand[3] << "                       **\n"
			<< "**                                 **\n"
			<< "**                                 **\n"
			<< "**                                 **\n"
			<< "**    " << pHand[0] << pHand[1] << "  " << pHand[2] << pHand[3] << "                       **\n"
			<< "**    " << "Current Total: " << setw(2) << handTotal << "   Current Bet: " << currentBet <<"   **\n"
			<< "**            " << name << "                 **\n"
			<< "*************************************\n";
		playRound();
	}
}

void playRound() {
	char choice;
	if (dealerTotal == 21 && handTotal != 21) {
		endGame(tempWalet);
	}
	else if (handTotal > 22)
	{
		endGame(tempWalet);
	}
	else if (handTotal == 21) {
		endGame(currentBet);
	}
	else {
		cout << "What would you like to do?\n Press H to Hit, \nPress S to Stand, \nPress D to Double down, \n";
		if (pHand[0] == pHand[1]) {
			cout << "Press P to Split";
		}
		cin >> choice;
		choice = toupper(choice);
	}
	switch (choice) {
	case 'H':
		cardCount++;
	case 'S':
	case 'D':
		cardCount++;
		//case 'P':

	default:
	}
}

void gameScreen() {

}


//int endGame(string) {
//	string lose = 
//		cout << "Sorry you have lost.";
//		walet = tempWalet;
//		return walet;
//	}
//	else if (handTotal == 21 && cardCount == 2) {
//		cout << "You Win";
//		walet =+ (currentBet * 1.5);
//	}
//	else if (handTotal > dealerTotal && dealerTotal > 17)
//		{
//		walet = currentBet;
//		}
//}
//
//
