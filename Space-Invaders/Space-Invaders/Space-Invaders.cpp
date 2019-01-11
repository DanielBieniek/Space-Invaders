#include "stdafx.h"
#include <iostream> 
#include <deque> 
#include <windows.h> //sleep
#include <cstdlib> //srand, rand
#include <ctime> //time for rand

//CUSTOM HEADERS:
#include "Entity.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Player.h"
#include "Board.h"
using namespace std;

/*
TODO:
	- change enemies to array/vector/deque of deques of enemies, so that it's possible to check only one row, not all of them
	- check projectile hit on enemy
	- stop loop if player lost all their lives
	- point system
*/

int main()
{
	Board board;

	srand(time(NULL));
	
	int frame = 0;
	double time_counter = 0;
	clock_t this_time = clock();
	clock_t last_time = this_time;
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
				//DO 3.(3) TIMES A SECOND
				if (GetKeyState(VK_UP) & 0x8000)
				{
					board.movePlayer(-1);
				}
				if (GetKeyState(VK_DOWN) & 0x8000)
				{
					board.movePlayer(1);
				}
				if (GetKeyState(VK_SPACE) & 0x8000)
				{
					board.spawnProjectile();
				}
				if (GetKeyState(VK_SHIFT) & 0x8000)
				{
					board.moveEnemies();
				}
				board.moveProjectiles();
			}

			if (frame % 30 == 0) {
				//DO EVERY THREE SECONDS
				board.moveEnemies();
				board.spawnEnemy(rand() % board.BoardHeight()); //spawn new enemy
			}
			//DO 10 TIMES A SECOND
			board.draw();
			frame++;
		}
	}
    return 0;
}