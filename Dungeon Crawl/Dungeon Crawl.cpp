// Dungeon Crawl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <random>
using std::cout;
using std::cin;
using std::endl;

int playerCurrentTile = 0;
int playerNextTile = 0;

int m1CurrentTile = 8;	//monster current tiles
int m2CurrentTile = 52;
int m3CurrentTile = 66;

char moveDirection;
bool isDead = false;
bool isWon = false;

std::random_device ranDev;
std::uniform_int_distribution<int> intDis(0, 3);

void loadMap(std::vector<char> theMap);
void move(std::vector<char> & theMap, char theDirection);
void monsterMove(std::vector<char> & theMap, int & mCurrentTile, int theDirection);	//changes monster positions by reference so player can process them in map


int main()
{	
	std::vector<char> map = {
	'.', '.', '.', '.', 'T', '.', '.', '.', 'M', '.',
	'.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
	'.', '.', '.', '.', 'T', '.', '.', '.', '.', '.',
	'.', '.', '.', '.', '.', '.', 'T', '.', '.', '.',
	'.', '.', '.', '.', '.', '.', '.', '.', 'T', '.',
	'.', '.', 'M', '.', '.', '.', '.', '.', 'T', 'X',
	'.', '.', '.', '.', '.', '.', 'M', '.', '.', '.',
	};

	
	while (isWon == false && isDead == false)
	{
		
		system("cls");	

		cout << "Enter w,a,s,d to move up, left, down, right. Reach the X to win, step on a trap to die." << endl << endl;

		loadMap(map);

		if (playerCurrentTile == m1CurrentTile || playerCurrentTile == m2CurrentTile || playerCurrentTile == m3CurrentTile)	//Test once after monsters move and after map reloads
		{
			cout << "A monster ate you" << endl;
			isDead = true;
			break;
		}

		cout << endl << "Enter move direction: ";
		cin >> moveDirection;
		move(map, moveDirection);

		if (playerCurrentTile == m1CurrentTile || playerCurrentTile == m2CurrentTile || playerCurrentTile == m3CurrentTile)	//Test another time after player moves in case he runs into a monster
		{
			cout << "A monster ate you" << endl;
			isDead = true;
			break;
		}

		monsterMove(map, m1CurrentTile, intDis(ranDev));
		monsterMove(map, m2CurrentTile, intDis(ranDev));
		monsterMove(map, m3CurrentTile, intDis(ranDev));
	
	}



	char pause;
	cout << endl << "Enter anything to quit: ";
	cin >> pause;

    return 0;
}

void loadMap(std::vector<char> theMap)
{
	if (theMap[playerCurrentTile] != 'M')	//If monster ate player then it takes its place, so we don't want to overwrite 'M' with 'P'
	{
		theMap[playerCurrentTile] = 'P';
	}

	cout << theMap[0] << " " << theMap[1] << " " << theMap[2] << " " << theMap[3] << " " << theMap[4] << " " << theMap[5] << " " << theMap[6] << " " << theMap[7] << " " << theMap[8] << " " << theMap[9] << endl;
	cout << theMap[10] << " " << theMap[11] << " " << theMap[12] << " " << theMap[13] << " " << theMap[14] << " " << theMap[15] << " " << theMap[16] << " " << theMap[17] << " " << theMap[18] << " " << theMap[19] << endl;
	cout << theMap[20] << " " << theMap[21] << " " << theMap[22] << " " << theMap[23] << " " << theMap[24] << " " << theMap[25] << " " << theMap[26] << " " << theMap[27] << " " << theMap[28] << " " << theMap[29] << endl;
	cout << theMap[30] << " " << theMap[31] << " " << theMap[32] << " " << theMap[33] << " " << theMap[34] << " " << theMap[35] << " " << theMap[36] << " " << theMap[37] << " " << theMap[38] << " " << theMap[39] << endl;
	cout << theMap[40] << " " << theMap[41] << " " << theMap[42] << " " << theMap[43] << " " << theMap[44] << " " << theMap[45] << " " << theMap[46] << " " << theMap[47] << " " << theMap[48] << " " << theMap[49] << endl;
	cout << theMap[50] << " " << theMap[51] << " " << theMap[52] << " " << theMap[53] << " " << theMap[54] << " " << theMap[55] << " " << theMap[56] << " " << theMap[57] << " " << theMap[58] << " " << theMap[59] << endl;
	cout << theMap[60] << " " << theMap[61] << " " << theMap[62] << " " << theMap[63] << " " << theMap[64] << " " << theMap[65] << " " << theMap[66] << " " << theMap[67] << " " << theMap[68] << " " << theMap[69] << endl;
	
}

