#include "POSITIONCHAR.h"
#include "BOMB.h"
#include <cstdlib>
#include <iostream>

Bomb::Bomb(PositionChar targetPosition)
{
	targetLine = targetPosition.lin;
	targetColumn = targetPosition.col;

	bomb_deviation();
}

void Bomb::bomb_deviation()
{
	int i;
	i = rand() % 10;

	if (i == 0)
		targetLine = targetLine - 1;

	else if (i == 1)
		targetColumn = targetColumn - 1;

	else if (i == 2)
		targetLine = targetLine + 1;

	else if (i == 3)
		targetColumn = targetColumn + 1;
}

PositionChar Bomb::getTargetPosition() const
{
	PositionChar bom_position;

	bom_position.lin = targetLine;
	bom_position.col = targetColumn;

	return bom_position;
}

void Bomb::show() const
{
	std::cout << targetLine << targetColumn;
}



