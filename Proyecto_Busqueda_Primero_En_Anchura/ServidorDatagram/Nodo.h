#ifndef NODO_H
#define NODO_H

class Nodo
{
private: 
	char puzzle[9];
	char tipoExp;//0 nodo inicial, 1 izq, 2 der, 3 arriba, 4 abajo
	Nodo *nodoPadre;
	

public:
	Nodo(char puzz[], char tipoExp, Nodo *padre);
	char* getPuzzle();
	Nodo* getNodoPadre();
	void setNodoPadre(Nodo* nodoPadre1);
	char getTipoExp();
	~Nodo();
};

#endif