#include "BOARD.h"
#include "SHIP.h"
#include "BOMB.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

//nothing have changed

void setcolor(unsigned int color, unsigned int background_color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (background_color == 0)
		SetConsoleTextAttribute(hCon, color);
	else
		SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}

void clrscr(void)
{
	COORD coordScreen = { 0, 0 }; // upper left corner
	DWORD cCharsWritten;
	DWORD dwConSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hCon, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, coordScreen);
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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
		Position<char> position;  
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
	int line = s.getPosition().lin;
	int column = s.getPosition().col;
	bool free = true;
	if (s.getOrientation() == 'H') // orientacao horizontal
	{
		if (column + s.getSize() > numColumns || line < 0 || column < 0 || line > numLines)
			return false;
		for (int j = 0; j < s.getSize(); j++) // preencher o numero de posicoes correspondentes ao tamanho do navio
		{
			if (board[line][column + j] != -1 && board[line][column + j] != num)
			{
				free = false;
				break;
			}
		}
	}
	else                           // orientacao vertical
	{
		if (line + s.getSize() > numLines || line < 0 || column < 0 || column > numColumns)
			return false;
		for (int j = 0; j < s.getSize(); j++) // preencher o numero de posicoes correspondentes ao tamanho do navio
		{
			if (board[line + j][column] != -1 && board[line][column + j] != num)
			{
				free = false;	
				break;
			}
		}
	} 
	if (free)
	{
		if (s.getOrientation() == 'H') // orientacao horizontal
		{
			for (int j = 0; j < s.getSize(); j++) // preencher o numero de posicoes correspondentes ao tamanho do navio
			{
				board[line][column + j] = num;
			}
		}
		else                           // orientacao vertical
		{
			for (int j = 0; j < s.getSize(); j++) // preencher o numero de posicoes correspondentes ao tamanho do navio
			{
				board[line + j][column] = num;
			}
		}
	}
	return free;
}

void Board::putShips() 
{
	for (unsigned int i = 0; i < ships.size(); i++)
		putShip(ships[i], i);
}

void Board::moveShips() // tries to randmonly move all the ships of the fleet
{
	int count = 0;
	for (unsigned int i = 0; i < ships.size(); i++)
	{
		Ship temp = ships[i];
		bool move = ships[i].moveRand(0, 0, numLines - 1, numColumns- 1);
		if (move || ships[i].getOrientation() != temp.getOrientation())
		{
			deleteShip(temp);
			while (1)
			{
				if (putShip(ships[i], i))
					break;
				else if (count >= 20)
				{
					ships[i] = temp;
					putShip(temp, i);
				}
				else
				{
					ships[i] = temp;
					ships[i].moveRand(0, 0, numLines - 1, numColumns - 1);
				}
				count++;
			}
		}
		else
		{
			ships[i] = temp;
		}

	}
}

void Board::deleteShip(const Ship &s)
{
	int line = s.getPosition().lin;
	int column = s.getPosition().col;
	if (s.getOrientation() == 'H') // orientacao horizontal
		{
			for (int j = 0; j < s.getSize(); j++) // preencher o numero de posicoes correspondentes ao tamanho do navio
			{
				board[line][column + j] = -1;
			}
		}
	else                           // orientacao vertical
	{
		for (int j = 0; j < s.getSize(); j++) // preencher o numero de posicoes correspondentes ao tamanho do navio
		{
			board[line + j][column] = -1;
		}
	}
}

bool Board::attack(const Bomb &b)
{
	bool hit = true;
	Position<unsigned int> coordenates;
	int partNumber;
	coordenates.lin = (int)(b.getTargetPosition().lin - 'A');
	coordenates.col = (int)(b.getTargetPosition().col - 'a');

	clrscr();
	gotoxy(0, 0);

	if (coordenates.lin < 0 || coordenates.col < 0 || coordenates.lin > numLines - 1 || coordenates.col > numColumns - 1)
		hit = false;
	else if (board[coordenates.lin][coordenates.col] == -1 )
		hit = false;

	if (hit)
	{
		if (ships[board[coordenates.lin][coordenates.col]].getOrientation() == 'H')
			partNumber = coordenates.col - ships[board[coordenates.lin][coordenates.col]].getPosition().col;
		else if (ships[board[coordenates.lin][coordenates.col]].getOrientation() == 'V')
			partNumber = coordenates.lin - ships[board[coordenates.lin][coordenates.col]].getPosition().lin;

		char h = ships[board[coordenates.lin][coordenates.col]].getStatus()[partNumber];
		if (islower(h))
		{
			cout << "Position has already been hit! \n";
		}

		ships[board[coordenates.lin][coordenates.col]].attack(partNumber);
		setcolor(10, 0);
		cout << "\nHit! \n";
		if (ships[board[coordenates.lin][coordenates.col]].isDestroyed())
		{
			setcolor(7, 0);
			cout << "Ship "; 
			setcolor(ships[board[coordenates.lin][coordenates.col]].getColor(), 0);
			cout << ships[board[coordenates.lin][coordenates.col]].getSymbol();
			setcolor(7, 0);
			cout << " has been destroyed!";
			deleteShip(ships[board[coordenates.lin][coordenates.col]]);
			
		}
	}
	
	else
	{
		setcolor(12, 0);
		cout << "\nMiss! \n";
		setcolor(7, 0);
	}

	return hit;
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
				if (ships[board[i][k]].getOrientation() == 'H')
					std::cout << setw(2) << ships[board[i][k]].getStatus()[k - ships[board[i][k]].getPosition().col]; // <- aterar [0]
				else if (ships[board[i][k]].getOrientation() == 'V')
					std::cout << setw(2) << ships[board[i][k]].getStatus()[i - ships[board[i][k]].getPosition().lin]; // <- aterar [0]
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

vector<Ship> Board::getShips() const
{
	return ships;
}

bool Board::areDestroyed() const
{
	bool destroyed = true;
	for (unsigned int i = 0; i < ships.size(); i++)
	{
		if (ships[i].isDestroyed() == false)
			destroyed = false;
	}
	return destroyed;
}

int Board::getColumns() const
{
	return numColumns;
}

int Board::getLines() const
{
	return numLines;
}