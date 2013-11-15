#include <iostream>
#include <time.h>
#include <array>
#include <string>

using namespace std;

void shuffleDeck(void);
void drawCards(int,char);
int randomNumber(int,int);
void resetCards(void);
string suitSwitch(string);
void firstDraw(void);
bool checkForBlackjack(char);

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

Card g_deck[52]; // Create a global int array to contain the deck
short g_positionInDeck; // Set to short because var will never be above 52. Memory Saver, didnt set to char because it would require lots of casting.
short g_availableCards[52];

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

void deckFiller()
{
	
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

	Card temp[1];


	/*int i = 0;
	int timeout = 1000;
	
	while(i < 52)
	{
		timeout--;
		//cout << timeout << endl;
		int randomNum = randomNumber(0,51);

		if (g_availableCards[randomNum] == 1)
		{
			g_deck[i] = randomNum + 1;
			g_availableCards[randomNum] = 0;

			i++;
			timeout = 1000;
		}

		if (timeout < 1)
		{
			cout << "ERROR: initDeck loop took other 1000 attempts.\n";
			break;
		}
	}*/

}

bool checkForBlackjack(char whoseCard)
{
	/*
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
	*/
	return false;
	
}

void firstDraw(void)
{
	//Draw cards for first draw and hides dealer second card
	drawCards(2,'P');
	drawCards(2,'D');
	//TODO: hide second dealer card function!

}

void drawCards(int amount, char toWho)  
{
	/*
	//toWho should contain a D for Dealer or P for Player
	int cardsDrawn[2]; //2 should be the maximum amount of concurrent card draws.

	if (amount < 0 || amount > 2)
	{
		cout << "FATAL ERROR: Invalid amount of cards were requested";
	}
	
	switch (toWho)
	{
		case 'P':
			for (int i = 0; i < amount; i++)
			{
				g_playersHand[g_playersCardTotal] = g_deck[g_positionInDeck];
				g_playersCardTotal++;
				g_positionInDeck++;
			}
		break;

		case 'D':
			for (int i = 0; i < amount; i++)
			{
				g_dealersHand[g_dealersCardTotal] = g_deck[g_positionInDeck];
				g_dealersCardTotal++;
				g_positionInDeck++;
			}
		break;
		
		default:
			cout << "FATAL ERROR: Invalid toWho value passed to drawCards function";
		break;
	}
	for (int i = 0; i < amount; i++)
	{	
		cardsDrawn[i] = cardValue;	
	}*/
    
}

int main(void) 
{
	
	resetCards();
	
	// debug loop
	for (int i = 0; i < 52; i++)
	{
		cout << i << ", " << g_deck[i].name << ", " << g_deck[i].value << ", " << g_deck[i].suit << endl;
	}
	firstDraw();
	//debug hand display
	//cout << "Player Hand: "<< g_playersHand[0] << ", " << g_playersHand[1];
	//cout << "Dealer Hand: "<< g_dealersHand[0] << ", " << g_dealersHand[1];
	
	


	return 0;
}