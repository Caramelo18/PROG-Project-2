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
#include "TABLECREATOR.h"



struct Navios
{
	int quant;
	string nome;
	int casas;
	char ident;
	string cor;
};


void escreveTamanho(int lin, int col, string filename)
{
	ofstream fich;
	fich.open(filename);

	fich << lin << " x " << col; // Escreve no ficheiro as dimensoes
	fich.close();
}


void escreveFicheiro(char ident, int tamanho, char linha, char coluna, char ori, int cor, string filename)
{
	ofstream fich;
	fich.open(filename, ios::app); // Escreve depois do que ja esta escrito
	fich << endl;
	fich << ident << " " << tamanho << " " << linha << coluna << " " << ori << " " << cor;
	fich.close();

}


int escolheCores(string cor)
{
	int num;
	// vai devolver o codigo da cor consoante o nome
	if (cor == "Preto")
		num = 0;
	else if (cor == "Azul")
		num = 1;
	else if (cor == "Verde")
		num = 2;
	else if (cor == "Ciano")
		num = 3;
	else if (cor == "Vermelho")
		num = 4;
	else if (cor == "Magenta")
		num = 5;
	else if (cor == "Castanho")
		num = 6;
	else if (cor == "Cinzento_claro")
		num = 7;
	else if (cor == "Cinzento_escuro")
		num = 8;
	else if (cor == "Azul_claro")
		num = 9;
	else if (cor == "Verde_claro")
		num = 10;
	else if (cor == "Ciano_claro")
		num = 11;
	else if (cor == "Vermelho_claro")
		num = 12;
	else if (cor == "Magenta_claro")
		num = 13;
	else if (cor == "Amarelo")
		num = 14;
	else if (cor == "Branco")
		num = 15;
	else num = 16; // vai retornar 16 quando a cor nao for nenhuma das indicadas para saber que a cor e invalida
	return num;
}


void verificaCores(vector<Navios> &navios)
{
	string cor;
	for (unsigned short int i = 0; i < navios.size(); i++)
	{
		if (escolheCores(navios[i].cor) == 16)
		{
			cout << "Cor do navio " << navios[i].nome << " invalida. Por favor insira outra cor: ";
			cin >> cor;
			navios[i].cor = cor;
		}
	}
}


void imprimeTabuleiro(int larg, int comp, vector<vector<char>> &tab, vector<Navios> &navios)
{
	int a = (int)'a';
	int A = (int)'A';
	int inc = 0;

	for (int i = a; i < a + larg; i++) // Identificação das colunas
	{
		setcolor(15, 0);
		if (i == a)
			cout << "  " << (char)i;
		else cout << fixed << setw(2) << (char)i;
	}
	cout << endl;
	for (int i = 0; i < comp; i++) // Desenho do tabuleiro
	{
		for (int j = -1; j < larg; j++)
		{
			if (j == -1)
			{
				setcolor(15, 0);
				cout << (char)(A + inc); // Identificação das linhas
			}
			else if (tab[i][j] == '.') // se a posicao do tabuleiro estiver vazia, imprime com a cor normal
			{
				setcolor(9, 15);
				cout << " " << tab[i][j];
			}
			else
			{
				for (unsigned int k = 0; k < navios.size(); k++)
					if (navios[k].ident == tab[i][j]) // vai procurar a cor correspondente a identificacao do navio
					{
					setcolor(escolheCores(navios[k].cor), 15);
					break;
					}
				cout << " " << tab[i][j];
			}

		}
		cout << endl;
		inc = inc + 1;
	}

	cout << "\n";
	setcolor(15, 0);
}


bool vazias(int tam, char ori, vector<vector<char>> &tab, int lin, int col)
{
	bool vazio = true;

	if (ori == 'H' || ori == 'h') // se a orientacao desejada for horizontal vai procurar na mesma linha
	{
		for (int i = 0; i < tam; i++)
		{
			if (tab[lin - (int)'A'][col - (int)'a' + i] != '.') // quando a posicao for diferente indica que nao esta vazio
				vazio = false;
		}
	}
	else if (ori == 'V' || ori == 'v') // se a orientacao desejada for vertical vai procurar na coluna
	{
		for (int i = 0; i < tam; i++)
		{
			if (tab[lin - (int)'A' + i][col - (int)'a'] != '.') // quando a posicao for diferente indica que nao esta vazio
				vazio = false;
		}
	}
	return vazio;
}


char escolheOri()
{
	int num;
	char ori;
	num = rand() % 2; // vai gerar um numero aleatorio (0 ou 1) e a partir dai ira escolher a orientacao
	if (num == 0)
		ori = 'V';
	else ori = 'H';
	return ori;
}


