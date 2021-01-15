#ifndef _CARDS_
#define _CARDS_
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

class Cards
{
public:
	Cards()
	{
		card1val = 0;
		card2val = 0;
		card1suit = " ";
		card2suit = " ";

		numPlayers = 0;
	}
	Cards(std::string card)
	{
		card1val = AssignValue(card);
		card1suit = card[1];
		card1origVal = card[0];
	}
	Cards(std::string card1, std::string card2, size_t players)
	{
		card1val = AssignValue(card1);
		card1origVal = card1[0];
		card1suit = card1[1];
		card2val = AssignValue(card2);
		card2origVal = card2[0];
		card2suit = card2[1];
		numPlayers = players;
		deckTotal = 52 - (2 * numPlayers);
	}
	~Cards() = default;
	int AssignValue(std::string card)
	{
		char val = card[0];
		int numVal = 0;
		switch (val)
		{
		case '2':
			numVal = 2;
			break;
		case '3':
			numVal = 3;
			break;
		case '4' :
			numVal = 4;
			break;
		case '5' :
			numVal = 5;
			break;
		case '6' :
			numVal = 6;
			break;
		case '7' :
			numVal = 7;
			break;
		case '8' :
			numVal = 8;
			break;
		case '9' :
			numVal = 9;
			break;
		case 'T' :
			numVal = 10;
			break;
		case 'J' :
			numVal = 11;
			break;
		case 'Q' :
			numVal = 12;
			break;
		case 'K' :
			numVal = 13;
			break;
		case 'A' :
			numVal = 14;
			break;
		default :
			std::cout << "Invalid card:" << std::endl;
			numVal = 0;
			
		}
		return numVal;
	}
	double PreFlopValue() // calculates a starting hand value based on "The Chen Formula" for expressing high card strength
	{
		double	handStrength = 0;
		if (card1val < 11) // Number Cards
		{
			handStrength += (static_cast<double>(card1val) / 2);
		}
		else if (card1val == 14) // Ace
		{
			handStrength += 10;
		}
		else if (card1val == 13) // King
		{
			handStrength += 8;
		}
		else if (card1val == 12) // Queen
		{
			handStrength += 7;
		}
		else if (card1val == 11) // Jack
		{
			handStrength += 6;
		}
		if (card2val < 11) // Number cards
		{
			handStrength += (static_cast<double>(card2val) / 2);
		}
		else if (card2val == 14) // Ace
		{
			handStrength += 10;
		}
		else if (card2val == 13) // King
		{
			handStrength += 8;
		}
		else if (card2val == 12) // Queen
		{
			handStrength += 7;
		}
		else if (card2val == 11) // Jack
		{
			handStrength += 6;
		}
		if (card1val == card2val) //Pair
		{
			handStrength *= 2;
			if (handStrength <= 5)
			{
				if (handStrength == 5)
				{
					handStrength = 6;
				}
				else
				{
					handStrength = 5;
				}
			}
		}
		if (card1suit == card2suit) //Suited
		{
			handStrength += 2;
		}
		int gapperVal = card1val - card2val;
		gapperVal = abs(gapperVal);
		if (gapperVal == 2)
		{
			handStrength--;
		}
		else if (gapperVal == 3)
		{
			handStrength -= 2;
		}
		else if (gapperVal == 4)
		{
			handStrength -= 4;
		}
		else if (gapperVal > 4)
		{
			handStrength -= 5;
		}
		else if (gapperVal == 1)
		{
			handStrength++;
		}
		return handStrength;
	}
	double One_Pair()
	{
		double probPair;
		
		if (card1val == card2val)
		{
			pair = true;
			return 1.0;
		}
		if (gameState == 0) // Flop
		{

			probPair = ((6 * (comb(11, 2) * comb(4, 1) * comb(4, 1))) / comb(deckTotal, 3));
		}
		else if (gameState == 1) // Turn 
		{
			probPair = 15 / deckTotal;
		}
		else if (gameState == 2)
		{
			probPair = 18 / deckTotal;
		}
		
			return probPair;
	}
	double Two_Pair()
	{ 
		if (twoPair)
			return 1.0;

		double pTwoPair = 0.0;
		if (pair)
		{
			if (gameState == 0) // Pre Flop
			{
				pTwoPair = ((6.0 * (comb(11.0, 2.0) * comb(4.0, 1.0) * comb(4.0, 1.0))) / comb(deckTotal, 3.0));
			}
			else if (gameState == 1) // Pre Turn
			{
				pTwoPair = 9.0 / deckTotal;
			}
			else if (gameState == 2) // Pre River
			{
				pTwoPair = 12.0 / deckTotal;
			}
		}
		else
		{
			if (gameState == 0) // Pre Flop
			{
				pTwoPair = (comb(3.0, 1.0) * comb(3.0, 1.0) * comb(deckTotal, 1.0)) / (comb(deckTotal, 3.0));
			}
			else if (gameState == 2.0) // Turn and River
			{
				pTwoPair = (12.0 / deckTotal);
			}
			
		}
		return pTwoPair;
	}
	double Three_Of_A_Kind()
	{
		if (threeKind)
			return 1.0;
		double probThreeKind = 0.0;
		if (pair) // One Pair hole cards
		{
			if (gameState == 0) //Pre Flop
			{
				probThreeKind = 1.0 - ((48.0 / deckTotal) *(47.0 / deckTotal - 1.0) * (46.0 / deckTotal - 2.0));
			}
			else if (gameState == 1) // Pre Turn
			{
				probThreeKind = 1.0 - (45.0 / (deckTotal));
			}
			else if (gameState == 2) // Pre River
			{
				probThreeKind = 1.0 - (44.0 / (deckTotal));
			}

		}
		else
		{
			if (gameState == 0) //Pre Flop
			{
				probThreeKind = (comb(3.0, 1.0) * comb(2.0, 1.0) * comb(deckTotal, 1.0)) / (comb(deckTotal, 3.0));
			}
			else if (gameState == 2 || gameState == 1) // Pre Turn
			{
				probThreeKind = 2.0 / deckTotal;
			}
			
		}
		return probThreeKind;
	}
	double Flush()
	{
		double flushProb = 0.0;
		int numSuited = NumSuitMatches();
		
		if (suited)
		{
			if (gameState == 0) // Flop
			{
				flushProb = (11.0 / deckTotal) * (10.0 / deckTotal - 1.0)  * (9.0 / deckTotal - 2.0);
			}
			else if (gameState == 1 && numSuited == 4) // Turn
			{
				flushProb = 9.0 / deckTotal;
			}
			else if (gameState == 2 && numSuited == 4) // River
			{
				flushProb = 9.0 / deckTotal;
			}
		}
		else
		{
			if (gameState == 1 && numSuited == 4 ) // Turn
			{
				flushProb = 9.0 / deckTotal;
			}
			else if (gameState == 2 && numSuited == 4) // River
			{
				flushProb = 9.0 / deckTotal;
			}
		
		}
		return flushProb;
	}
	double Full_House()
	{
		if (fullHouse)
			return 1.0;
		double pFullHouse;
		if (pair)
		{
			if (gameState == 0) //Flop
			{
				pFullHouse = (comb(3.0, 1.0) * comb(2.0, 1.0) * comb(deckTotal, 1.0)) / (comb(deckTotal, 3.0));
			}
			else if ((gameState == 1 || gameState == 2) && twoPair) // Turn & River
			{
				pFullHouse = 4.0 / deckTotal;
			}
			else
				pFullHouse = 0.0;

		}
		else if (threeKind)
		{
			if (gameState == 1) // turn
			{
				pFullHouse = 6.0 / deckTotal;
			}
			else if (gameState == 2) // river
			{
				pFullHouse = 9.0 / deckTotal;
			}
		}
		else
		{
			pFullHouse = 0.0;
		}
		return pFullHouse;
	}
	double Four_Of_A_Kind()
	{
		if (fourKind)
			return 1.0;
		double pFourKind = 0.0;
		if (pair)
		{
			if (gameState == 0) // Flop
			{
				pFourKind = ((6.0 * (comb(11.0, 2.0) * comb(4.0, 1.0) * comb(4.0, 1.0))) / comb(deckTotal, 3.0));
			}
			else if (gameState == 1 ) //Turn 
			{
				pFourKind = 9.0 / deckTotal;
			}
			else if (gameState == 2 && !twoPair) // River
			{
				pFourKind = 12.0 / deckTotal;
			}
		}
		else if (fullHouse) // Only possible at River
		{
			if (gameState == 1 || gameState == 2) // Turn & River
			{
				pFourKind = 1 / deckTotal;
			}
		}
		else if (threeKind)
		{
			pFourKind = 1 / deckTotal;
		}
		return pFourKind;
	}
	double Royal_Flush()
	{
		double pRoyalFlush = 0.0;
		if ((card1val > 9 && royalFlush) || (card2val > 9 && card1val > 9) || (royalFlush && card2val > 9))
		{
			if ((card2val > 9 && card1val > 9) && (card1suit == card2suit) && gameState == 0)
			{
				pRoyalFlush = (6.0 * comb(11, 3) * comb(3, 1) * comb(3, 1) / comb(deckTotal, 3.0));
			}
			else if ((card1val > 9 && royalFlush) || (royalFlush && card2val > 9) && gameState > 0)
			{
				pRoyalFlush = 1.0 / deckTotal;
			}
		}
		return pRoyalFlush;
	}
	double Straight()
	{
		double pStraight = 0.0;
		int gapperVal = card1val - card2val;
		gapperVal = abs(gapperVal);
		if (gapperVal >= 4 && gameState > 0 )
		{
			return 0.0;
		}
		if (gapperVal < 4)
		{
			if (gameState == 0 && !pair) 
			{
				pStraight = (6.0 * (comb(9.0, 1)) * (comb(8.0, 1)) * (comb(7.0, 1)) / comb(deckTotal, 3.0));
			}
			else if (gameState > 0 && !pair) // Turn
			{
				pStraight = 6.0 / deckTotal;
			}
		}
		
		return pStraight;
	}
	
