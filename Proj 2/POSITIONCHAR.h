#ifndef _POSITIONCHAR
#define _POSITIONCHAR
using namespace std;

struct PositionChar // to store a board position in char format
{ // example: 'B','d'
	char lin, col; // ranges: lin - ['A'..'Z']; col - ['a'..'z']
};
#endif