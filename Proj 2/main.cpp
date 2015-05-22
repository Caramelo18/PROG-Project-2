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
#include "SCORE.h"

using namespace std;
void readScores(vector<Score> &scores)
{
	fstream file("Highscores.txt");
	string line, temp, name;
	int score;
	if (file.is_open())
	{
		file << "Battleship Highscores" << endl;
		for (int i = 0; i < 10; i++)
			file << i << "  -  Player  -  0" << endl;
		file.close();
		file.open("Highscores.txt");
		getline(file, line);
		for (int i = 0; i < 10; i++)
		{
			getline(file, line);
			stringstream ss(line);
			ss >> temp >> temp >> name >> temp >> score;
			scores[i].name = name;
			scores[i].score = score;
		}
	}
	else
	{
		getline(file, line);
		for (int i = 0; i < 10; i++)
		{
			getline(file, line);
			stringstream ss(line);
			ss >> temp >> temp >> name >> score;
			scores[i].name = name;
			scores[i].score = score;
		}
	}
}

void showScores(vector<Score> &scores)
{
	for (int i = 0; i < 10; i++)
		cout << scores[i].name << " - " << scores[i].score << endl;
}

int main()
{
	srand((unsigned)time(NULL));
	
	string name1, name2;
	string fich1, fich2;
	bool validfile = true;
	int j = 1;

	vector<Score> scores(10);

	cout << "Player 1 write your name: ";
	getline(cin, name1);
	do
	{
		cout << name1 << " introduce the file name you want to use: ";
		cin >> fich1;
		ifstream file(fich1);
		if (file.fail())
			validfile = false;
		else validfile = true;

	} while (!validfile);
	Player p1(name1, fich1);
	cin.ignore(1000, '\n');
	
	cout << "Player 2 write your name: ";
	getline(cin, name2);
	do
	{
		cout << name2 << " introduce the file name you want to use: ";
		cin >> fich2;
		ifstream file(fich2);
		if (file.fail())
			validfile = false;
		else validfile = true;
	} while (!validfile);
	Player p2(name2, fich2);
	cin.ignore(1000, '\n');
	
	//Player p1("Jorge", "p2.txt");
	//Player p2("Isidoro", "p1.txt");
	
	p1.getBoard().putShips();
	p2.getBoard().putShips();
	
	while (!p1.getBoard().areDestroyed() || !p2.getBoard().areDestroyed())
	{
		if (p1.getBoard().areDestroyed())
		{
			cout << name2 << "is the winner. Congratulations!" << endl;
			break;
		}
		else if (p2.getBoard().areDestroyed())
		{
			cout << name1 << "is the winner. Congratulations!" << endl;
			break;
		}

		if (j % 2 == 0)
		{
			// p1 a atacar
			cout << name1 << " it's your turn. \n\n";
			p2.showBoard();
			Bomb atck = p1.getBomb();
			//p2.getBoard().moveShips();
			p2.attackBoard(atck);
			cout << "\n\n";
			// p2.showBoard();
			
		}
		else if (j % 2 != 0)
		{
			// p2 a atacar
			cout << name2 << " it's your turn. \n\n";
			p1.showBoard();
			Bomb atck = p2.getBomb();
			//p1.getBoard().moveShips();
			p1.attackBoard(atck);
			cout << "\n\n";
			//p1.showBoard();
		}
		j++;

	}
		
	return 0;
}