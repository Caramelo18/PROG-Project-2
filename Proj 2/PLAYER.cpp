#include "BOMB.h"
#include "PLAYER.h"
#include "BOARD.h"
#include <iostream>

Player::Player(string playerName, string boardFilename)
{
	name = playerName;
	board = Board::Board(boardFilename);
}

void Player::showBoard() const // shows the player’s board
{
	board.display();
}

Bomb Player::getBomb() const // asks bomb target coordinates and creates the bomb
{
	string coordenates;
	PositionChar char_coordenates;

	std::cout << "Introduce your bomb coordenates (lin, col): ";
	std::cin >> coordenates;

	if (coordenates.size() != 2)
		std::cout << "Invalid input! \n";
	else
	{
		char_coordenates.lin = coordenates[0];
		char_coordenates.col = coordenates[1];
	}

	return Bomb::Bomb(char_coordenates);
}

void Player::attackBoard(const Bomb &b) // "receives" a bomb from the opponent;
{
	board.attack(b);
}

// updates own board taking into account the damages
// caused by the bomb; BEFORE THAT… moves the ships