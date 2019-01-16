#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "InterfazCliente.h"

char VACIO = '*';
void nodoEjemplo();

void getNodoInicial(char* puzz)
{	 
	char entrada[17];
	char valido;
	do
	{
		printf("Introduce el nodo inicial\n");
		printf("Ejemplo: 1,2,*,3,4,5,6,7,8\n");
		nodoEjemplo();
		printf("* representa el nodo vacio\n");
		scanf("%s",entrada);
		valido = validacionPuzzle(entrada, puzz);
		if(!valido)
			printf("Nodo Invalido\n");
	}while(!valido);
}

void getNodoFinal(char* puzz)
{	 
	char entrada[17];
	char valido;
	do
	{
		printf("Introduce el nodo final\n");
		scanf("%s",entrada);
		valido = validacionPuzzle(entrada, puzz);
		if(!valido)
			printf("Nodo Invalido\n");
	}while(!valido);
	
}


char validacionPuzzle(char * entrada, char *puzz)
{
	int aux = 0;
	char cont = 0;
	for(char i = 0, j = 0; i < 17; i = i + 2, j++ )
	{
		memcpy(&aux, entrada + i, 1); 
		if((aux > 48 && aux < 57) || aux == 42)
		{
			memcpy( puzz + j ,&aux, 1);
			if(aux == 42)
				cont++;
		}
		else
		{
			cont = 2;
			break;
		}
	}
	if(cont == 1)
		return 1;
	else
		return 0;
}


void imprimirNodo(char* nodo)
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


void nodoEjemplo()
{
	printf("\n\n");
	printf("-------------\n");
	printf("| 1 | 2 | * |\n");
	printf("-------------\n");
	printf("| 3 | 4 | 5 |\n");
	printf("-------------\n");
	printf("| 6 | 7 | 8 |\n");
	printf("-------------\n\n");
}
/**
	Existen 3 tipos de nodos de acuerdo a la cantidad de subnodos que puede producir en una expansion.
	casos 
	1 = 3 subnodos
	2 = 4 subnodos
	3 = 2 subnodos   -->5 subnodos
**/
char verificarTipoNodo(char * nodo)
{
	int i;
	for( i = 0; i < 9; i++ )
	{
		if(strncmp(&nodo[i], &VACIO, 1) == 0)
			break;
	}
	if(i == 4)
		return 2;

	if(i == 0 || i == 2 || i == 6 || i == 8)
		return 3;

	return 1;

}

void inicializarPack(char tipoNodoIni, char* nodoFinal, char * pack )
{
	//memcpy(pack + 1, nodoInicial, sizeof(char) * 9);
	memcpy(pack + 9, nodoFinal, sizeof(char) * 9);
	memcpy(pack + 18, &tipoNodoIni, sizeof(char) * 1);
}



void expIzquierda(char *puzzle)
{
	register char i;
	for( i = 0; i < 9; i++)
		if( strncmp(puzzle + i, &VACIO, 1) == 0 )
			break;
	
	memcpy(puzzle + i, puzzle + i + 1, 1);
	memcpy(puzzle + i + 1, &VACIO, 1);
}

void expIzquierda(char *puzzle, char pnv)
{
	memcpy(puzzle + pnv, puzzle + pnv + 1, 1);
	memcpy(puzzle + pnv + 1, &VACIO, 1);
}


void expDerecha(char* puzzle)
{
	register char i;
	for( i = 0; i < 9; i++)
		if( strncmp(puzzle + i, &VACIO, 1) == 0 )
			break;

	memcpy(puzzle + i, puzzle + i - 1, 1);
	memcpy(puzzle + i - 1, &VACIO, 1);
}

void expDerecha(char* puzzle, char pnv)
{
	memcpy(puzzle + pnv, puzzle + pnv - 1, 1);
	memcpy(puzzle + pnv - 1, &VACIO, 1);
}

void expArriba(char* puzzle)
{
	register char i;
	for( i = 0; i < 9; i++)
	{
		if( strncmp(puzzle + i, &VACIO, 1) == 0 )
		{
			break;
		}
	}
	memcpy(puzzle + i, puzzle + i + 3, 1);
	memcpy(puzzle + i + 3, &VACIO, 1);
}

void expArriba(char* puzzle, char pnv)
{
	memcpy(puzzle + pnv, puzzle + pnv + 3, 1);
	memcpy(puzzle + pnv + 3, &VACIO, 1);
}

void expAbajo(char* puzzle)
{
	register char i;
	for( i = 0; i < 9; i++)
		if( strncmp(puzzle + i, &VACIO, 1) == 0 )
			break;

	memcpy(puzzle + i, puzzle + i - 3, 1);
	memcpy(puzzle + i - 3, &VACIO, 1);
}

void expAbajo(char* puzzle, char pnv)
{
	memcpy(puzzle + pnv, puzzle + pnv - 3, 1);
	memcpy(puzzle + pnv - 3, &VACIO, 1);
}



int posicionNodoVacio(char* puzzle)
{
	register int i;
	for( i = 0; i < 9; i++)
	{
		if( strncmp(puzzle + i, &VACIO, 1) == 0 )
		{
			break;
		}
	}
	return i;
}