/*
	CP3 PROJECT
	Daniel Bieniek
	AEiI Macrofaculty sem.3 group.3
	Teacher: Anna Gorawska

	CP3 project requirements:
	- at least 5 classes [DONE]
	- at least 4 topics:

	1. Inheritance [DONE]
	2. Polymorphism [DONE]
	3. Multiple inheritance
	4. RTTI
	5. Templates
	6. Exceptions [DONE]
	7. i/o streams [DONE]
*/

#include "stdafx.h"
#include <iostream>
#include <deque>
#include <vector>
#include <conio.h> //used for menu choice input
#include <windows.h> //keyboard detection
#include <cstdlib> //srand, rand
#include <ctime> //time for rand
#include <iomanip> //manipultion of i/o streams. used for points with leading zeros: i.e 091 points

//CUSTOM HEADERS:
#include "Entity.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Player.h"
#include "Board.h"
#include "Menu.h"
using namespace std;

int main()
{
	gameMenu();
	system("cls");

	Board board;
	srand(time(NULL)); //needed for rand()
	int frame = 0;					//
	double time_counter = 0;		// used for time management
	clock_t this_time = clock();	//
	clock_t last_time = this_time;	//
	int moveDir = 0; // 0-dont move. 1-move down. -1-move up
	bool shoot = false;

	//GAME LOOP
	while (board.gameLoop)
	{
		//TIME CALCULATIONS
		this_time = clock();
		time_counter += this_time - last_time;
		last_time = this_time;
		//GET KEY STATES AND UPDATE EVENT VARIABLES
		if ((moveDir != -1) && (GetKeyState(VK_UP) & 0x8000)) //on key UP
		{
			moveDir = -1;
		}
		if ((moveDir != 1) && (GetKeyState(VK_DOWN) & 0x8000)) //on key DOWN
		{
			moveDir = 1;
		}
		if ((shoot != true) && (GetKeyState(VK_SPACE) & 0x8000)) //on key SPACE
		{
			shoot = true;
		}

		if (time_counter >= CLOCKS_PER_SEC / 10) //do every 0.1 second
		{
			time_counter -= CLOCKS_PER_SEC / 10; //reset timer
			if (frame % 3 == 0) { //DO EVERY 3 FRAMES
				if (shoot) {
					board.spawnProjectile(); //create projectile at player location
				}
				if (moveDir) {
					board.movePlayer(moveDir); //move player up or down
				}
				moveDir = 0;
				shoot = false;
				board.moveProjectiles();
				board.checkProjectiles();
			}
			if (frame % 10 == 0) { //DO EVERY SECOND
				board.moveEnemies();
				board.spawnEnemy(rand() % board.BoardHeight()); //spawn new enemy
			}
			board.draw();
			frame++;
		}
	}

	//outputs "GAME OVER" with the number of points. If the player has only 1 point it doesn't write "points" in plural
	cout << endl << endl << "\t       GAME OVER" << endl << "\t   You got " << board.getPoints() << " point" << (board.getPoints() == 1 ? "" : "s") << "." << endl << endl;
	cout << "Press Enter to exit." << endl;
	getchar(); //it's here to prevent accidental closing of the game. waits for the player to press enter in order to close the game

    return 0;
}