#ifndef _Position<int>
#define _Position<int>
using namespace std;

struct Position<int> // to store a board position in unsig. integer format
{					// example: 7,0
	unsigned int lin, col; // ranges: lin - [0..26]; col - [0..26]
};
#endif