#include "Lottery.h"
#include <iostream>
#include <math.h>
#include "graph1.h"

Lottery::Lottery()
{
	no_balls = 0;
	yourNumbers = NULL;
	winningNumbers = NULL;
	matches = 0;
}

Lottery::~Lottery()
{
	delete[] yourNumbers;
	delete[] winningNumbers;
}

int Lottery::getNoBalls()
{
	return no_balls;
}

bool Lottery::setNoBalls(int no_balls) //The return value will be false if its input parameter is less than 3 or greater than 10 inclusively.
{
	int i = 0;
	bool result = false;

	if (no_balls < 3) {
		this->no_balls = 3;
		return result;
	}
	else if (no_balls > 10) {
		this->no_balls = 10;
		return result;
	}
	else {
		this->no_balls = no_balls;
		result = true;
		yourNumbers = new int[this->no_balls];
		for (int i = 0; i < no_balls; i++) {
			yourNumbers[i] = 0;
		}
		winningNumbers = new int[this->no_balls];
		for (int i = 0; i < no_balls; i++) {
			winningNumbers[i] = 0;
		}
		return result;
	}	
}

//Inserts a number into the "yourNumbers" array into the next unfilled element
bool Lottery::addNumber(int num)
{
	bool result = false;
	int i = 0;

	if (num < 1) {
		return result;
	}
	else if (num > 40) {
		return result;
	}
	else {
		for (i = 0; i <= no_balls - 1; i++) {
			if (yourNumbers[i] == 0) {
				yourNumbers[i] = num;
				result = true;
				return result;
			}
		}
	}
	
}

void Lottery::displayYourNumbers()
{
	int i = 0;
	int x = 40, y = 320;
	//Sleep(1000 * 1); //Sleep function uses miliseconds --> 1000 miliseconds = 1 second

	for (i = 0; i < no_balls; i++) {
		displayBMP(to_string(yourNumbers[i]) + ".bmp", x, y);
		Sleep(1000);
		x += 60;
	}
	gout << setPos(40, 375) << "Your Numbers" << endg;
}

void Lottery::processWinningNumbers()
{
	bool duplicate = false;
	int i = 0, j = 0;
	int x = 40, y = 220;

	//Create winning numbers
	for (i = 0; i < no_balls; i ++) {
		winningNumbers[i] = rand() % 40 + 1;
		do {
			duplicate = false;
			for (j = 0; j < i; j++) {
				if (winningNumbers[i] == winningNumbers[j]) {
					winningNumbers[i] = rand() % 40 + 1;
					duplicate = true;
					break;
				}
			}
		} while (duplicate);
	}
	//Display winning numbers
	for (i = 0; i < no_balls; i++) {
		displayBMP(to_string(winningNumbers[i]) + ".bmp", x, y);
		Sleep(1000);
		x += 60;
	}
	//Sort winning numbers
	insertionSort();

	Sleep(3000);
	x = 40;
	for (i = 0; i < no_balls; i++) {
		displayBMP(to_string(winningNumbers[i]) + ".bmp", x, y);
		x += 60;
	}
	gout << setPos(40, 285) << "Winning Numbers" << endg;
}

void Lottery::selectionSort()
{
	int i = 0, j = 0;
	int temp = 0;
	int smallest = 0;
	int sm_index = 0;

	for (i = 0; i < no_balls - 1; i++) {
		smallest = yourNumbers[i];
		sm_index = i;
		for (j = i + 1; j < no_balls; j++) {
			if (yourNumbers[j] < smallest) {
				smallest = yourNumbers[j];
				sm_index = j;
			}
		}
		if (smallest < yourNumbers[i]) {
			temp = yourNumbers[i];
			yourNumbers[i] = yourNumbers[sm_index];
			yourNumbers[sm_index] = temp;
		}
	}
}

void Lottery::insertionSort()
{
	int i = 0, j = 0, k = 0;
	for (i = 1; i < no_balls; i++) {
		k = winningNumbers[i];
		j = i;
		while (j > 0 && winningNumbers[j - 1] > k) {
			winningNumbers[j] = winningNumbers[j - 1];
			j--;
		}
		winningNumbers[j] = k;
	}
}

int Lottery::getMatches()
{
	return matches;
}

int Lottery::binarySearch(int target)
{
	int low = 0;
	int high = 0;
	int middle = 0;
	bool result = false;

	high = no_balls - 1;

	while((low <= high) && (!result)){
		middle = (low + high) / 2;

		if (winningNumbers[middle] == target) {
			result = true;
		}
		else if (target > winningNumbers[middle]) {
			low = middle + 1;
		}
		else {
			high = middle - 1;
		}
	}

	return result;
}

int Lottery::computeWinnings()
{
	int i = 0;
	double winnings = 0;
	bool result;

	for (i = 0; i < no_balls; i++) {

		result = binarySearch(yourNumbers[i]);
		if (result == true) {
			matches++;
		}
	}

	winnings = pow(10.0, matches);

	return winnings;
}