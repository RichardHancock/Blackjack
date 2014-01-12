#include <iostream>
#include <time.h>
#include <array>
#include <cstring>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

//Card Values
const short ACE = 11;
const short FACECARD = 10;
//Special Characters
const char HEARTS = '\x03';
const char DIAMONDS = '\x04';
const char CLUBS = '\x05';
const char SPADES = '\x06';
const char CHAR_NULL = '\0';

//CHANGEconst string CARDNAMES[13] = {"Ace","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};
const short NUM_OF_SUITS = 4;
const short NUM_OF_CARDS_PER_SUIT = 13;
const short NUM_OF_CARDS_IN_DECK = 52;
const short MAX_NUM_OF_CARDS_IN_HAND = 12; //11 is the max, but 12th is the card that will cause bust
//Player Actions
const short HIT = 1;
const short STAND = 2;

//Identifiers
const short PLAYER = 1;
const short DEALER = 2;

//Turn States
const short NORMAL = 1;
const short BLACKJACK = 2;
const short BUST = 3;

//Validation Types
const short MENU = 1;
const short P_ACTION_CHECK = 2; //hit or stick validation
const short BETTING = 3;

//Stucture Declarations
struct Card
{
	char name[6]; 
	short value; // 0 for ace due to it being 1 or 11
	char suit;
};

struct Deck
{
	short posInDeck; //Current position in the deck
	Card cards[52];
};

struct Player
{
	int bet;
	int balance;
	int handTotal;
	int numOfCards;
	Card hand[MAX_NUM_OF_CARDS_IN_HAND]; // Maximum possible cards
};

struct Dealer
{
	int handTotal;
	int numOfCards;
	Card hand[MAX_NUM_OF_CARDS_IN_HAND];
};

//Function Prototypes
void shuffleDeck(Deck &);
void drawCards(int,char, Deck &, Player &, Dealer &);
int randomNumber(int,int);
void resetDeck(Deck &);
char suitSwitch(char);
short checkForBlackjack(Player &, Dealer &);
void mainGameLoop(Deck &, Player &, Dealer &);
short playersTurn(Deck &, Player &, Dealer &);
short dealersTurn(Deck &, Player &, Dealer &);
int handTotal(Card,short);
bool isBustCheck(int);
void resetHands(Player &, Dealer &);
short validation(short, Player &);
void resetGame(Player &);



int main(void) 
{
	Deck deck;

	Player player;
	Dealer dealer;
	
	bool running = true;
	
	while(running == true) 
	{
		cout << "Blackjack V1.0" << endl << "By: Richard Hancock" << endl;
		cout << "\n\n1 - Play" << endl << "2 - Rules" << endl << "3 - Exit"<< endl;
		cout << "Press the number for the option you want to access, followed by Enter." << endl;
		short menuAction = 0;
		menuAction = validation(MENU, player);
		system("CLS");
	
		switch (menuAction)
		{
			case 1: //Play
				resetGame(player);
				resetDeck(deck);
				resetHands(player, dealer);
				shuffleDeck(deck);
				mainGameLoop(deck, player, dealer);
			break;

			case 2:
				cout << "Rules" << endl;
				cout << "In blackjack the objectice is to get as close to 21 with out going over. You play against the dealer and must have a hand of cards higher than theirs to win." << endl;
				cout << "The player places a bet on each round and if they win their bet is doubled, but if you win by a black jack (10 + Ace on first draw) you get a bonus." << endl;
				cout << "The player has the option to Hit or Stand every round. Hitting gives the player another card, while standing sticks with the players current cards.\n"<< endl;
			break;

			case 3:
				return 0;
			break;

			default:
				cout << "FATAL ERROR: menu passed invalid menuAction var";
			break;

		}
	}

}

int randomNumber(int minimum, int maximum)
{
	return rand() % (maximum - minimum + 1) + minimum;
}

int handTotal(Card hand[], short cardCount)
{	
	short total = 0;
	short aceCount = 0;

	for(short currentCardNum = 0; currentCardNum < cardCount; currentCardNum++)
	{
		if (hand[currentCardNum].value == ACE)
		{
			aceCount++;
		}
		total += hand[currentCardNum].value;
	}
	if (total > 21) 
	{
		total - (10 * aceCount);
	}
	return total;
}

