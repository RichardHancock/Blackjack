#include <iostream>
#include <time.h>
#include <array>
#include <string>

using namespace std;

struct Card
{
	string name; 
	short value; // 0 for ace due to it being 1 or 11
	string suit;
};

struct Player
{
	int bet;
	int balance;
	int pIndex;
	int handTotal;
	Card hand[12];
};

struct Dealer
{
	int dIndex;
	int handTotal;
	Card hand[12];
};

//Function Prototypes
void shuffleDeck(void);
void drawCards(int,char);
int randomNumber(int,int);
void resetDeck(void);
string suitSwitch(string);
void checkForBlackjack(short);
void mainGameLoop();
short playersTurn();
short dealersTurn();
int handTotal(Card,short);
bool isBustCheck(int);
void resetHands(void);
void menuValidation(void);
void actionValidation(void);

//Card Values
const short ACE = 0;
const short FACECARD = 10;
//Special Characters
const char HEARTS = '\x03';
const char DIAMONDS = '\x04';
const char CLUBS = '\x05';
const char SPADES = '\x06';

const string CARDNAMES[13] = {"Ace","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};
const short NUM_OF_SUITS = 4;
const short NUM_OF_CARDS_PER_SUIT = 13;
const short NUM_OF_CARDS_IN_DECK = 52;

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

//Destroy all these start
Card g_deck[NUM_OF_CARDS_IN_DECK]; // Create a global int array to contain the deck
short g_positionInDeck;

Card g_playersHand[11];
short g_playersCardCount;
Card g_dealersHand[10];
short g_dealersCardCount;

int g_playerMoney = 1000;
//Destroy all these end

int randomNumber(int minimum, int maximum)
{
	return rand() % (maximum - minimum + 1) + minimum;
}

int handTotal(Card hand[], short cardCount)
{	
	short total = 0;
	short currentCardNum = 0;

	for(; currentCardNum < cardCount; currentCardNum++)
	{
		total += hand[currentCardNum].value;
	}
	
	return total;
}

string suitSwitch(string suit)
{
	
	if (suit == "Hearts")
	{
		return "Diamonds";
	}

	if (suit == "Diamonds")
	{
		return "Clubs";
	}
	
	if (suit == "Clubs")
	{
		return "Spades";
	}
	
	return "Done";
}

void resetHands(void)
{
	for (int i = 0; i < 11; i++)
	{
		g_playersHand[i].name = "";
		g_playersHand[i].value = -1;
		g_playersHand[i].suit = "";
		
		if (i < 10)
		{
			g_dealersHand[i].name = "";
			g_dealersHand[i].value = -1;
			g_dealersHand[i].suit = "";
		}
	}
	g_playersCardCount = 0;
	g_dealersCardCount = 0;
}

void resetDeck(void)
{
	// Seed random number generator
	srand(time(NULL));

	// Reset Deck
	string currentSuit = "Hearts";
	g_positionInDeck = 0;

	for (int j = 1; j <= NUM_OF_SUITS; j++)
	{
		for (int k = 1; k <= NUM_OF_CARDS_PER_SUIT; k++)
		{
			
			if (k >= 2 && k <= 10)
			{
				g_deck[g_positionInDeck].name = CARDNAMES[k-1];
				g_deck[g_positionInDeck].value = k;
				g_deck[g_positionInDeck].suit = currentSuit;
			}
			else
			{

				if (k >= 11 && k <= NUM_OF_CARDS_PER_SUIT) 
				{
					g_deck[g_positionInDeck].name = CARDNAMES[k-1];
					g_deck[g_positionInDeck].value = 10;
					g_deck[g_positionInDeck].suit = currentSuit;
				}
				else
				{
					if (k == 1) 
					{
						g_deck[g_positionInDeck].name = CARDNAMES[0];
						g_deck[g_positionInDeck].value = ACE;
						g_deck[g_positionInDeck].suit = currentSuit;
					}
				}

			}
			
			g_positionInDeck++;
		}
		currentSuit = suitSwitch(currentSuit);
	}

	g_positionInDeck = 0;
	
}

void shuffleDeck(void)
{
	Card temp;
	int index1 = 0, index2 = 0;

	for (index1 = 0; index1 < NUM_OF_CARDS_IN_DECK; index1++)
	{
		//With pointer might be able to make a copy struct functions
		index2 = randomNumber(0,51);
		
		temp.name = g_deck[index1].name;
		temp.suit = g_deck[index1].suit;
		temp.value = g_deck[index1].value;
		
		g_deck[index1].name = g_deck[index2].name;
		g_deck[index1].suit = g_deck[index2].suit;
		g_deck[index1].value = g_deck[index2].value;

		g_deck[index2].name = temp.name;
		g_deck[index2].suit = temp.suit;
		g_deck[index2].value = temp.value;
	}
}

void checkForBlackjack(short whoseCard) //TODO
{
	/* TODO
	switch (whoseCards)
	{
		case PLAYER:
			
		break;

		case DEALER:

		break;

		default:
			cout << "FATAL ERROR: check for blackjack was passed invalid variable (" << whoseCards << ")";
		break;
	}
	*/
}

void menuValidation(void) 
{

}

void actionValidation(void)
{
	
}

void drawCards(int amount, short toWho)  
{
	Card cardsDrawn[2]; //2 should be the maximum amount of concurrent card draws.

	if (amount < 0 || amount > 2)
	{
		cout << "FATAL ERROR: Invalid amount of cards were requested";
	}
	
	switch (toWho)
	{
		case PLAYER:
			for (int i = 0; i < amount; i++)
			{
				g_playersHand[g_playersCardCount].name = g_deck[g_positionInDeck].name;
				g_playersHand[g_playersCardCount].value = g_deck[g_positionInDeck].value;
				g_playersHand[g_playersCardCount].suit = g_deck[g_positionInDeck].suit;

				if (i == 0) 
				{
					cout << "Player drew ";
				}

				cout << g_playersHand[g_playersCardCount].name << " of " << g_playersHand[g_playersCardCount].suit;
				if (i < amount - 1)
				{
					cout << " and ";
				}
				else
				{
					cout << endl;
				}

				g_playersCardCount++;
				g_positionInDeck++;
			}
		break;

		case DEALER:
			for (int i = 0; i < amount; i++)
			{
				g_dealersHand[g_dealersCardCount].name = g_deck[g_positionInDeck].name;
				g_dealersHand[g_dealersCardCount].value = g_deck[g_positionInDeck].value;
				g_dealersHand[g_dealersCardCount].suit = g_deck[g_positionInDeck].suit;

				if (i == 0) 
				{
					cout << "Dealer drew ";
				}

				cout << g_dealersHand[g_dealersCardCount].name << " of " << g_dealersHand[g_dealersCardCount].suit;

				if (i < amount - 1)
				{
					cout << " and ";
				}
				else
				{
					cout << endl;
				}


				g_dealersCardCount++;
				g_positionInDeck++;
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

void mainGameLoop()
{
	bool gameState = true;

	while(gameState == true)
	{
		//Betting System
		cout << "Your Current Balance:" << player.balance << endl;
		cout << "Please enter your bet: ";
		cin >> Bet;
		//HERE

		drawCards(2, PLAYER);
		drawCards(2, DEALER);
		// Screen update function

		if (playersTurn() == BUST)
		{
			cout << "Player busted, Dealer Wins!\n\n";
		}
		else
		{
			if (dealersTurn() == BUST)
			{
				cout << "Dealer busted, Player Wins!\n\n";
			}
			else
			{
				short playersTotal = handTotal(g_playersHand, g_playersCardCount);
				short dealersTotal = handTotal(g_dealersHand, g_dealersCardCount);

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
		resetHands();
		if (g_positionInDeck > 51) {
			//Deck Finished
			gameState = false;
		}
		
	}
}

short playersTurn()
{
	bool turnContinuing = true;
	int playersCommand = 0;

	//blackjack check
	while(turnContinuing == true)
	{
		cout << "Dealers Hand Total: " << handTotal(g_dealersHand, g_dealersCardCount) << endl;
		cout << "Your Hand Total: " << handTotal(g_playersHand, g_playersCardCount) << endl;
		cout << "Hit or Stand:\n";
		cin >> playersCommand;
		// Need input validation/conversion later
		switch(playersCommand)
		{
			case 1:
				//hit
				drawCards(1,PLAYER);
				if(isBustCheck(handTotal(g_playersHand, g_playersCardCount)) == true)
				{
					//maybe replace with ternary
					return BUST;
				}
				break;
			case 2:
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

short dealersTurn() 
{
	bool turnContinuing = true;

	//blackjack check
	while(turnContinuing == true)
	{
		cout << "Dealers Hand Total: " << handTotal(g_dealersHand, g_dealersCardCount) << endl;

		if(handTotal(g_dealersHand, g_dealersCardCount) < 17)
		{
			//hit
			drawCards(1,DEALER);
			if (isBustCheck(handTotal(g_dealersHand, g_dealersCardCount)) == true)
			{
				return BUST;
			}
		}
		else
		{
			//stand
			turnContinuing = false;
		}
	}
	return NORMAL;
}

int main(void) 
{
	Player player;
	
	resetDeck();
	resetHands();
	shuffleDeck();
	mainGameLoop();
	
	/* debug loop
	for (int i = 0; i < 52; i++)
	{
		cout << i << ", " << g_deck[i].name << ", " << g_deck[i].value << ", " << g_deck[i].suit << endl;
	}

	debug hand display
	drawCards(2,PLAYER);
	drawCards(2,DEALER);
	cout << "Player Hand: "<< g_playersHand[0].name << ", " << g_playersHand[0].value << ", " <<  g_playersHand[0].suit << ";\n" << g_playersHand[1].name << ", " << g_playersHand[1].value << ", " << g_playersHand[1].suit << ";" << endl;
	cout << "Dealer Hand: "<< g_dealersHand[0].name << ", " << g_dealersHand[0].value << ", " <<  g_dealersHand[0].suit << ";\n" << g_dealersHand[1].name << ", " << g_dealersHand[1].value << ", " << g_dealersHand[1].suit << ";" << endl;
	*/
	//Menu loop
	//Cin plus validation
	//Switch statement
	//End Menu loop
	
	return 0;
}