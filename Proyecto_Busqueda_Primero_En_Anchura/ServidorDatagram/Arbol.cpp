#include "Arbol.h"
#include <string.h>
#include <iostream>

Arbol:: Arbol(char pInicial[], char pObjetivo[], char tipoNodoIni)
{
	memcpy(puzzleInicial,pInicial, sizeof(char) * 9);
	memcpy(puzzleObjetivo,pObjetivo, sizeof(char) * 9);
	inicial = new Nodo(pInicial, tipoNodoIni, NULL);
	niveles = 0;
	nodos = 1;
	arbol.reserve( LIMITE );
	arbol.push_back(*inicial);
}

bool Arbol::comprobar(char *puzzle)
{	
	if(strncmp(puzzle, puzzleObjetivo,9) == 0)
		return true;
	return false;
}

bool Arbol:: expIzquierda(char *puzzle)
{
	register char i;
	for( i = 0; i < 9; i++)
	{
		if( strncmp(puzzle + i, &VACIO, 1) == 0 )
		{
			break;
		}
	}
	if(i == 2 || i == 4 || i == 8)
		return false;
	
	memcpy(puzzle + i, puzzle + i + 1, 1);
	memcpy(puzzle + i + 1, &VACIO, 1);
	nodos++;
	printf("Numero de nodos: %d\n", nodos);
	return true;
}

bool Arbol::expDerecha(char* puzzle)
{
	register char i;
	for( i = 0; i < 9; i++)
	{
		if( strncmp(puzzle + i, &VACIO, 1) == 0 )
		{
			break;
		}
	}
	if(i == 0 || i == 3 || i == 6)
		return false;
	
	memcpy(puzzle + i, puzzle + i - 1, 1);
	memcpy(puzzle + i - 1, &VACIO, 1);
	nodos++;
	printf("Numero de nodos: %d\n", nodos);
	return true;
}

bool Arbol::expArriba(char* puzzle)
{
	register char i;
	for( i = 0; i < 9; i++)
	{
		if( strncmp(puzzle + i, &VACIO, 1) == 0 )
		{
			break;
		}
	}
	if(i == 6 || i == 7 || i == 8)
		return false;
	
	memcpy(puzzle + i, puzzle + i + 3, 1);
	memcpy(puzzle + i + 3, &VACIO, 1);
	nodos++;
	printf("Numero de nodos: %d\n", nodos);
	return true;
}

bool Arbol::expAbajo(char* puzzle)
{
	register char i;
	for( i = 0; i < 9; i++)
	{
		if( strncmp(puzzle + i, &VACIO, 1) == 0 )
		{
			break;
		}
	}
	if(i == 0 || i == 1 || i == 2)
		return false;
	
	memcpy(puzzle + i, puzzle + i - 3, 1);
	memcpy(puzzle + i - 3, &VACIO, 1);
	nodos++;
	printf("Numero de nodos: %d\n", nodos);
	return true;
}


bool Arbol::expandir()
{	
	bool encontrado1=false, expansion;
	int i=0;
	//Menor a 9!/2
	while(nodos < LIMITE )
	{		
		aux = &( arbol[i] );
		char puzzleIzquierda[9],puzzleDerecha[9],puzzleArriba[9],puzzleAbajo[9];
		memcpy(puzzleIzquierda, aux->getPuzzle(), 9 );
		memcpy(puzzleDerecha, aux->getPuzzle(), 9);
		memcpy(puzzleArriba, aux->getPuzzle(), 9);
		memcpy(puzzleAbajo, aux->getPuzzle(), 9);

		if(aux->getTipoExp() != 2)
		{
			expansion = expIzquierda( puzzleIzquierda );
			if(expansion)
			{
				Nodo temp1(puzzleIzquierda, 1, aux);
				arbol.push_back( temp1 );
				encontrado1 = comprobar(puzzleIzquierda);
				if(encontrado1)
				{
					final = &temp1;
					break;
				}
			}
		}
		if(aux->getTipoExp() != 1 )
		{
			expansion = expDerecha( puzzleDerecha );
			if(expansion)
			{
				Nodo temp2(puzzleDerecha, 2, aux);
				arbol.push_back( temp2 );
				encontrado1 = comprobar( puzzleDerecha );
				if(encontrado1)
				{
					final = &temp2;
					break;
				}
			}
		}
		if(aux->getTipoExp() != 4 )
		{
			expansion = expArriba( puzzleArriba );
			if( expansion )
			{
				Nodo temp3(puzzleArriba, 3, aux);
				arbol.push_back( temp3 );
				encontrado1 = comprobar( puzzleArriba );
				if(encontrado1)
				{
					final = &temp3;
					break;
				}
			}
		}
		if(aux->getTipoExp() != 3 )
		{
			expansion = expAbajo( puzzleAbajo );
			if(expansion)
			{
				Nodo temp4(puzzleAbajo, 4, aux);
				arbol.push_back( temp4 );
				encontrado1 = comprobar(puzzleAbajo);
				if(encontrado1)
				{
					final = &temp4;
					break;
				}
			}
		}
		i++;
	}

	if(encontrado1)
	{
		aux = final;
	//	imprimirNodo(final->getPuzzle());
		while(aux != NULL)
		{
			aux = aux->getNodoPadre();
			niveles++;
		}
	}
	return encontrado1;
}


unsigned int Arbol::getNodos()
{	
	return nodos;
}

void Arbol::setNodos(int nodos1)
{
	nodos = nodos1;
}

char* Arbol::getCamino()
{
	register int i = 0;
	int tamF = niveles * 9;
	aux = final;
	//imprimirNodo(final->getPuzzle());
	temp = (char *) malloc(sizeof(char) * tamF);
	while(aux!=NULL)
	{
		memcpy(temp + tamF - (i + 1) * 9 , aux->getPuzzle(), sizeof(char)*9);
		aux = aux->getNodoPadre();
		i++;
	}
	return temp;
} 

int Arbol::getNiveles()
{
	return niveles;
}

void Arbol:: imprimirNodo(char* nodo)
{
 	printf("\n\n");
	printf("-------------\n");
	printf("| %c | %c | %c |\n", nodo[0], nodo[1], nodo[2]);
	printf("-------------\n");
	printf("| %c | %c | %c |\n", nodo[3], nodo[4], nodo[5]);
	printf("-------------\n");
	printf("| %c | %c | %c |\n", nodo[6], nodo[7], nodo[8]);
	printf("-------------\n\n");
}


Arbol::~Arbol()
{

}
