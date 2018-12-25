#include "stdafx.h"
#include <iostream> 
#include <vector>
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
	Board board(20,7);
	srand(time(NULL));

	//GAME LOOP;
	//board.spawnEnemy(rand() % 7); //randomize the spawn location between 0 and 7.
	board.spawnEnemiesTEMPORARY();
	//board.spawnProjectile();
	board.spawnProjectilesTEMPORARY();
	cout << "GENERATED";
	board.draw();

	cout << "HARD CODED";
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
	cout << endl;
    return 0;
}