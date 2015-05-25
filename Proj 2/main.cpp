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
#include "TABLECREATOR.h"
#include "LAYOUT.h"

using namespace std;

int calculateScore(time_t playerTime, Player opponent) // calcula a pontuacao do jogador vencedor
{
	int score;
	int boardArea = opponent.getBoard().getColumns() * opponent.getBoard().getLines();
	int shipsArea = 0;

	for (unsigned int i = 0; i < opponent.getBoard().getShips().size(); i++)
	{
		shipsArea = shipsArea + opponent.getBoard().getShips()[i].getSize(); // segue a formula T*S/A
	}

	score = (int)round(playerTime * ((double)shipsArea / boardArea));

	return score;
}

void readScores(vector<Score> &scores) // le o ficheiro das pontuacoes mais altas e armazena as mesmas num vetor
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
			scores[i].score = 999999; // pontuacao alta porque as pontuacoes sao melhores quanto melhor for o resultado
		}
	}
	else
	{
		for (int i = 0; i < 10; i++) //armazena a informacao do ficheiro no vetor
		{
			getline(file, line);
			stringstream ss(line);
			ss >> temp >> temp >> name >> temp >> score;
			scores[i].name = name;
			scores[i].score = score;
		}
	}
}

void showScores(vector<Score> &scores) // le do vetor as pontuacoes mais elevadas e escreve-as na consola
{
	cout << "\n    Battleship Highscores \n\n";
	for (int i = 0; i < 10; i++)
		cout << fixed << setw(2) << i + 1 << " - " << setw(13) << scores[i].name << " - " << setw(6) << scores[i].score << endl;
}

bool updateScore(vector<Score> &scores, unsigned int playerScore, string playerName) // recebe a pontuacao do jogador vencedor e verifica se esta entra nas pontuacoes mais elevadas e se tal for verdade faz um return e escreve-a no ficheiro das pontuacoes mais elevadas
{
	unsigned int i = 0;

	for (i; i < scores.size(); i++)
	{
		if (playerScore < (unsigned) scores[i].score)
			break;
	}

	if (i == scores.size())
		return false;

	for (unsigned int j = scores.size() - 1; j > i; j--) // vai passando as posicoes das pontuacoes mais altas para a posicao seguinte visto que foram ultrapassadas
	{
		scores[j] = scores[j - 1];
	}
	
	scores[i].name = playerName;
	scores[i].score = playerScore;

	
	fstream file("Highscores.txt"); // escreve no ficheiro as novas melhores pontuacoes
	string line, temp, name;

	file << "Battleship Highscores" << endl;
	for (unsigned int j = 0; j < 10; j++)
	{
		file << j + 1 << "  -  " << scores[j].name << " - " << scores[j].score << endl;	
	}
	file.close();

	return true;
}

