// Projecto

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <sstream>
#include <stdlib.h>
#include "LAYOUT.h"


using namespace std;


struct Navios;


void escreveTamanho(int lin, int col, string filename);


void escreveFicheiro(char ident, int tamanho, char linha, char coluna, char ori, int cor, string filename);


int escolheCores(string cor);


void verificaCores(vector<Navios> &navios);


void imprimeTabuleiro(int larg, int comp, vector<vector<char>> &tab, vector<Navios> &navios);


bool vazias(int tam, char ori, vector<vector<char>> &tab, int lin, int col);


char escolheOri();


void posicionaNavios(char modo, vector<Navios> &navios, vector<vector<char>> &tab, int larg, int comp);


void leTamanho(string fich, char modo, vector<Navios> &navios);


void leNavios(string fich, char modo);


string escolheFicheiro(); // Devolve o nome do ficheiro a abrir, devolvendo o primeiro ficheiro no caso de erro de input


void createTable();