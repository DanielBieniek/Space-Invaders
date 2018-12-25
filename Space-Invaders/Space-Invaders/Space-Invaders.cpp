#include "stdafx.h"
#include <iostream> 
#include <vector>
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

int main()
{
	Board board(20, 7);

	srand(time(NULL));

	int frame = 1;
	double time_counter = 0;
	clock_t this_time = clock();
	clock_t last_time = this_time;
	//GAME LOOP
	while (true)
	{
		//TIME CALCULATIONS
		this_time = clock();
		time_counter += this_time - last_time;
		last_time = this_time;
		
		if (time_counter >= CLOCKS_PER_SEC/10) 
		{
			time_counter -= CLOCKS_PER_SEC/10;
			frame++;

			if (frame % 10 == 0) {
				//DO EVERY SECOND
				board.EverySecond();
			}
			//DO 5 TIMES A SECOND
			board.EveryFrame();

		}

	}



	//

	/*
	board.spawnEnemy(rand() % 7);
	board.spawnProjectile();
	board.spawnEnemiesTEMPORARY();
	board.spawnProjectilesTEMPORARY();
	*/

	/*cout << "HARD CODED";
	cout << endl;
	cout << "\t|-ooo----------------|" << endl;
	cout << "\t|                #   |" << endl;
	cout << "\t|                   #|" << endl;
	cout << "\t| >  -             # |" << endl;
	cout << "\t|           -        |" << endl;
	cout << "\t|               #    |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|--------------------|" << endl;
	cout << endl;*/
    return 0;
}