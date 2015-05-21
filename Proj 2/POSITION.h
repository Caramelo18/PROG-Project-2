#pragma once
template <typename T>
struct Position
{
	T lin, col;
};

/*
using namespace std;

struct Position<char> // to store a board position in char format
{ // example: 'B','d'
	char lin, col; // ranges: lin - ['A'..'Z']; col - ['a'..'z']
};
*/