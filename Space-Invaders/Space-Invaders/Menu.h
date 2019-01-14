#pragma once

void instructions(); //prototype, necessary because instructions() uses gameMenu(), and gameMenu() uses instructions().

void gameMenu() {
	char choice = '0';
	do {
		choice = '0';
		system("cls");
		cout << endl << "\t   SPACE-INVADERS" << endl;
		cout << "\t by  Daniel Bieniek" << endl;
		cout << endl << "\t1. Start" << endl;
		cout << "\t2. Instructions" << endl;
		cout << "\t3. Exit";
		choice = _getch();
		cout << endl;
		switch (choice) {
		case '1': //start: leave this function to start the game loop
			break;
		case '2': //instructions: display game menu
			instructions();
			break;
		case '3': //exit
			cout << endl;
			exit(0);
			break;
		default: //loop back to menu
			choice = '0';
			break;
		}
	} while (choice == '0');
}

void instructions() {
	char choice = '0';
	do {
		choice = '0';
		system("cls");

		cout << endl << "\t    INSTRUCTIONS:" << endl << endl;
		cout << "\tKeybinds:" << endl;
		cout << "\tUP arrow - move up" << endl;
		cout << "\tDOWN arrow - move down" << endl;
		cout << "\tSPACE - shoot" << endl << endl;
		cout << "\t1. Start Game" << endl;
		cout << "\t2. Back" << endl;
		cout << "\t3. Exit";
		choice = _getch();
		switch (choice) {
		case '1':
			break;
		case '2':
			gameMenu();
			break;
		case '3':
			exit(0);
			break;
		default:
			choice = '0';
			break;
		}
	} while (choice == '0');
}