void move(std::vector<char> & theMap, char theDirection)
{
	switch (moveDirection)
	{
	case 'w':
		playerNextTile = (playerCurrentTile - 10);	//purpose of two step assignment to current tile is to test valid value first and prevent assignment if out of range
		if (playerNextTile >= 0 && playerNextTile <= 69)
		{
			playerCurrentTile = playerNextTile;
		}
		break;

	case 'a':
		playerNextTile = (playerCurrentTile - 1);
		if ( (playerCurrentTile % 10) != 0 )	//prevent teleporting to right side of previous row by moving left on left wall
		{
			if (playerNextTile >= 0 && playerNextTile <= 69)
			{
				playerCurrentTile = playerNextTile;
			}
		}
		break;

	case 's':
		playerNextTile = (playerCurrentTile + 10);
		if (playerNextTile >= 0 && playerNextTile <= 69)
		{
			playerCurrentTile = playerNextTile;
		}
		break;

	case 'd':
		playerNextTile = (playerCurrentTile + 1);
		if ( ((playerCurrentTile - 9) % 10) != 0)	////prevent teleporting to left side of next row by moving right on right wall
		{
			if (playerNextTile >= 0 && playerNextTile <= 69)
			{
				playerCurrentTile = playerNextTile;
			}
		}
		break;
		
	default: cout << "Invalid input" << endl;
	}

	
	if (theMap[playerCurrentTile] == 'T')
	{
		cout << "You stepped on a trap and died." << endl;
		isDead = true;
		cin.ignore();	// In case multiple inputs happen and one of them steps on the trap and the next input in the buffer fills the pause at the end of main and ends the program.
	}
	if (theMap[playerCurrentTile] == 'X')
	{
		cout << "You got the treaure!" << endl;
		isWon = true;
		cin.ignore();	// In case multiple inputs happen and one of them steps on the treasure and the next input in the buffer fills the pause at the end of main and ends the program.
	}
	
}

void monsterMove(std::vector<char> & theMap, int & mCurrentTile, int theDirection)
{
	//Monsters can teleport through sides to previous/next row
	switch (theDirection)
	{
	case 0: //step up
		if ( (mCurrentTile - 10) >= 0 )		//Testing for valid value before testing for valid range because the mere act of testing an invalid range is an error
		{
			if ((theMap[mCurrentTile - 10] == '.' || theMap[mCurrentTile - 10] == 'P') )
			{
				theMap[mCurrentTile - 10] = 'M';
				theMap[mCurrentTile] = '.';
				mCurrentTile -= 10;
			}
		}
		break;
	case 1:	//step down
		if ((mCurrentTile + 10) <= 69)
		{
			if ((theMap[mCurrentTile + 10] == '.' || theMap[mCurrentTile + 10] == 'P') )
			{
				theMap[mCurrentTile + 10] = 'M';
				theMap[mCurrentTile] = '.';
				mCurrentTile += 10;
			}
		}
		break;
	case 2:	//step left
		if ((mCurrentTile - 1) >= 0)
		{
			if ((theMap[mCurrentTile - 1] == '.' || theMap[mCurrentTile - 1] == 'P') )
			{
				theMap[mCurrentTile - 1] = 'M';
				theMap[mCurrentTile] = '.';
				mCurrentTile -= 1;
			}
		}
		break;
	case 3:	//step right
		if ((mCurrentTile + 1) >= 69)
		{
			if ((theMap[mCurrentTile + 1] == '.' || theMap[mCurrentTile + 1] == 'P') )
			{
				theMap[mCurrentTile + 1] = 'M';
				theMap[mCurrentTile] = '.';
				mCurrentTile += 1;
			}
		}
		break;
	default: 
		break;

	}
}