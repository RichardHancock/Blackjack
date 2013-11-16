#include <iostream>
#include <time.h>
#include <array>
#include <string>

using namespace std;

//Function Prototypes
void shuffleDeck(void);
void drawCards(int,char);
int randomNumber(int,int);
void resetCards(void);
string suitSwitch(string);
//bool checkForBlackjack(char);

struct Card
{
	string name;
	short value; // 0 for ace due to it being 1 or 11
	string suit;
};

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
const short PLAYER = 1;
const short DEALER = 2;

Card g_deck[NUM_OF_CARDS_IN_DECK]; // Create a global int array to contain the deck
short g_positionInDeck;

Card g_playersHand[11];
short g_playersCardTotal;
Card g_dealersHand[10];
short g_dealersCardTotal;


int randomNumber(int minimum, int maximum)
{
	return rand() % (maximum - minimum + 1) + minimum;
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

void resetCards(void)
{
	// Seed random number generator
	srand(time(NULL));

	// Reset Hands
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
	g_playersCardTotal = 0;
	g_dealersCardTotal = 0;


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

/*bool checkForBlackjack(char whoseCard)
{
	
	switch (whoseCards)
	{
		case 'P':
			
		break;

		case 'D':

		break;

		default:
			cout << "FATAL ERROR: check for blackjack was passed invalid variable (" << whoseCards << ")";
		break;
	}
	
	return false;
	
}*/

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
				g_playersHand[g_playersCardTotal].name = g_deck[g_positionInDeck].name;
				g_playersHand[g_playersCardTotal].value = g_deck[g_positionInDeck].value;
				g_playersHand[g_playersCardTotal].suit = g_deck[g_positionInDeck].suit;

				g_playersCardTotal++;
				g_positionInDeck++;
			}
		break;

		case DEALER:
			for (int i = 0; i < amount; i++)
			{
				g_dealersHand[g_dealersCardTotal].name = g_deck[g_positionInDeck].name;
				g_dealersHand[g_dealersCardTotal].value = g_deck[g_positionInDeck].value;
				g_dealersHand[g_dealersCardTotal].suit = g_deck[g_positionInDeck].suit;

				g_dealersCardTotal++;
				g_positionInDeck++;
			}
		break;
		
		default:
			cout << "FATAL ERROR: Invalid toWho value passed to drawCards function";
		break;
	}
}

int main(void) 
{
	
	resetCards();
	shuffleDeck();
	// debug loop
	for (int i = 0; i < 52; i++)
	{
		cout << i << ", " << g_deck[i].name << ", " << g_deck[i].value << ", " << g_deck[i].suit << endl;
	}

	//debug hand display
	drawCards(2,PLAYER);
	drawCards(2,DEALER);
	cout << "Player Hand: "<< g_playersHand[0].name << ", " << g_playersHand[0].value << ", " <<  g_playersHand[0].suit << ";\n" << g_playersHand[1].name << ", " << g_playersHand[1].value << ", " << g_playersHand[1].suit << ";" << endl;
	cout << "Dealer Hand: "<< g_dealersHand[0].name << ", " << g_dealersHand[0].value << ", " <<  g_dealersHand[0].suit << ";\n" << g_dealersHand[1].name << ", " << g_dealersHand[1].value << ", " << g_dealersHand[1].suit << ";" << endl;
	
	return 0;
}