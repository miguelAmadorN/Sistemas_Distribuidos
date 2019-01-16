#include "Nodo.h"
#include <iostream>
#include <string.h>

Nodo::Nodo(char puzz[], char tipo, Nodo *padre)
{
	memcpy(puzzle, puzz, sizeof(char)*9);
	tipoExp = tipo;
	nodoPadre = padre;
}


char* Nodo::getPuzzle()
{
	return puzzle;
}

Nodo* Nodo::getNodoPadre()
{
	return nodoPadre;
}
void Nodo:: setNodoPadre(Nodo* nodoPadre1)
{
	nodoPadre = nodoPadre1;
}

char Nodo::getTipoExp()
{
	return tipoExp;
}

Nodo::~Nodo()
{
		
}