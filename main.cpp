#include <iostream>
#include <string>
#include <vector>

#include "Cards.h"
void PlayGame();
void PrintInstructions();


using namespace std;
int main()
{
	char userChoice;
	cout << "Hello, welcome to Texas Hold em' assistance program!" << endl << endl;
	cout << "Menu: \n" << "a - New Game \n" << "b - See Instructions \n" << "q - Quit" << endl << endl;
	cin >> userChoice;
	
	while (userChoice != 'q')
	{
		
		switch (userChoice)
		{
		case 'a':
			PlayGame();
			break;
		case 'b':
			PrintInstructions();
			break;
		case 'q':
			cout << "Goodbye!" << endl;
			break;
		default:
			cout << "Invalid selection" << endl;
		}
		cout << "Menu: \n" << "a - New Game \n" << "b - See Instructions \n" << "q - Quit" << endl << endl;
		cin >> userChoice;
	}


	return 0;
}

void PlayGame()
{
	int players = 0;
	string card1;
	string card2;
	string flopcard1;
	string flopcard2;
	string flopcard3;
	string turnCard;
	cout << "How many players are in the game?" << endl; 
	cin >> players;
	cout << "What is your 1st card?" << endl;
	cin >> card1;
	cout << "What is your 2nd card?" << endl;
	cin >> card2;

	cout << "Your Hand: " << card1 << " " << card2 << endl;
	Cards game(card1, card2, players);
	cout << "Your preflop hand strength is: " << game.PreFlopValue() << endl;
	game.EvaluateHands();
	game.PrintProbs();

	cout << "What is the 1st flop card?" << endl; 
	cin >> flopcard1;
	cout << "What is the 2nd flop card?" << endl;
	cin >> flopcard2;
	cout << "What is the 3rd flop card?" << endl;
	cin >> flopcard3;
	

	// flop
	game.AddCard(flopcard1);
	game.AddCard(flopcard2);
	game.AddCard(flopcard3);
	game.IncGameState();
	game.EvaluateHands();
	game.PrintProbs();


	// Turn
	cout << "What is the Turn Card?" << endl;
	cin >> turnCard;

	game.AddCard(turnCard);
	game.IncGameState();
	game.EvaluateHands();
	game.PrintProbs();

	// River
}
void PrintInstructions()
{
	cout << "When prompted for a card please enter the card accordingly: " << endl;
	cout << "Begin with the value of the card followed by the suit." << endl;
	cout << "The value must be a numerical value 0-9 and capitalized alphabetical values (T-A) corresponding to the first letter in their names for values 10 and higher." << endl;
	cout << "The suit will follow and must be a capitalized letter corresponding to the first letter in its name i.e. C, S, D, H" << endl;

}