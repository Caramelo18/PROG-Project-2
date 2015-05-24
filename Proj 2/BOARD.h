#ifndef _BOARD
#define _BOARD
#include <vector>
#include "SHIP.h"
#include "BOMB.h"
#include <Windows.h>

class Board
{
	
public:
	Board();
	Board(const string &filename); // loads board from file 'filename'
	bool putShip(const Ship &s, unsigned int num); // adds ship to the board, if possible
	void putShips();
	void moveShips(); // tries to randmonly move all the ships of the fleet
	bool attack(const Bomb &b);
	void display() const; // displays the colored board during the game
	void show() const; // shows the attributes of the board (for debugging)
	// OTHER METHODS, if necessary
	// ...
	bool checkPosition(int line, int column, unsigned int size, char orientation, char direction) const;
	void deleteShip(const Ship &s);
	friend ostream& operator<<(ostream& output, const Board &board);
	friend bool operator==(const Board &board1, const Board &board2);
	vector<Ship> getShips() const;
	bool areDestroyed() const;
	int getLines() const;
	int getColumns() const;
	
private:
	int numLines, numColumns; // redundant info …
	vector<Ship> ships; // ships that are placed on the board
	vector<vector<int>> board; // each element indicates
							   // the index of a ship in the 'ships' vector
							   // (in the range 0..ships.size()-1) ;
							   // -1 is used to represent the sea
};

#endif