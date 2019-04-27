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
string pSHand[10];
string dTemp[2];
const char* rankName[] = {  //rank names as shown on screen
"","A","2","3","4","5","6","7","8","9","10","J","Q","K","A"
};

//the initial deck
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

int games = 0, psh, aces=0,sAces=0, dAces;
int gwon = 0, quit = 0;
int walet =0, bet =0, currentBet, tempWalet;
int hand, handTotal = 0, dealer, dealerTotal = 0, dealTempTotal = 0, cardCount = 0, dI = 0, ph = 0, dh = 0, splitTotal=0, splitCount=0;
bool game = true, play = true, start =true;  //exits
string name;
ofstream outFile;
ifstream inFile;
char choice;
#define DSIZE (sizeof(standardDeck) / sizeof(CARD))
int DeckSize = DSIZE;
CARD* shoe[DSIZE];





int main()
{
	while (start)
	{
		char Ans;
		cout << "      2222222                          1111111\n"
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
			<< "2222222222222222222222         1111111111111111111111111\n"
			<< endl << endl << endl << endl
			<< "Press P to Play\n"
			<< "Press H for Help\n"
			<< "Press Q to Quit.";

		cin >> Ans;
		Ans = toupper(Ans);
		switch (Ans)
		{
		case 'P':
			//Begin the game
			beginGame();
			clearRound();
			break;
		case 'H':
			//Display Help Screen
			showHelp();
			clearRound();
			break;
		case 'Q':
			start = false;
			//Quit the Program
			break;
		default:
			cout << "Please enter P, H or Q! \n\n\n";
		}
	}
}
void beginGame()
{
	char ans;
	
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
				game = false;
				break;
			case 'L':
				//Loads a player profile from saved .txt file and reads in wallet amount
				loadGame();
				game = false;
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
				while (ans != 'N' && ans != 'L' && ans != 'H' && ans != 'Q') {
					cout << "Valid choices are only N,L,H or Q."
						<< "Please enter your choice.";
					cin >> ans;
					ans = toupper(ans);
					
				}
				break;
			}
	
	}
	if (ans == 'N' || ans == 'L')
		playGame();
}


void clearScreen() //prints 100 new lines to effectivly "clear" the screen
{
	int n;
	for (n = 0; n < 10; n++)
		printf("\n\n\n\n\n\n\n\n\n\n");

}

void showHelp()
{// explains how the game works. 
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
		<< "In the case of a tie, a push will occur and you will get your initial bet back. "
		<< endl << endl << endl;
}		


void deckCreation() { //takes the cards from the standard decklist and puts them into a shoe
	for (int ind = 0; ind < DeckSize; ind++){
		shoe[ind] = &standardDeck[ind];
	}
}

