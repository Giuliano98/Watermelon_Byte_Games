#include <iostream>
#include <string>
#include <ctime>

using namespace std;


// Create a player class
class Players 
{
public:
	string name;
	int wins;
	bool turn;
	bool dice;
};

// Get and return the player's name
string getName(int i) 
{
	const int minCharacters = 6;
	string player;

	cout << "Player " << i << " enter your Username (min. Characters: 6): ";	
	do
	{
		cin >> player;
		if (player.length() < minCharacters)
			cout << "ERROR. Enter a username with at least " << minCharacters << " characters" << endl << endl;
		else 
			cout << "Valid username enter." << endl << endl;

	} while (player.length() < minCharacters);

	return player;
}

// Return a Random Num between <rangMin and a rangMax>
int generateRandNum(int rangMin, int rangMax) 
{
	return (rand() % rangMax) + rangMin;
}

// Return the max turns that the game could have
int bestOf(int maxRounds)
{
	return (maxRounds + 1) / 2;
}

// Update the current range where the secret number could be in
void updateRange(int &min, int &max, int guess, int randNum) 
{
	if (min < guess && guess < randNum)
		min = guess;
	if (guess < max && randNum < guess)
		max = guess;
}

// Reset the ranges to <1 - 100>
void resetRang(int &min, int &max) 
{
	min = 1;
	max = 100;
}

// Check if the player* won and add +1 o wins
void checkWinner(bool turn, int &wins) 
{
	if (turn)
		wins++;
}

// Set a random turn 
void randTurn(bool &p1Turn, bool &p2Turn) 
{
	p1Turn = generateRandNum(0, 2);
	p2Turn = !p1Turn;
}

// Reset game - reset all the var
void resetGame(int &min, int &max, int &rNum, int &guess)
{
	// Reset the playerGuess
	guess = 0;

	// Reset the ranges to <1 - 100>
	resetRang(min, max);

	// Reset the Rand Number
	rNum = generateRandNum(min, max);
}

/*Dice result Funtions*/
void slapOpponent(bool &pTurn, bool &pTurnOther)
{
	cout << "You just HYPER-slaped your opponent. You can play AGAIN!!!." << endl;
	pTurn = false;
	pTurnOther = true;
}

int newRandNum(int min, int max)
{
	cout << "There is a new random number between <" << min << " - " << max << ">." << endl;
	return generateRandNum(min, max);
}

void otherTip(int num)
{
	string tip = (num % 2) ? "Even." : "Odd.";
	cout << "Here is a little secret the number is " << tip << endl;
}

void spartan()
{
	cout << "You just became a legendary SPARTAN. You have to demostrated your skills doing 1 push-up irl." << endl;
}

int resetBestOf(int &rounds)
{
	cout << "You just reset the best-of 3 to 5. You are addicted to this video game. Thanks <3" << endl;
	return rounds = bestOf(5);
}

void exodia(int &wins) 
{
	cout << "You take the 5 cards out of your pocket and put it in the arena!!" << endl;
	cout << "Exodia The Forbidden One has been invoked. Exodia will flip a coin \nif it lands heads you will win automatically" << endl;
	if (generateRandNum(0,2))
	{
		cout << "It landed HEADS. You just won the GAME!" << endl;
		wins += 5;
	}
	else
	{
		cout << "It is not your day. It landed Tail." << endl;
	}
}


int main() 
{ 
	srand((unsigned)time(0));
	/*Starting Vars*/
	// Determinate the min and max ranges
	int rangMin = 1;
	int rangMax = 100;
	int guessMin = rangMin;
	int guessMax = rangMax;
	// Generate a randNum with the ranges above
	int randNum = generateRandNum(rangMin, rangMax);
	// Set the max of round (The best of "#")
	int maxRounds = bestOf(3);
	// Init. the player guess on a var
	int playerGuess = 0;
	// Answer for player
	int answer;
	// dice result
	int dice = 0;


	/*Init. The players*/
	Players player1;
	player1.name = getName(1);
	player1.wins = 0;
	player1.turn;
	player1.dice = true;

	Players player2;
	player2.name = getName(2);
	player2.wins = 0;
	player2.turn;
	player2.dice = true;

	// test pGaming
	Players pPlaying;
	Players pPlayingOther;


	/*Decide who start first*/
	// Who starts is random
	randTurn(player1.turn, player2.turn);


	/*Game Start*/
	// Loop until best of maxRounds
	while (player1.wins < maxRounds && player2.wins < maxRounds)
	{
		// Show randNum
		cout << randNum << endl << endl;

		do 
		{
			if (player1.turn)
			{
				pPlaying = player1;
				pPlayingOther = player2;
			}
			if (player2.turn)
			{
				pPlaying = player2;
				pPlayingOther = player1;
			}


			cout << "It is Player / " << pPlaying.name << " turn." << endl;
			cout << "Would you like to guess or roll a dice: \n 1) Guess\t2)Roll Dice: ";
			cin >> answer;

			if (answer == 2 && pPlaying.dice)
			{
				// player #'s dice !
				pPlaying.dice = !pPlaying.dice;
				// randNum <1 - 6>
				dice = generateRandNum(1, 6);
				cout << "You roll the dice. The result was: " << dice << endl;
				// switch case
				switch (dice)
				{
				case 1:
					slapOpponent(pPlaying.turn, pPlayingOther.turn);
					break;
				case 2:
					randNum = newRandNum(guessMin, guessMax);
					break;
				case 3:
					otherTip(randNum);
					break;
				case 4:
					spartan();
					break;
				case 5:
					exodia(pPlaying.wins);
					break;
				case 6:
					resetBestOf(maxRounds);
					break;
				default:
					break;
				}

				if (dice == 5)
					break;
			}
			else if (answer == 2 && !pPlaying.dice)
			{
				cout << "Player / " << pPlaying.name << " does not have a dice anymore." << endl;
			}

			updateRange(guessMin, guessMax, playerGuess, randNum);
			cout << "The secret number is between <" << guessMin << ", " << guessMax << ">" << endl;
			cin >> playerGuess;


			if (player1.turn)
			{
				player1 =  pPlaying;
				player2 =  pPlayingOther;
			}
			if (player2.turn)
			{
				player2 = pPlaying;
				player1 = pPlayingOther;
			}


			player1.turn = !player1.turn;
			player2.turn = !player2.turn;
		} while (!(playerGuess == randNum));


		// Check who won / also add a +1 to wins to the winner
		if (playerGuess == randNum)
		{
			checkWinner(!player1.turn, player1.wins);
			checkWinner(!player2.turn, player2.wins);
		}		

		// Resetting the game
		resetGame(guessMin, guessMax, randNum, playerGuess);
	}

	cout << "Player 1: " << player1.wins << " wins, Player 2: " << player2.wins << " wins" << endl << endl;

	return 0;
}