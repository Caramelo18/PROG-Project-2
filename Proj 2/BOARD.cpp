#include "BOARD.h"
#include "SHIP.h"
#include "BOMB.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

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
}

bool Board::putShip(const Ship &s) // adds ship to the board, if possible
{
	
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

}

void Board::show() const// shows the attributes of the board (for debugging)
{

}