void shuffle() { //shuffles the card shoe to randomize for playing the  game
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

int getCardValue(int value) { //checks the card values and prints a value of 10 for KQJ
	if (value >= 11 && value <= 13) {
		return 10;
	}
	else if (value == 14) { //if the card value is an A check to see if hand is higher than 10 if not the value is 11 if it is the value is 1
		if (value == 14 && handTotal > 10) {
			return 1;
		}
		return 11;
	}
	
	return value;
	}

int betting(int bet) { //reads in your bet and makes sure its a valid value
	bool valid = true;
		while (bet == 0 || bet > walet) {
				cout << "Please enter a valid bet between 1 and " << walet;
				cout << "\n What is your bet?  ";
				cin >> bet;
				
		}

		tempWalet = walet - bet;
		currentBet = bet;
		return currentBet;
}

void playGame() {

	// the main play of the game calls all functions and returns here at the end of the round
	while (play) {
		clearScreen();
		cout << "You currently have $" << walet << " how much would you like to bet?  ";
		cin >> bet;
		betting(bet);
		startGame();
		gameScreen();
		playRound();
		clearRound();
		saveGame();
		playAgain();
	}
}

void playRound() {
	//checks to see if your standing if not runs through checking hand totals
	while (choice != 'S') {
		checkAces();
		if (cardCount ==5){
			gameWin();
		}
		else if (dealerTotal == 21 && handTotal != 21) 
		{
			gameLost(bet);
			break;
		}
		else if (handTotal >= 22)
		{
			gameLost(bet);
			break;
		}
		else if (handTotal == 21) {
			gameWin();
			break;
		}
		else {
			cout << "What would you like to do?\n Press H to Hit \nPress S to Stand \n"; //asks you to hit stand or conditionally double down or split
				if (cardCount == 2) {
					cout << "Press D to Double down";
				}
			if (pHand[0] == pHand[2]) {
				cout << ", \nPress P to Split";
			}
			cin >> choice;
			choice = toupper(choice);
		}
		switch (choice) {  
		case 'H':
			playerDraw();
			break;
		case 'S':
			break;
		case 'D':
			currentBet = currentBet * 2;
			playerDraw();
			choice = 'S';
			break;
		case 'P': 
			pairSplit();
			break;
		default:
			cout << "Please enter H, S, or D";
		}
		clearScreen();
		gameScreen();
	}
	if (choice == 'S') { //once you stand it draws cards for the dealer til they bust, hit 18, or win
		dHand[2] = dTemp[0];
		dHand[3] = dTemp[1];
		dealerTotal += dealTempTotal;
		gameScreen();
		checkDealAces();
		while (dealerTotal < handTotal -1 || dealerTotal < 18 ) {
			clearScreen();
			dealerDraw();
			gameScreen();
		}
		if (dealerTotal > handTotal &&	dealerTotal <= 21) {
			gameLost(bet);

		}
		else if (dealerTotal == handTotal) {
			gameDraw();

		}
		else if (dealerTotal > 21 || dealerTotal < handTotal) {
			gameWin();
			}
	}
}

void gameScreen() {  //prints out the game screen
		cout << "*************************************\n"
<< "**            DEALER                 \n"
<< "**       Dealer Total: "<<  dealerTotal <<"                           \n"
<< "**       " << dHand[0] << dHand[1] << "  " << dHand[2] << dHand[3] << "    " << dHand[4] << dHand[5] << "  " << dHand[6] << dHand[7] << "   " << dHand[8] << dHand[9] << "                \n"
<< "**                                   \n"
<< "**                                 \n"
<< "**    " << pSHand[0] << pSHand[1] << "  " << pSHand[2] << pSHand[3] << "   " << pSHand[4] << pSHand[5] << "    " << pSHand[6] << pSHand[7] << "  " << pSHand[8] << pSHand[9] <<"     \n"
<< "**    " << pHand[0] << pHand[1] << "  " << pHand[2] << pHand[3] << "   " << pHand[4] << pHand[5] << "    " << pHand[6] << pHand[7] << "  " << pHand[8] << pHand[9] << "       \n"
<< "**    " << "Current Total: " << setw(2) << handTotal << "   Current Bet: " << currentBet << "   \n"
<< "**            " << name << "                 \n"
<< "*************************************\n";
}



//section deals with winning and losing
int gameLost(int bet) {
	cout << "Sorry you have lost.";
	walet = walet - bet;
	return walet;
}

void gameDraw() {
	cout << "PUSH!!";
}

void gameWin() {
	cout << "You Win! \n";
	if (handTotal == 21 && cardCount == 2)
	{
		walet += currentBet * 1.5;
	}
	else 
	{
		walet += currentBet;
	}
}
//draws a card reads the first string adds it to the pHand Array checks for aces and then adds the suit to the next spot
void playerDraw() {
	
	pHand[ph] = rankName[shoe[dI]->rank];
	handTotal += getCardValue(shoe[dI]->rank);
	
	if (pHand[ph] == "14") {
		aces++;
	}

	ph++;
	pHand[ph] = shoe[dI]->Suit;
	ph++;
	dI++;
	cardCount++;

}
//draws a card reads the first string adds it to the pSHand Array checks for aces and then adds the suit to the next spot
void playerSplitDraw() {

	pSHand[psh] = rankName[shoe[dI]->rank];
	splitTotal += getCardValue(shoe[dI]->rank);
	if (pSHand[psh] == "14") {
		aces++;
	}
	psh++;
	pSHand[psh] = shoe[dI]->Suit;
	psh++;
	dI++;
	

}
//draws a card reads the first string adds it to the dHand Array checks for aces and then adds the suit to the next spot
void dealerDraw() {
	
	if (dh == 2) { //if its the second card drawn, hides it from player until they stay.
		dTemp[0] = rankName[shoe[dI]->rank];
		dealTempTotal += getCardValue(shoe[dI]->rank);
		if (dTemp[0] == "14") {
			aces++;
		}
		dh++;
		dTemp[1] = shoe[dI]->Suit;
		dh++;
		dI++;

		dHand[2] = "X";
		dHand[3] = "X";
	}
	else {
		dHand[dh] = rankName[shoe[dI]->rank];
		dealerTotal += getCardValue(shoe[dI]->rank);
		if (dHand[dh] == "14") {
			aces++;
		}
		dh++;
		dHand[dh] = shoe[dI]->Suit;
		dh++;
		dI++;
	}

}
//shuffles the deck then draws the first cards
void startGame() {
	shuffle();
	playerDraw();
	dealerDraw();
	playerDraw();
	dealerDraw();
}

//sets all positions back to starting values for next round
void clearRound() {
	dI = 0, ph = 0, dh = 0, dealerTotal = 0, dealTempTotal = 0, cardCount = 0, tempWalet = 0, handTotal=0, aces=0, sAces=0, dAces=0;
	pHand[0] = "", pHand[1] = "", pHand[2] = "", pHand[3] = "", pHand[4] = "", pHand[5] = "", pHand[6] = "", pHand[7] = "", pHand[8] = "", pHand[9] = "";
	pSHand[0] = "", pSHand[1] = "", pSHand[2] = "", pSHand[3] = "", pSHand[4] = "", pSHand[5] = "", pSHand[6] = "", pSHand[7] = "", pSHand[8] = "", pSHand[9] = "";
	dHand[0] = "", dHand[1] = "", dHand[2] = "", dHand[3] = "", dHand[4] = "", dHand[5] = "", dHand[6] = "", dHand[7] = "", dHand[8] = "", dHand[9] = "";
	play = true, game = true;
	shuffle();
}

void playAgain() { //asks user if they want to play another round
	cout << "Would you like to play again? Y/N";
	cin >> choice;
	choice = toupper(choice);
	while (play)
	{

		switch (choice)
		{
		case 'Y':
			break;
		case 'N':
		{
			play = false;
		
			break;
		}
		default: cout << "Please enter Y or N.";
		}
		break;
	}

}

void pairSplit() { //same code as normal play but with a secondary hand if your split a pair
	pSHand[0] = pHand[2];
	pSHand[1] = pHand[3];
	pHand[2] = "";
	pHand[3] = "";
	ph = 2;
	psh = 2;
	cardCount--;
	playerDraw();
	playerSplitDraw();


	cout << "What would you like to do with the first (Top) hand? \n H to Hit, S to Stay";
	
	while (choice != 'S') {
		checkSplitAces();
		if (splitCount == 5) {
			gameWin();
		}
		else if (dealerTotal == 21 && splitTotal != 21)
		{
			gameLost(bet);
			break;
		}
		else if (splitTotal >= 22)
		{
			gameLost(bet);
			break;
		}
		else if (splitTotal == 21) {
			gameWin();
			break;
		}
		else {
			cout << "What would you like to do?\n Press H to Hit \nPress S to Stand \n";
			cin >> choice;
			choice = toupper(choice);
		}
		switch (choice) {
		case 'H':
			playerSplitDraw();
			break;
		case 'S':
			break;
		default:
			cout << "Please enter H or S";
		}
		clearScreen();
		gameScreen();
	}
}


void checkAces() { //checks to see if you have an ace before busting your hand
	if (handTotal < 21 && aces != 0) {
		handTotal = handTotal - 10;
		aces--;
	}
}
void checkSplitAces() {
	if (splitTotal < 21 && sAces != 0) {
		splitTotal = splitTotal - 10;
		sAces--;
	}
}
	void checkDealAces() {
		if (handTotal < 21 && dAces != 0) {
			handTotal = handTotal - 10;
			dAces--;
		}
	}