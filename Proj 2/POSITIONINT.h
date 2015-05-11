#ifndef _POSITIONINT
#define _POSITIONINT
using namespace std;

struct PositionInt // to store a board position in char format
{ // example: 'B','d'
	char lin, col; // ranges: lin - ['A'..'Z']; col - ['a'..'z']
};
#endif