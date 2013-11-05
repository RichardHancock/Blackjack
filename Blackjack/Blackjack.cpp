#include <iostream>
#include <time.h>
#include <array>

using namespace std;

void initdeck(void);
int drawCard(int,char);
int randomNumber(int,int);
void resetDeck();

int g_deck [52]; // Create a global int array to contain the deck
int g_availableCards[52];
int g_playersHand[11] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int g_dealersHand[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

int randomNumber(int minimum, int maximum)
{
	return rand() % (maximum - minimum + 1) + minimum;
}

void resetDeck(void)
{
	srand(time(NULL));

	for (int i = 0; i < 52; i++)
	{
		g_availableCards[i] = 1;
	}
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
	drawCards(2,P);
	drawCards(2,D);
	//TODO: hide second dealer card function!

}

int drawCards(int amount, char toWho)  
{
	//toWho should contain a D for Dealer or P for Player
	int counter = 0;
	int timeout = 0;
	int cardsDrawn[2]; //2 should be the maximum amount of concurrent card draws.

	if (amount < 0)
	{
		cout << "ERROR: No cards were requested";
		return -1;
	}
	
	while (counter < amount)
	{	
		/*if (timeout > 1000)
		{
			cout << "ERROR: Draw card loop has failed to draw any cards after 1000 loops. Aborting";
			return -1;
		}

		timeout++;*/

		if (g_deck[cardValue] == 0) 
		{
			//Dont increase counter to force a redraw.
		}
		else
		{
			cardsDrawn[counter] = cardValue;
			counter++;
		}
	}
	 
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
	cout << "Player Hand: "<< g_playersHand[0] << ", " << g_playersHand[1];
	


	return 0;
}