char suitSwitch(char suit)
{
	switch (suit) {
		case HEARTS:
			return DIAMONDS;
		break;

		case DIAMONDS:
			return CLUBS;
		break;
		
		case CLUBS:
			return SPADES;
		break;

		default:
			return CHAR_NULL;
		break;
	}
}

void resetGame(Player &player) 
{
	// Seed random number generator
	srand(time(NULL));

	// Reset players balance
	player.balance = 1000;
}

void resetDeck(Deck &deck)
{		
	char currentSuit = HEARTS;
	deck.posInDeck = 0;

	for (int suitIterator = 1; suitIterator <= NUM_OF_SUITS; suitIterator++) // Loop through every suit
	{

		for (int cardIterator = 1; cardIterator <= NUM_OF_CARDS_PER_SUIT; cardIterator++) //Loop through every card in a suit
		{

			if (cardIterator >= 2 && cardIterator <= 9)
			{
				deck.cards[deck.posInDeck].name[0] = (48 + cardIterator); //ASCII position of 0 plus current number
				deck.cards[deck.posInDeck].name[1] = CHAR_NULL; //Correctly ending CharArray
				deck.cards[deck.posInDeck].value = cardIterator;
				deck.cards[deck.posInDeck].suit = currentSuit;
			}
			else
			{

				if (cardIterator >= 11 && cardIterator <= NUM_OF_CARDS_PER_SUIT) 
				{
					deck.cards[deck.posInDeck].value = 10;
					deck.cards[deck.posInDeck].suit = currentSuit;
					switch (cardIterator) {
						case 11:
							strcpy(&deck.cards[deck.posInDeck].name[0],"Jack");
						break;
						case 12:
							strcpy(&deck.cards[deck.posInDeck].name[0],"Queen");
						break;
						case 13:
							strcpy(&deck.cards[deck.posInDeck].name[0],"King");
						break;
					}
				}
				else
				{

					if (cardIterator == 1) 
					{
						strcpy(&deck.cards[deck.posInDeck].name[0],"Ace");
						deck.cards[deck.posInDeck].value = ACE;
						deck.cards[deck.posInDeck].suit = currentSuit;
					}
					else //10 card
					{
						strcpy(&deck.cards[deck.posInDeck].name[0],"10");
						deck.cards[deck.posInDeck].value = 10;
						deck.cards[deck.posInDeck].suit = currentSuit;
					}
				}

			}

			//Switch to next card in deck
			deck.posInDeck++;
		}

		// Switch to next suit
		currentSuit = suitSwitch(currentSuit);
	}

	//Set position back to the top of the deck
	deck.posInDeck = 0;
	
}

void resetHands(Player &player, Dealer &dealer)
{
	for (int i = 0; i < MAX_NUM_OF_CARDS_IN_HAND; i++)
	{
		player.hand[i].name[0] = CHAR_NULL;
		player.hand[i].value = -1;
		player.hand[i].suit = CHAR_NULL;
		
		dealer.hand[i].name[0] = CHAR_NULL;
		dealer.hand[i].value = -1;
		dealer.hand[i].suit = CHAR_NULL;
	}
	player.numOfCards = 0;
	dealer.numOfCards = 0;

	player.bet = 0;
}

void shuffleDeck(Deck &deck)
{

	int index1 = 0, index2 = 0;

	for (index1 = 0; index1 < NUM_OF_CARDS_IN_DECK; index1++)
	{
		Card temp;
		//With pointer might be able to make a copy struct functions
		index2 = randomNumber(0,51);
		
		strcpy(&temp.name[0], deck.cards[index1].name);
		temp.suit = deck.cards[index1].suit;
		temp.value = deck.cards[index1].value;
		
		strcpy(deck.cards[index1].name, deck.cards[index2].name);
		deck.cards[index1].suit = deck.cards[index2].suit;
		deck.cards[index1].value = deck.cards[index2].value;

		strcpy(deck.cards[index2].name, temp.name);
		deck.cards[index2].suit = temp.suit;
		deck.cards[index2].value = temp.value;

	}
}

