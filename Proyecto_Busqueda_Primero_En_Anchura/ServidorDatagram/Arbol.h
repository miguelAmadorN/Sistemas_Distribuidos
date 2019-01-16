
#ifndef ARBOL_H
#define ARBOL_H
#include <vector>
#include "Nodo.h"
using namespace std;

const char VACIO = '*';
const int LIMITE = 181440;
class Arbol
{

private:
	unsigned int nodos;
	int niveles;
	char puzzleInicial[9];
	char puzzleObjetivo[9];
	char *camino,*temp;
	Nodo *inicial,*aux,*final;
	vector<Nodo> arbol;
	bool expIzquierda(char *puzzle);
	bool expDerecha(char *puzzle);
	bool expArriba(char *puzzle);
	bool expAbajo(char *puzzle);
	bool comprobar(char *puzzle);

public:
	Arbol(char pInicial[], char pObjetivo[], char tipoNodoIni);
	bool expandir();
	unsigned int getNodos();
	void setNodos(int nodos1);
	char * getCamino();
	int getNiveles();
	void  imprimirNodo(char* nodo);
	~Arbol();
};

#endif
