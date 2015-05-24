#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <sstream>
#include <stdlib.h>
#include "BOMB.h"
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
	getline(file, line);
	if (line == "") // se o ficheiro estiver vazio vai preencher o vector de scores com scores irrealistas
	{
		for (unsigned int i = 0; i < scores.size(); i++)
		{
			scores[i].name = "Player";
			scores[i].score = 999999;
		}
		/*file << "Battleship Highscores" << endl;
		for (int i = 0; i < 10; i++) 
			file << i + 1 << " - Player - 999999" << endl;
		getline(file, line);
		for (int i = 0; i < 10; i++)
		{
			getline(file, line);
			stringstream ss(line);
			ss >> temp >> temp >> name >> temp >> score;
			scores[i].name = name;
			scores[i].score = score;
		}*/
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			getline(file, line);
			stringstream ss(line);
			ss >> temp >> temp >> name >> temp >> score;
			scores[i].name = name;
			scores[i].score = score;
		}
	}
}

void showScores(vector<Score> &scores)
{
	for (int i = 0; i < 10; i++)
		cout << i + 1 << " - " << scores[i].name << " - " << scores[i].score << endl;
}

void updateScore(vector<Score> &scores, unsigned int playerScore, string playerName) //nao funciona a 100%
{
	unsigned int i = 0;

	for (i; i < scores.size(); i++)
	{
		if (playerScore < scores[i].score)
			break;
	}

	for (unsigned int j = i; j < scores.size() - 2; j++)
	{
		if (i == 0)
		{
			cout << "Yet to do \n";
			
			break;
		}
		else if (j == i)
		{
			scores[j + 2] = scores[j + 1];
			scores[j + 1] = scores[j];
		}
		
		else
			scores[j + 2] = scores[j + 1];
	}
	scores[i].name = playerName;
	scores[i].score = playerScore;

	/*for (int j = 0; j < scores.size() - 1 - i; j++)
	{
		scores[scores.size() - j - 1].score = scores[scores.size() - j - 2].score;
		scores[scores.size() - j - 1].name = scores[scores.size() - j - 2].name;
	}*/

	//scores[i].name = playerName;
	//scores[i].score = playerScore;
	fstream file("Highscores.txt");
	string line, temp, name;

	file << "Battleship Highscores" << endl;
	for (unsigned int j = 0; j < 10; j++)
	{
		file << j + 1 << "  -  " << scores[j].name << " - " << scores[j].score << endl;	
	}
	file.close();
}

void game()
{
	srand((unsigned)time(NULL));
	
	string name1, name2;
	string fich1, fich2;
	bool validfile = true;
	int j = 1;

	vector<Score> scores(10);
	/*
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
		*/

	updateScore(scores, 11, "Miquelina");
	showScores(scores);

}

void gotoxy1(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main()
{
	int option;
	bool validoption = true;

	vector<Score> scores(10);
	readScores(scores);


	gotoxy1(35, 0);
	cout << "BATTLESHIP \n\n";
	gotoxy1(0, 2);
	cout << "1 - Play Game" << endl;
	cout << "2 - View Highscores" << endl;
	cout << "3 - Create a new table \n\n";
	do
	{
		cout << "Please select an option: ";
		cin >> option;
		if (cin.fail() || cin.eof() || option > 3 || option < 1)
		{
			validoption = false;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else validoption = true;
	} while (!validoption);
	if (option == 1)
		game();
	else if (option == 2)
	{
		updateScore(scores, 35, "Jorge");
		showScores(scores);
	}
	
}