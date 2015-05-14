#include "BOARD.h"
#include "SHIP.h"
#include "BOMB.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>


void setcolor(unsigned int color, unsigned int background_color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (background_color == 0)
		SetConsoleTextAttribute(hCon, color);
	else
		SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}

Board::Board()
{
	numColumns = 0;
	numLines = 0;
}

Board::Board(const string &filename) // loads board from file 'filename'
{
	string leitura;
	char temp;

	ifstream fich(filename);
	
	fich >> numLines >> temp >> numColumns;

	while (!fich.eof())
	{
		char symbol, orientation;
		PositionChar position;  
		unsigned int size, color; 
		
		fich >> symbol >> size >> position.lin >> position.col >> orientation >> color;

		ships.push_back(Ship(symbol, position, orientation, size, color));
	}
	fich.close();
	
	for (int i = 0; i < numLines; i++)
	{
		vector<int> temp (numColumns, -1);
		board.push_back(temp);
	}
	
}

bool Board::putShip(const Ship &s, unsigned int num) // adds ship to the board, if possible
{
	int linha = s.getPosition().lin;
	int coluna = s.getPosition().col;
	if (s.getOrientation() == 'H') // orientacao horizontal
	{
		for (int j = 0; j < s.getSize(); j++) // preencher o numero de posicoes correspondentes ao tamanho do navio
		{
			board[linha][coluna + j] = num;
		}
	}
	else                           // orientacao vertical
	{
		for (int j = 0; j < s.getSize(); j++) // preencher o numero de posicoes correspondentes ao tamanho do navio
		{
			board[linha + j][coluna] = num;
		}
	}
	return true;
}

void Board::putShips() 
{
	for (int i = 0; i < ships.size(); i++)
		putShip(ships[i], i);
}

void Board::moveShips() // tries to randmonly move all the ships of the fleet
{

}

bool Board::attack(const Bomb &b)
{
	return true;
}

void Board::display() const // displays the colored board during the game
{
	for (int i = 'a'; i < 'a' + numColumns; i++) // Identificação das colunas
	{
		setcolor(7, 0);
		if (i == 'a')
			cout << "  " << (char)i;
		else cout << fixed << setw(2) << (char)i;
	}
	cout << endl;

	for (int i = 0; i < numLines; i++)
	{
		for (int k = -1; k < numColumns; k++)
		{
			if (k == -1)
			{
				setcolor(7, 0);
				cout << (char)('A' + i); // Identificação das linhas
			}
			else if (board[i][k] == -1)
			{
				setcolor(9, 15);
				std::cout << setw(2) << ".";
			}
			else
			{
				setcolor(ships[board[i][k]].getColor(), 15);
				std::cout << setw(2) << ships[board[i][k]].getSymbol();
			}
		}
		std::cout << endl;
	}
	setcolor(7, 0);
}

void Board::show() const// shows the attributes of the board (for debugging)
{
	for (int i = 0; i < numLines; i++)
	{
		for (int k = 0; k < numColumns; k++)
		{
			std::cout << setw(3) << board[i][k];
		}
		std::cout << endl;
	}

}


