#ifndef _BOMB
#define _BOMB
#include "POSITIONCHAR.h"

class Bomb
{
public:
	Bomb(PositionChar targetPosition);
	PositionChar getTargetPosition() const;
	void bomb_deviation();
	// OTHER METHODS, if necessary
	// ...
	void show() const; // shows the attributes of the bomb (for debugging)
private:
	char targetLine, targetColumn;
};
#endif