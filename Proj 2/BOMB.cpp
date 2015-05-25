#include "POSITION.h"
#include "BOMB.h"
#include <cstdlib>
#include <iostream>

Bomb::Bomb(Position<char> targetPosition) //define os privates da classe Bomb
{
	targetLine = toupper(targetPosition.lin);
	targetColumn = tolower(targetPosition.col);

	bomb_deviation();
}

void Bomb::bomb_deviation()
{
	int i;
	i = rand() % 10; // gera um numero entre 0 e 9 para ter uma probabilidade de 40% de alterar a trajectória

	if (i == 0)
		targetLine = targetLine - 1; //dirige a bomba para Norte

	else if (i == 1)
		targetColumn = targetColumn - 1; //dirige a bomba para Oeste

	else if (i == 2)
		targetLine = targetLine + 1; //dirige a bomba par Sul

	else if (i == 3)
		targetColumn = targetColumn + 1; //dirige a bomba para Este
}

Position<char> Bomb::getTargetPosition() const //devolve as coordenadas da bomba após o seu desvio
{
	Position<char> bom_position;

	bom_position.lin = targetLine;
	bom_position.col = targetColumn;

	return bom_position;
}

void Bomb::show() const // imprime as coordenadas finais da bomba
{
	std::cout << targetLine << targetColumn;
}