void posicionaNavios(char modo, vector<Navios> &navios, vector<vector<char>> &tab, int larg, int comp, string filename)
{
	int quantidade = navios[0].quant + navios[1].quant + navios[2].quant + navios[3].quant + navios[4].quant; //quantidade de navios a colocar no tabuleiro
	int k = 0; // indice para navegar entre o tipo de navios
	int n = 0; // indice para saber quantos navios de um tipo foram utilizados
	string input;
	char lin, col, ori;

	escreveTamanho(comp, larg, filename);

	if (modo == 'M' || modo == 'm') // Se o modo seleccionado for manual
	{
		for (unsigned int i = 0; i < navios.size(); i++) // o numero de colocacao de peças tera que ser o numero de pecas existentes
		{
			while (n < navios[i].quant)
			{
				setcolor(escolheCores(navios[k].cor), 0); // a cor da mensagem sobre a informacao do navio a colocar sera a cor do navio
				cout << navios[i].ident << " - " << navios[k].nome << " - Tamanho: " << navios[k].casas << " - Falta(m): " << navios[k].quant - n << endl;

				setcolor(15, 0);
				cout << "\n" << "Linha (A.." << (char)((int)'A' + comp - 1) << "), Coluna (a.." << (char)((int)'a' + larg - 1) << "), Orientacao(H V) ? ";
				cin >> input;
				cout << "\n";
				if (cin.eof())
					exit(1);
				lin = toupper(input[0]);
				col = tolower(input[1]);
				ori = toupper(input[2]);

				if ((ori == 'V') && (int)lin - (int)'A' + navios[k].casas > comp || (ori == 'H') && (int)col - (int)'a' + navios[k].casas > larg || (int)col - (int)'a' >= larg || (int)lin - (int)'A' >= comp) // verifica se nao esta fora do tabuleiro
				{
					clrscr();
					gotoxy(0, 0);
					cout << "Fora das dimensoes do tabuleiro, insira de novo \n\n";
				}
				else if (vazias(navios[k].casas, ori, tab, lin, col))
				{
					if (ori == 'H') // se a orientacao desejada for horizontal coloca a peca na horizontal
					{
						for (int i = 0; i < navios[k].casas; i++)
						{
							tab[lin - (int)'A'][col - (int)'a' + i] = navios[k].ident; // escreve no tabuleiro 
						}
						n = n + 1;
						clrscr();
						gotoxy(0, 0);
						escreveFicheiro(navios[k].ident, navios[k].casas, lin, col, ori, escolheCores(navios[k].cor), filename); // escreve no ficheiro a posicao do navio colocada depois de escrever no tabuleiro
					}
					else if (ori == 'V') // se a orientacao desejada for horizontal coloca a peca na horizontal
					{
						for (int i = 0; i < navios[k].casas; i++)
						{
							tab[lin - (int)'A' + i][col - (int)'a'] = navios[k].ident; // escreve no tabuleiro									
						}
						n = n + 1;
						clrscr();
						gotoxy(0, 0);
						escreveFicheiro(navios[k].ident, navios[k].casas, lin, col, ori, escolheCores(navios[k].cor), filename); // escreve no ficheiro a posicao do navio colocada depois de escrever no tabuleiro
					}
				}
				else
				{
					clrscr();
					gotoxy(0, 0);
					cout << "Posicao " << lin << col << ori << " invalida, insira nova posicao \n \n";
				}
				imprimeTabuleiro(larg, comp, tab, navios); // imprime o tabuleiro 
			}
			k = k + 1; // passa para o proximo tipo de navio
			n = 0;
		}
	}
	else if (modo == 'A' || modo == 'a') // Se o modo seleccionado for automatico
	{
		for (unsigned int i = 0; i < navios.size(); i++) // o numero de colocacao de peças tera que ser o numero de pecas existentes
		{
			setcolor(15, 0);
			while (n < navios[k].quant)
			{
				lin = rand() % (comp - navios[k].casas + 1) + (int)'A';
				col = rand() % (larg - navios[k].casas + 1) + (int)'a';
				ori = escolheOri();
				if (vazias(navios[k].casas, ori, tab, lin, col))
				{
					if (ori == 'H') // se a orientacao desejada for horizontal coloca a peca na horizontal
					{
						for (int i = 0; i < navios[k].casas; i++) // preenche o numero de casas do tamanho do navio a colocar	
						{
							tab[lin - (int)'A'][col - (int)'a' + i] = navios[k].ident;
						}
						n = n + 1;
						escreveFicheiro(navios[k].ident, navios[k].casas, lin, col, ori, escolheCores(navios[k].cor), filename); // escreve no ficheiro a posicao do navio colocada depois de escrever no tabuleiro
					}
					else if (ori == 'V') // se a orientacao desejada for horizontal coloca a peca na horizontal
					{
						for (int i = 0; i < navios[k].casas; i++)
						{
							tab[lin - (int)'A' + i][col - (int)'a'] = navios[k].ident;
						}
						n = n + 1;
						escreveFicheiro(navios[k].ident, navios[k].casas, lin, col, ori, escolheCores(navios[k].cor), filename); // escreve no ficheiro a posicao do navio colocada depois de escrever no tabuleiro
					}
				}
			}
			k = k + 1;
			n = 0;
		}
		imprimeTabuleiro(larg, comp, tab, navios); // imprime o tabuleiro alterado
	}
	setcolor(7, 0);
}


