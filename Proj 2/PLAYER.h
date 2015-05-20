#ifndef _PLAYER
#define _PLAYER
#include "BOMB.h"
#include "BOARD.h"
#include <string>

class Player
{
public:
	Player(string playerName, string boardFilename);
	void showBoard() const; // shows the player’s board
	Bomb getBomb() const; // asks bomb target coordinates and creates the bomb
	void attackBoard(const Bomb &b); // "receives" a bomb from the opponent;
	bool areDestroyed(const vector<Ship> &ships) const;
	// updates own board taking into account the damages
	// caused by the bomb; BEFORE THAT… moves the ships
	Board& getBoard();
private:
	string name; // name of the player
	Board board; // board of the player
};
#endif