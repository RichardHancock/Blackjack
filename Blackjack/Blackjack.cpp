#include <iostream>
#include <time.h>
#include <array>

using namespace std;

void initdeck(void);
void drawCards(int,char);
int randomNumber(int,int);
void resetDeck(void);
void firstDraw(void);

short g_deck [52]; // Create a global int array to contain the deck
short g_positionInDeck; // Set to short because var will never be above 52. Memory Saver, didnt set to char because it would require lots of casting.
short g_availableCards[52];

short g_playersHand[11];
short g_playersCardTotal;
short g_dealersHand[10];
short g_dealersCardTotal;

int randomNumber(int minimum, int maximum)
{
	return rand() % (maximum - minimum + 1) + minimum;
}

void resetDeck(void)
{
	srand(time(NULL));
	for (int i = 0; i < 11; i++)
	{
		g_playersHand[i] = -1;
		
		if (i < 10)
		{
			g_dealersHand[i] = -1;
		}
	}
	g_playersCardTotal = 0;
	g_dealersCardTotal = 0;

	for (int j = 0; j < 52; j++)
	{
		g_availableCards[j] = 1;
	}
	g_positionInDeck = 0;
	
}

void initDeck(void)
{
	int i = 0;
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
	}

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
	/*for (int i = 0; i < amount; i++)
	{	
		cardsDrawn[i] = cardValue;	
	}*/
	 
}

int main(void) 
{
	resetDeck();
	initDeck();
	// debug loop
	/*for (int i = 0; i < 52; i++)
	{
		cout << g_deck[i] << endl;
	}*/
	firstDraw();
	//debug hand display
	cout << "Player Hand: "<< g_playersHand[0] << ", " << g_playersHand[1];
	cout << "Player Hand: "<< g_dealersHand[0] << ", " << g_dealersHand[1];

	


	return 0;
}