void leTamanho(string fich, char modo, vector<Navios> &navios, string filename)
{
	int comp, larg;
	string linha, tmp;
	fstream ficheiro(fich);
	getline(ficheiro, linha);
	char ponto = '.';
	bool max = true;

	stringstream ss(linha);

	ss >> tmp >> comp >> tmp >> larg; // retira da primeira linha do ficheiro o tamanho do tabuleiro
	ficheiro.close();

	int areatab = comp * larg;
	int areanav = 0;
	for (unsigned int i = 0; i < navios.size(); i++)  // vai calcular as casas ocupadas pelos navios
		areanav += navios[i].casas * navios[i].quant;

	for (unsigned int i = 0; i < navios.size(); i++)
	{
		if (navios[i].casas > comp || navios[i].casas > larg) // vai verificar se todas as pecas cabem no tabuleiro
		{
			max = false;
			break;
		}
	}

	if (areanav <= areatab) // apenas avanca se o numero de casas ocupadas pelo navio for menor ou igual que o numero de casas do tabuleiro
	{
		if (comp < 27 && larg < 27 && comp > 0 && larg > 0 && max)
		{
			vector<vector<char>> tabuleiro(comp, vector<char>(larg, ponto));
			if (modo == 'M' || modo == 'm')
			{
				verificaCores(navios);
				imprimeTabuleiro(larg, comp, tabuleiro, navios); // imprime o tabuleiro com as medidas
				posicionaNavios(modo, navios, tabuleiro, larg, comp, filename);
			}
			else if (modo == 'A' || modo == 'a')
			{
				verificaCores(navios);
				posicionaNavios(modo, navios, tabuleiro, larg, comp, filename); // apenas vai imprimir o tabuleiro ja preenchido automaticamente
			}
		}
		else cout << "Tamanho invalido\n";
	}
	else cout << "Tabuleiro demasiado pequeno para os navios existentes \n";
}


void leNavios(string fich, char modo, string filename)
{
	string linha;
	fstream ficheiro(fich);
	string navio;
	Navios nav;
	char lix;
	vector <Navios> navios;

	getline(ficheiro, linha); // le a primeira linha mas ignora pois e a dimensao
	while (!ficheiro.eof()) // enquanto o ficheiro nao acaba vai guardar a informacao na struct e depois no vector
	{
		getline(ficheiro, linha);
		stringstream ss(linha);
		ss >> nav.quant >> lix >> nav.nome >> lix >> nav.casas >> lix >> nav.ident >> lix >> nav.cor;
		navios.push_back(nav);
	}
	leTamanho(fich, modo, navios, filename); // Constroi o tabuleiro com as medidas do ficheiro
}


string escolheFicheiro() // Devolve o nome do ficheiro a abrir, devolvendo o primeiro ficheiro no caso de erro de input
{
	string fil;
	bool validfile = true;
	do
	{
		cout <<"Introduce the name of the config file you want to use: ";
		cin >> fil;
		ifstream file(fil);
		if (file.fail())
		{
			validfile = false;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else validfile = true;
	} while (!validfile);
	return fil;
}


void createTable()
{
	char modo;
	bool modoValido;
	string filename;
	srand((unsigned)time(NULL));


	do
	{
		cout << "Manual mode (M/m) or automatic mode (A/a)? ";
		cin >> modo;
		cin.ignore(100, '\n');

		if ((int)modo == (int)'M' || (int)modo == (int)'m' || (int)modo == (int)'A' || (int)modo == (int)'a') // Verificacao de validade do modo
		{
			cout << "Valid mode" << endl;
			modoValido = true;
		}
		else
		{
			cout << "Invalid mode" << endl;
			modoValido = false;
		}
	} while (!modoValido);


	if (modoValido) // apenas vai continuar se o modo for valido
	{
		cout << "Introduce the name of the file where you want to save your board: ";
		cin >> filename;
		leNavios(escolheFicheiro(), modo, filename);  // Guarda a informacao sobre os navios 
	}

}
