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
	Position<char> char_coordenates;
	bool valid = true;

	do
	{
		std::cout << "Introduce your bomb coordenates (lin, col): ";
		std::cin >> coordenates;
		if (coordenates.size() != 2 || cin.eof())
		{
			std::cout << "Invalid input! \n";
			cin.clear();
			valid = false;
		}
		else if (toupper(coordenates[0]) > (char)((int)'A' + board.getLines() - 1) || tolower(coordenates[1]) >(char)((int)'a' + board.getColumns() - 1) || toupper(coordenates[0]) < 'A' || tolower(coordenates[1]) < 'a') // verifica se as posicoes inseridas estao contidas no tabuleiro
		{
			valid = false;
			std::cout << "Inserted position out of range \n";
		}
		else
		{
			valid = true;
			char_coordenates.lin = coordenates[0];
			char_coordenates.col = coordenates[1];
		}

	} while (!valid);
	

	return Bomb::Bomb(char_coordenates);
}

void Player::attackBoard(const Bomb &b) // "receives" a bomb from the opponent;
{
	board.moveShips();
	board.attack(b);
	
}

// updates own board taking into account the damages
// caused by the bomb; BEFORE THAT… moves the ships

Board& Player::getBoard() 
{
	return board;
}