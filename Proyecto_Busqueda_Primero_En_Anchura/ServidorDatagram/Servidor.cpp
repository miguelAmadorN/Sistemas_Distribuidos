#include <iostream>
#include <stdio.h>
#include <string.h>
#include "SocketDatagrama.h"
#include "Arbol.h"
using namespace std;

int main(int argc, char *argv[])
{

	if(argc < 2)
	{
		printf("Introduce puerto al ejecutar, ejemplo:\n");
		printf("./Servidor 7200\n");
		exit(0);
	}
	int puerto=atoi(argv[1]);
	int tamMensaje = 19*sizeof(char);
	int tamMensajeEnvio;

	bool res;
	char puzzles[tamMensaje];
	char pIni[9], pObj[9];
	PaqueteDatagrama pdr(tamMensaje);
	SocketDatagrama sd(puerto);
	size_t t = sizeof(char)*9;
	char tipoNodoIni;

	while(1)
	{
		sd.recibe(pdr);
		memcpy(puzzles, pdr.obtieneDatos(), tamMensaje);
		memcpy(&pIni, puzzles, t);
		memcpy(&pObj, puzzles + 9, t);
		memcpy(&tipoNodoIni, puzzles + 18, 1);

		Arbol arbol(pIni, pObj, tipoNodoIni);

		printf("Tipo nodo: %d\n", tipoNodoIni);
		printf("Ini: %c,%c,%c,%c,%c,%c,%c,%c,%c\n", pIni[0], pIni[1], pIni[2], pIni[3], pIni[4], pIni[5], pIni[6], pIni[7], pIni[8] );
		printf("Fin: %c,%c,%c,%c,%c,%c,%c,%c,%c\n", pObj[0], pObj[1], pObj[2], pObj[3], pObj[4], pObj[5], pObj[6], pObj[7], pObj[8] );

		arbol.imprimirNodo(pIni);
		arbol.imprimirNodo(pObj);

		res = arbol.expandir();
		if(res)
		{
			tamMensajeEnvio = arbol.getNiveles()*9+1;
			char camino[tamMensajeEnvio];
			camino[0] = arbol.getNiveles();
			memcpy(camino + 1, arbol.getCamino(), tamMensajeEnvio -1 );
			PaqueteDatagrama pds( camino, tamMensajeEnvio, pdr.obtieneDireccion(), pdr.obtienePuerto());
			sd.envia(pds);
			printf("Con solucion\n");
			printf("Numero de niveles: %d\n",camino[0]);
		}
		else
		{
			char camino[1];
			camino[0] = 0;
			PaqueteDatagrama pds( camino, 1, pdr.obtieneDireccion(), pdr.obtienePuerto());
			sd.envia(pds);
			printf("NO TIENE SOLUCION\n");
		}
		

		
	}


	return 0;
}