short checkForBlackjack(Player &player, Dealer &dealer) //TODO
{
	bool playerBlackjack = false;
	bool dealerBlackjack = false;

	if (handTotal(player.hand, player.numOfCards) == 21) 
	{
		playerBlackjack = true;
	}
	if (handTotal(dealer.hand, dealer.numOfCards) == 21) 
	{
		dealerBlackjack = true;
	}

	if (playerBlackjack == true && dealerBlackjack == true)
	{
		return 3; //Both have blackjack
	}
	else
	{
		if (playerBlackjack == true)
		{
			return PLAYER;
		}
		else
		{
			if (dealerBlackjack == true)
			{
				return DEALER;
			}
			else
			{
				return 0;
			}
		}
	}
}

short validation(short type, Player &player) 
{	
	bool Valid = false;
	char toValidate[10];

	switch (type) //See type definition constants at top of code
	{
		case MENU:
			while (Valid == false) 
			{
				cin >> toValidate[0]; 
				if (toValidate[0] == '1' || toValidate[0] == '2' || toValidate[0] == '3')
				{
					Valid = true;
					return atoi(toValidate);
				}
			}
		break;
		case P_ACTION_CHECK:
			while (Valid == false) 
			{
				cin >> toValidate;

				for(short i = 0; i <= strlen(toValidate); i++)
				{
					toValidate[i] = tolower(toValidate[i]);
					
				}
				
				if ((toValidate[0] == 'h') && 
					(toValidate[1] == 'i') && 
					(toValidate[2] == 't'))
				{
					Valid = true;
					return HIT;
				}
				else
				{
					if ((toValidate[0] == 's') && 
						(toValidate[1] == 't') && 
						(toValidate[2] == 'a') && 
						(toValidate[3] == 'n') &&  
						(toValidate[4] == 'd'))
					{
						Valid = true;
						return STAND;
					}
				}

			}
		break;
		case BETTING:
			while (Valid == false) 
			{
				cin >> toValidate;
				
				Valid = true; // Set intially to true, so that if a problem doesnt occur the loop will end

				for (short j = 0; j < strlen(toValidate); j++)
				{
					if (toValidate[j] >= 47 && toValidate[j] >= 58) // if var is not a number in ASCII set
					{
						Valid = false;
					}
					
				}
				if (player.bet > player.balance)
				{
					Valid = false;
				}
				else
				{
					if (player.bet = 0)
					{
						Valid = false;
					}
				}
			}
			return atoi(toValidate);
		break;
		default:
			cout << "FATAL ERROR: Invalid type given to validation function" << endl;
			return 0;
		break;
	}
}

void drawCards(int amount, short toWho, Deck &deck, Player &player, Dealer &dealer)  
{

	if (amount < 0 || amount > 2)
	{
		cout << "FATAL ERROR: Invalid amount of cards were requested";
	}
	
	switch (toWho)
	{
		case PLAYER:
			for (int i = 0; i < amount; i++)
			{
				strcpy(player.hand[player.numOfCards].name, deck.cards[deck.posInDeck].name);
				player.hand[player.numOfCards].value = deck.cards[deck.posInDeck].value;
				player.hand[player.numOfCards].suit = deck.cards[deck.posInDeck].suit;

				if (i == 0) 
				{
					cout << "Player drew ";
				}

				cout << player.hand[player.numOfCards].name << " of " << player.hand[player.numOfCards].suit;
				if (i < amount - 1)
				{
					cout << " and ";
				}
				else
				{
					cout << endl;
				}
				
				deck.posInDeck++;
				player.numOfCards++;
			}
		break;

		case DEALER:
			for (int i = 0; i < amount; i++)
			{
				

				strcpy(dealer.hand[dealer.numOfCards].name, deck.cards[deck.posInDeck].name);
				dealer.hand[dealer.numOfCards].value = deck.cards[deck.posInDeck].value;
				dealer.hand[dealer.numOfCards].suit = deck.cards[deck.posInDeck].suit;

				if(i == 0) //only displays the first card the dealers draws, but not second.
				{
				cout << "Dealer drew " << dealer.hand[dealer.numOfCards].name << " of " << dealer.hand[dealer.numOfCards].suit << endl;
				}
				deck.posInDeck++;
				dealer.numOfCards++;
			}
		break;
		
		default:
			cout << "FATAL ERROR: Invalid toWho value passed to drawCards function";
		break;
	}
}

