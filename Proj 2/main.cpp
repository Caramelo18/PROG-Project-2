#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <sstream>
#include <stdlib.h>
//#include "BOMB.h"
#include "BOARD.h"
#include "SHIP.h"
#include "PLAYER.h"

using namespace std;

int main()
{
	srand((unsigned)time(NULL));
	
	string name1, name2;
	string fich1, fich2;
	int j = 1;
	
	/*
	cout << "Jogador 1 introduza o nome: ";
	getline(cin, name1);
	cout << name1 << " introduza o nome do ficheiro a utilizar: ";
	cin >> fich1;
	Player p1(name1, fich1);
	cin.ignore(1000, '\n');
	
	cout << "Jogador 2 introduza o nome: ";
	getline(cin, name2);
	cout << name2 << " introduza o nome do ficheiro a utilizar: ";
	cin >> fich2;
	Player p2(name2, fich2);
	cin.ignore(1000, '\n');
	*/
	Player p1("Jorge", "p2.txt");
	Player p2("Isidoro", "p1.txt");


	Board b1 = p1.getBoard();
	Board b2 = p2.getBoard();
	
	
	p1.showBoard();
	cout << endl;
	b1.putShips();
	b1.display();
	b1.moveShips();
	b1.display();
	
	
	while (!b1.areDestroyed() || !b2.areDestroyed())
	{
		if (b1.areDestroyed())
			cout << name2 << "is the winner. Congratulations!" << endl;
		else if (b2.areDestroyed())
			cout << name1 << "is the winner. Congratulations!" << endl;
	}

	return 0;
}