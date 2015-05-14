#include "SHIP.h"
#include <string>
#include <cstdlib>
#include <iostream>


Ship::Ship(char symbol, PositionChar position, char orientation, unsigned int size, unsigned int color)
{
	this->symbol = symbol;
	this->position.col = (int)(position.col - 'a');
	this->position.lin = (int)(position.lin - 'A');
	this->orientation = orientation;
	this->size = size;
	this->color = color;
	this->status = string(size, symbol);
}

bool Ship::move(char direction, bool rotate, unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax) // moves the boat (SEE NOTES)
{
	bool valid = true;

	if (rotate) 
	{
		if (orientation == 'H')
			orientation = 'V';

		else if (orientation == 'V')
			orientation = 'H';
	}


	if (orientation == 'H')  // verifica se a nova posicao do navio esta contida no tabuleiro e movimenta, caso contrário devolve falso
	{

		if (direction == 'N')
		{
			if ((position.lin - 1) < lineMin)
				valid = false;

			else
				position.lin = position.lin - 1;
		}

		else if (direction == 'S')
		{
			if ((position.lin + 1) > lineMax)
				valid = false;

			else
				position.lin = position.lin + 1;
		}

		else if (direction == 'W')
		{
			if ((position.col - 1) < columnMin)
				valid = false;

			else
				position.col = position.col - 1;
		}

		else if (direction == 'E')
		{
			if ((position.col + size + 1) > columnMax)
				valid = false;

			else
				position.col = position.col + 1;
		}
	}

	else
	{
		if (direction == 'N')
		{
			if ((position.lin - 1) < lineMin)
				valid = false;

			else
				position.lin = position.lin - 1;
		}

		else if (direction == 'S')
		{
			if ((position.lin + size + 1) > lineMax)
				valid = false;

			else
				position.lin = position.lin + 1;
		}

		else if (direction == 'W')
		{
			if ((position.col - 1) < columnMin)
				valid = false;

			else
				position.col = position.col - 1;
		}

		else if (direction == 'E')
		{
			if ((position.col + 1) > columnMax)
				valid = false;

			else
				position.col = position.col + 1;
		}
	}
	return valid;
}

bool Ship::moveRand(unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax) // moves the ship randomly
{
	int i = rand() % 2;  // tem 50% de rodar
	bool rotate;

	if (i == 0)
		rotate = true;

	else if (i == 1)
		rotate = false;

	int j = rand() % 5;
	char direction;

	if (j < 4)
	{
		if (j == 0)
			direction = 'N';

		else if (j == 1)
			direction = 'S';

		else if (j == 2)
			direction = 'W';

		else if (j == 3)
			direction = 'E';

		Ship::move(direction, rotate, lineMin, columnMin, lineMax, columnMax);
		return true;

	}

	else if (j == 4)
		return false;
}

bool Ship::attack(size_t partNumber) //partNumber = {0,1,…, size-1}
{
	if (partNumber < size && isupper(status[partNumber])) // verifica se a posicao nao foi ja atacada
	{
		status[partNumber] = tolower(symbol);
		return true;
	}

	return false;
}

bool Ship::isDestroyed() const // checks whether the ship is destroyed
{
	int counter;
	for (unsigned int i = 0; i < size; i++)
	{
		if (status[i] == islower(symbol))
			counter++;
	}

	double size_to_destroy = size / 2;

	if (counter > size_to_destroy)
		return true;

	return false;
}

void Ship::show() const // shows the attributes of the ship (for debugging)
{
	std::cout << "Ship attributes:" << endl << "Symbol: " << symbol << endl << "Line position: " << position.lin << endl << "Column position: " << position.col << endl << "Orientation: " << orientation << endl << "Size: " << size << endl << "Color: " << color << endl << "Status: " << status << endl;
}

char Ship::getSymbol() const
{
	return symbol;
}

int Ship::getSize() const
{
	return size;
}

PositionInt Ship::getPosition() const
{
	return position;
}

char Ship::getOrientation() const
{
	return orientation;
}

int Ship::getColor() const
{
	return color;
}