bool isBustCheck(int cardTotal)
{
	if (cardTotal > 21) 
	{
		return true;
	}
	else
	{
		return false;
	}
}

void mainGameLoop(Deck &deck, Player &player, Dealer &dealer)
{
	bool gameState = true;

	while(gameState == true)
	{
		//Betting System
		cout << "Your Current Balance:" << player.balance << endl;
		cout << "Please enter your bet: ";
		player.bet = validation(BETTING, player);
		player.balance -= player.bet;
		system("CLS");


		drawCards(2, PLAYER, deck, player, dealer);
		drawCards(2, DEALER, deck, player, dealer);
		
		short blackjackCheckResults = checkForBlackjack(player, dealer);

		if (blackjackCheckResults == 0) //If a Blackjack did not occur
		{
			if (playersTurn(deck, player, dealer) == BUST) // If the player busted
			{
				cout << "Player busted, Dealer Wins!\n\n";
			}
			else
			{
				if (dealersTurn(deck, player, dealer) == BUST) // If the dealer busted
				{
					cout << "Dealer busted, Player Wins!\n\n";
				}
				else
				{
					short playersTotal = handTotal(player.hand, player.numOfCards);
					short dealersTotal = handTotal(dealer.hand, dealer.numOfCards);

					if(playersTotal == dealersTotal)
					{
						//Draw
						cout << "Draw!\n\n";
					}
					else
					{
						if(playersTotal > dealersTotal)
						{
							//PlayerWins
							cout << "Player Wins!\n\n";
						}
						else
						{
							//DealerWins
							cout << "Dealer Wins!\n\n";
						}
					}
				}
			}
		}
		else
		{
			switch(blackjackCheckResults)
			{
				case PLAYER:
					cout << "Blackjack! Player Wins!\n\n";
					player.balance += (2.5 * player.bet);
				break;

				case DEALER:
					cout << "Blackjack! Dealer Wins!\n\n";
				break;

				case 3: // Both
					cout << "Two Blackjacks! It's a draw!\n\n";
					player.balance += player.bet;
				break;
			}
		}

		resetHands(player, dealer);
		if (deck.posInDeck > (NUM_OF_CARDS_IN_DECK - (MAX_NUM_OF_CARDS_IN_HAND * 2)) - 1) 
		{
			resetDeck(deck);
			gameState = false;
		}
		
	}
}

short playersTurn(Deck &deck, Player &player, Dealer &dealer)
{
	bool turnContinuing = true;
	short playersCommand = 0;

	//blackjack check
	while(turnContinuing == true)
	{
		cout << "Dealers Hand Total: " << dealer.hand[0].value << endl;
		cout << "Your Hand Total: " << handTotal(player.hand, player.numOfCards) << endl;
		cout << "Hit or Stand:" << endl;
		playersCommand = validation(P_ACTION_CHECK, player);
		// Need input validation/conversion later
		switch(playersCommand)
		{
			case HIT:
				//hit
				drawCards(1,PLAYER, deck, player, dealer);
				if(isBustCheck(handTotal(player.hand, player.numOfCards)) == true)
				{
					//maybe replace with ternary
					return BUST;
				}
				break;
			case STAND:
				//stand
				turnContinuing = false;
			break;
			default:
				turnContinuing = false;
				cout << "ERROR: 1 or 2 was not inputted";
			break;
		}
	}
	return NORMAL;
}

short dealersTurn(Deck &deck, Player &player, Dealer &dealer) 
{
	bool turnContinuing = true;

	//blackjack check
	while(turnContinuing == true)
	{
		cout << "Dealers Hand Total: " << handTotal(dealer.hand, dealer.numOfCards) << endl;

		if(handTotal(dealer.hand, dealer.numOfCards) < 17)
		{
			//hit
			drawCards(1,DEALER, deck, player, dealer);
			if (isBustCheck(handTotal(dealer.hand, dealer.numOfCards)) == true)
			{
				return BUST;
			}
		}
		else
		{
			//stand
			cout << "Dealer Stands" << endl;
			turnContinuing = false;
		}
		cout << "Press Enter to Continue..." << endl;
		cin.get();
		cin.ignore();
	}

	return NORMAL;
}