void game(vector<Score> &scores) // funcao orientadora do jogo
{
	
	string name1, name2;
	string fich1, fich2;
	bool validfile = true;
	int j = rand() % 2; //tira a sorte qual dos jogadores vai iniciar o jogo
	time_t timeP1 = 0; //tempo total dos jogadores na realizacao do jogo
	time_t timeP2 = 0;
	int winnerScore;
	char cont = 'Y';

	do
	{
		cout << "Player 1 write your name: ";
		getline(cin, name1);
		cin.clear();
		
	} while (name1 == "");
	do // enquanto o ficheiro nao for valido repete a introducao do ficheiro
	{
		cout << name1 << " introduce the file name you want to use: ";
		cin >> fich1;
		ifstream file(fich1);
		if (file.fail() )
		{
			validfile = false;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else validfile = true;

	} while (!validfile);
	Player p1(name1, fich1);
	cin.ignore(1000, '\n');
	
	do
	{
		cout << "Player 2 write your name: ";
		getline(cin, name2);
		cin.clear();

	} while (name2 == "");
	do // enquanto o ficheiro nao for valido repete a introducao do ficheiro
	{
		cout << name2 << " introduce the file name you want to use: ";
		cin >> fich2;
		ifstream file(fich2);
		if (file.fail())
		{
			validfile = false;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else validfile = true;
	} while (!validfile);
	Player p2(name2, fich2);
	cin.ignore(1000, '\n');
	
	
	if (p1.getBoard() != p2.getBoard()) // verifica se o tabuleiro dos dois jogadores tem a mesma dimensao e avisa os mesmos
	{
			do
			{
			cout << "Different board sizes. Do you want to continue? (Y/N)";
			cin >> cont;
			cont = toupper(cont);
			} while (cont != 'Y' && cont != 'N');
	}
	
	if (cont == 'N') // se pretenderem o mesmo tamanho do tabuleiro repete a pergunta de introducao do ficheiro
		return;

	p1.getBoard().putShips();
	p2.getBoard().putShips();
	while (!p1.getBoard().areDestroyed() || !p2.getBoard().areDestroyed()) // verifica se o tabuleiro de algum dos jogadores ja esta destruido
	{
		if (p1.getBoard().areDestroyed()) // avisa qual e o vencedor
		{
			cout << name2 << " is the winner. Congratulations!" << endl;
			winnerScore = calculateScore(timeP2, p1);
			if (updateScore(scores, winnerScore, name2))
				cout << "Your score is on the top 10! Congratulations! \n";
			showScores(scores);
			break;
		}
		else if (p2.getBoard().areDestroyed())
		{
			cout << name1 << " is the winner. Congratulations!" << endl;
			winnerScore = calculateScore(timeP1, p2);
			if(updateScore(scores, winnerScore, name1))
				cout << "Your score is on the top 10! Congratulations! \n";
			showScores(scores);
			break;
		}

		if (j % 2 == 0) // define qual dos jogadores vai executar a jogada, se for par e o player 1 se for impar e o player 2
		{
			time_t startTime = time(NULL);
			// p1 a atacar
			cout << name1 << " it's your turn. \n\n";
			cout << p2.getBoard(); //mostra o tabuleiro do player 2 que vai ser atacado pelo player 1
			Bomb atck = p1.getBomb();
			p2.attackBoard(atck);
			cout << "\n\n";
			time_t endTime = time(NULL);
			timeP1 = timeP1 + (endTime - startTime); // adiciona o tempo de cada jogada ao tempo total

		}
		else if (j % 2 != 0)
		{
			time_t startTime = time(NULL);
			// p2 a atacar
			cout << name2 << " it's your turn. \n\n";
			cout << p1.getBoard(); //mostra o tabuleiro do player 1 que vai ser atacado pelo player 2
			Bomb atck = p2.getBomb();
			p1.attackBoard(atck);
			cout << "\n\n";
			time_t endTime = time(NULL);
			timeP2 = timeP2 + (endTime - startTime); // adiciona o tempo de cada jogada ao tempo total
		}
		j++;

	}
}

int main()
{
	srand((unsigned)time(NULL));
	string option;
	bool validoption = true;
	char cont = 'Y';
	do // mostra o menu principal
	{
		vector<Score> scores(10);
		readScores(scores);


		gotoxy(35, 0);
		std::cout << "BATTLESHIP \n\n";
		gotoxy(20, 22);
		std::cout << "Developed by Bruno Barros and Fabio Caramelo - FEUP - MIEIC";
		gotoxy(0, 2);
		std::cout << "1 - Play Game" << endl;
		std::cout << "2 - View Highscores" << endl;
		std::cout << "3 - Create a new table" << endl;
		std::cout << "4 - Exit \n\n";
		do // repete a pergunta enquanto nao for introduzido um algarismo que execute uma acao
		{
			std::cout << "Please select an option: ";
			std::getline(cin, option);
			if (std::cin.eof())
				cin.clear();
			else if (option.length() != 1 || option[0] > '4' || option[0] < '1')
				option = "";
		} while (option.length() != 1);

		if (option[0] == '1')
		{
			clrscr();
			game(scores);
		}
		else if (option[0] == '2')
		{
			clrscr();
			showScores(scores);
		}
		else if (option[0] == '3')
		{
			clrscr();
			createTable();
		}
		else if (option[0] == '4')
			exit(1);

		std::cout << "\n\nDo you want to continue? (Y/N)";
		std::cin >> cont;
		cin.ignore(1000, '\n');
		clrscr();
	} while (cont == 'Y' || cont == 'y');
	

	return 0;
	
}