	double Straight_Flush()
	{
		return Straight() * Flush();
	}
	
	void IncGameState()
	{
		++gameState;
	}
	void AddCard(std::string card)
	{
		Cards newCard(card);
		board.push_back(newCard);
		++numBoardCards;
		--deckTotal;
	}
	double comb(double n, double r) // Combinations
	{
		return fact(n) / (fact(r) * fact(n - r));
	}
	double fact(double  n) //factorial
	{
		double val = 1;
		for (int i = 2; i <= n; ++i)
		{
			val = val * i;
		}
		return val;
	}
	void EvaluateHands()
	{
		if (card1suit == card2suit)
			suited = true;
		if (card1val == card2val)
			pair = true;
		int numMatches = 0;
		int secMatches = 0;
		std::vector<Cards>tmpBoard = board;
		bool card1already = false;
		bool card2already = false;
		int curMatch = 0;
		int prevMatch = curMatch;
		bool difMatch = false;
		if (pair)
		{
			curMatch = card1val;
			prevMatch = curMatch;
			++numMatches;

		}
		for (size_t i = 0; i < board.size(); i++) //used to evaluate the number of matches found to determine one pair, three of a kind, and four of a kind
		{
			
			int tmp = tmpBoard.at(0).card1val;
			
			if (tmp == card1val && !card1already)
			{
				curMatch = tmp;
				card1already = true;
				if (difMatch)
				{
					++secMatches;
				}
				else
				{
					++numMatches;
				}
			}
			if (tmp == card2val && !card2already)
			{
				curMatch = tmp;
				card2already = true;
				if (difMatch)
				{
					++secMatches;
				}
				else
				{
					++numMatches;
				}
			}
			for (size_t j = 1; j < board.size() - 1; j++)
			{
				if (tmp == board.at(j).card1val && i != j)
				{
					curMatch = tmp;
					if (curMatch != prevMatch && prevMatch != 0)
						difMatch = true;

					if (difMatch)
					{
						++secMatches;
					}
					else
					{
						++numMatches;
					}
					
				}
				
			}
			prevMatch = curMatch;
			tmpBoard.erase(tmpBoard.begin());
			
		}
		if ((numMatches > 0 || secMatches > 0) && !difMatch)
		{
			pair = true;
			std::cout << "You Have a Pair!" << std::endl;
		}
		 if ((numMatches > 0 && secMatches > 0))
		{
			twoPair = true;
			std::cout << "You Have a Two Pair!" << std::endl;
		}
		if ((numMatches == 3 || secMatches == 3))
		{

			threeKind = true;
			std::cout << "You Have Three of a Kind!" << std::endl;
		}
		else if (numMatches == 4 || secMatches == 4)
		{
			
				fourKind = true;
				std::cout << "You Have Four of a Kind!" << std::endl;
			
		}
		if ((numMatches == 1 && secMatches == 2) || (numMatches == 2 && secMatches == 1) && difMatch)
		{
			fullHouse = true;
			std::cout << "You Have a Full House!" << std::endl;
		}
		
		//Check Royal Flush possibility
		int royalQualify = 0;
		std::vector<Cards> royalQualifiers;
		if (card1val > 9)
		{
			royalQualify++;
			
		}
		if (card2val > 9)
		{
			royalQualify++;
		}
		for (size_t i = 0; i < board.size(); i++)
		{
			if (board.at(i).card1val > 9)
			{
				royalQualify++;
				royalQualifiers.push_back(board.at(i));
			}
		}
		if (royalQualify >= 3)
		{
			bool royal = false;
			int suits = NumSuitMatches();
			if (royalQualify == suits)
			{
				royal = true;
			}
			
			if (royal)
			{
				royalFlush = true;
			}
		}
	}
	int NumSuitMatches()
	{
		
		int numcard1suited = 0;
		int numcard2suited = 0;
		for (size_t i = 0; i < board.size(); i++)
		{
			if (board.at(i).card1suit == this->card1suit)
			{
				++numcard1suited;
			}
			if (board.at(i).card1suit == this->card2suit)
			{
				++numcard2suited;
			}
		}
		if (suited)
		{
			return (numcard1suited + numcard2suited);
		}
		else if (numcard1suited > numcard2suited)
		{
			return numcard1suited;
		}
		else
		{
			return numcard2suited;
		}
	}
	void PrintProbs()
	{
		std::vector<std::string> winningHands{ "Pair", "Two-Pair", "Three of a Kind", "Straight", "Flush", "Full House", "Four of a Kind", "Straight Flush", "Royal Flush" };
		std::string round;
		if (gameState == 0)
		{
			round = "Flop";
		}
		else if (gameState == 1)
		{
			round = "Turn";
		}
		else if (gameState == 2)
		{
			round = "River";
		}
		std::cout << "Your Cards: " << card1origVal << card1suit << " " << card2origVal << card2suit << std::endl;
		std::cout << "Board Cards: " << std::endl;
		for (size_t i = 0; i < board.size(); i++)
		{
			std::cout << board.at(i).card1origVal << board.at(i).card1suit << " ";
		}
		std::cout << std::endl << std::endl;
		
		for (size_t i = 0; i < 9; i++)
		{
			double probVal = 0.0;
			switch (i) 
			{
			case 0:
				probVal = One_Pair();
				break;
			case 1:
				probVal = Two_Pair();
				break;
			case 2:
				probVal = Three_Of_A_Kind();
				break;
			case 3:
				probVal = Straight();
				break;
			case 4:
				probVal = Flush();
				break;
			case 5:
				probVal = Full_House();
				break;
			case 6:
				probVal = Four_Of_A_Kind();
				break;
			case 7:
				probVal = Straight_Flush();
				break;
			case 8:
				probVal = Royal_Flush();
				break;

			default:
				std::cout << "Not Implemented Yet ";
				break;
			}
			std::cout << std::fixed << std::setprecision(5) << "Probability of hitting a " << winningHands.at(i) << " at the " << round << ": " << probVal << std::endl;
		}
		std::cout << std::endl << std::endl;
	}
	size_t card1val;
	size_t card2val;
	std::string card1suit;
	std::string card2suit;
	std::vector<Cards> board;
	size_t numBoardCards = 0;
	int deckTotal;
	size_t numPlayers;
	int gameState = 0;
	char card1origVal;
	char card2origVal;

	bool suited = false;
	bool twoPair = false;
	bool threeKind = false;
	bool pair = false;
	bool flush = false;
	bool straight = false;
	bool fourKind = false;
	bool fullHouse = false;
	bool straightFlush = false;
	bool royalFlush = false;

};
#endif;
