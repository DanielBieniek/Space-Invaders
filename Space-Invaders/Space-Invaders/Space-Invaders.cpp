
/*
	CP3 PROJECT
	Daniel Bieniek
	AEiI Macrofaculty sem.3 group.3
	Teacher: Anna Gorawska
*/

#include "stdafx.h"
#include <iostream>
#include <deque>
#include <vector>
#include <windows.h> //keyboard detection
#include <cstdlib> //srand, rand
#include <ctime> //time for rand
#include <iomanip> //used for points with leading zeros: i.e 091 points

//CUSTOM HEADERS:
#include "Entity.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Player.h"
#include "Board.h"
using namespace std;

/*
CP3 project topic requirements:
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

int main()
{
	Board board;

	srand(time(NULL)); //needed for rand()
	
	int frame = 0;					//
	double time_counter = 0;		// used for time management
	clock_t this_time = clock();	//
	clock_t last_time = this_time;	//
	//GAME LOOP
	while (board.gameLoop)
	{
		//TIME CALCULATIONS
		this_time = clock();
		time_counter += this_time - last_time;
		last_time = this_time;
		
		if (time_counter >= CLOCKS_PER_SEC/10) 
		{
			time_counter -= CLOCKS_PER_SEC/10;

			if (frame % 3 == 0) {
				//DO EVERY 3 FRAMES
				if (GetKeyState(VK_UP) & 0x8000) //on key UP
				{
					board.movePlayer(-1); //move player up
				}
				if (GetKeyState(VK_DOWN) & 0x8000) //on key DOWN
				{
					board.movePlayer(1); //move player up
				}
				if (GetKeyState(VK_SPACE) & 0x8000) //on key SPACE
				{
					board.spawnProjectile(); //create projectile at player location
				}
				if (GetKeyState(VK_SHIFT) & 0x8000) //on key SHIFT
				{
					board.moveEnemies(); //move and create enemies. speeds up the game. used for debugging player death. shouldn't be in final project
					board.spawnEnemy(rand() % board.BoardHeight());
					board.checkPlayerLives();
				}
				board.moveProjectiles();
				board.checkProjectiles();
			}

			if (frame % 10 == 0) {
				//DO EVERY SECOND
				board.moveEnemies();
				board.spawnEnemy(rand() % board.BoardHeight()); //spawn new enemy
				board.checkPlayerLives();
			}
			//DO 10 TIMES A SECOND
			board.draw();
			frame++;
		}
	}

	//outputs "GAME OVER" with the number of points. If the player has only 1 point it doesn't write "points" in plural
	cout << endl << endl << "\t\tGAME OVER" << endl << "\t    You got " << board.getPoints() << " point" << (board.getPoints() == 1 ? "" : "s") << "." << endl << endl;

	getchar(); //it's here to prevent accidental closing of the game. waits for the player to press enter in order to close the game

    return 0;
}