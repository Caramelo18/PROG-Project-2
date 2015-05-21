#ifndef _BOMB
#define _BOMB
#include "POSITION.h"
#include <vector>

class Bomb
{
public:
	Bomb(Position<char> targetPosition);
	Position<char> getTargetPosition() const;
	void bomb_deviation();
	// OTHER METHODS, if necessary
	// ...
	void show() const; // shows the attributes of the bomb (for debugging)

private:
	char targetLine, targetColumn;
};
#endif