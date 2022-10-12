//Kathryn Kaelin
//Lab 6 Out
//Lottery ball game

#include <iostream>
#include <math.h>
#include "Lottery.h"
#include "graph1.h"

using namespace std;

int main()
{
	int no_balls = 0;
	int num = 0;
	int target = 0;
	int i = 0;
	int winnings = 0;
	bool result = false;
	Lottery player;

	srand(time(0));

	//Display graphics
	displayGraphics();

	//Get number of lottery balls (force user to reenter number if parameters are not met)

	do {
		cout << "How many lottery balls do you want to play: ";
		cin >> no_balls;
		result = player.setNoBalls(no_balls);

		if (result == false) {
			cout << "***ERROR*** Please re-enter the number." << endl;
		}

	} while (result == false);

	//Prompt user for the numbers for each lottery ball

	for (int i = 0; i < no_balls; i++) {
		result = false;
		do {
			cout << "Enter lottery # " << i + 1 << " <between 1 and 40>: ";
			cin >> num;
			result = player.addNumber(num);
			if (result == false) {
				cout << "***ERROR***Please re-enter the number." << endl;
			}
		} while (result == false);
	}

	//Sort and display lottery numbers the user entered
	player.selectionSort();
	player.displayYourNumbers();

	//Process and display winning balls
	player.processWinningNumbers();

	//Calculate winnings
	winnings = player.computeWinnings();

	//Display number of balls played, number of matches, and winnings
	gout << setPos(100, 60) << "Number of Balls Played: " << player.getNoBalls() << endg;
	gout << setPos(100, 80) << "Number of Matches: " << player.getMatches() << endg;
	gout << setPos(100, 100) << setPrecision(2) << "Your Payout: $" << winnings * 1.0 << endg;

	return 0;
}