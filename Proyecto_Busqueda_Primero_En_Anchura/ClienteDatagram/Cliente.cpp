#include <iostream>
#include <string.h>
#include "SocketDatagrama.h"
#include "InterfazCliente.h"

using namespace std;

int main()
{
	/**
		VERIFICAR QUE SI SE ENCUNTRA EN EL CLIENTE YA DESDE AQUI SE IMPRIMA
		Modificar puertos e IP's 
	**/
	
	int puerto1=7201;
	int puerto2=7202;
	int puerto3=7203;
	int puerto4=7204;

	int tamMensaje = 19*sizeof(char);
	int tipoNodo,caso;

	char ip1[]="10.0.0.3";
	char ip2[]="10.100.79.143";
	char ip3[]="10.100.66.105";


	char nodoInicial[tamMensaje];
	char nodoFinal[tamMensaje];
	getNodoInicial(nodoInicial);
	caso = verificarTipoNodo(nodoInicial);
	getNodoFinal(nodoFinal);


/** 
//Caso imposible
	char nodoInicial[] = "87654321*";
	caso = verificarTipoNodo(nodoInicial);
	char nodoFinal[] = "*12345678";
**/

	char pack1[tamMensaje];
	char pack2[tamMensaje];
	char pack3[tamMensaje];
	char packAux[tamMensaje];
	memcpy(pack1, nodoInicial, 9);
	memcpy(pack2, nodoInicial, 9);
	memcpy(pack3, nodoInicial, 9);

	PaqueteDatagrama pds(tamMensaje);
	SocketDatagrama sd(7210);

	if(caso == 1)
	{
		tipoNodo = posicionNodoVacio(nodoInicial);
		printf("IF1: %d\n", tipoNodo );
		if(tipoNodo == 1)
		{
			expIzquierda(pack1, tipoNodo);
			expDerecha(pack2, tipoNodo);
			expArriba(pack3, tipoNodo);
			inicializarPack( 1, nodoFinal, pack1 );
			inicializarPack( 2, nodoFinal, pack2 );
			inicializarPack( 3, nodoFinal, pack3 );
		}
		else if(tipoNodo == 3)
		{
			expIzquierda(pack1, tipoNodo);
			expArriba(pack2, tipoNodo);
			expAbajo(pack3, tipoNodo);
			inicializarPack( 1, nodoFinal, pack1 );
			inicializarPack( 3, nodoFinal, pack2 );
			inicializarPack( 4, nodoFinal, pack3 );
		}
		else if(tipoNodo == 5)
		{
			expDerecha(pack1, tipoNodo);
			expArriba(pack2, tipoNodo);
			expAbajo(pack3, tipoNodo);
			inicializarPack( 2, nodoFinal, pack1 );
			inicializarPack( 3, nodoFinal, pack2 );
			inicializarPack( 4, nodoFinal, pack3 );			
		}
		else if(tipoNodo == 7)
		{
			expIzquierda(pack1, tipoNodo);
			expDerecha(pack2, tipoNodo);
			expAbajo(pack3, tipoNodo);
			inicializarPack( 1, nodoFinal, pack1 );
			inicializarPack( 2, nodoFinal, pack2 );
			inicializarPack( 4, nodoFinal, pack3 );
		}

		PaqueteDatagrama pds1(pack1,tamMensaje,ip1,puerto1);
		PaqueteDatagrama pds2(pack2,tamMensaje,ip2,puerto2);
		PaqueteDatagrama pds3(pack3,tamMensaje,ip3,puerto3);

		sd.envia(pds1);
		sd.envia(pds2);
		sd.envia(pds3);
	}
	else if(caso == 2)
	{
		printf("IF2\n" );
		char pack4[tamMensaje];
		memcpy(pack4, nodoInicial, 9);
		expIzquierda(pack1);
		expDerecha(pack2);
		expArriba(pack3);
		expAbajo(pack4);

		inicializarPack( 1, nodoFinal, pack1 );
		inicializarPack( 2, nodoFinal, pack2 );
		inicializarPack( 3, nodoFinal, pack3 );
		inicializarPack( 4, nodoFinal, pack4 );

		PaqueteDatagrama pds1(pack1, tamMensaje, ip1, puerto1);
		PaqueteDatagrama pds2(pack2, tamMensaje, ip2, puerto2);
		PaqueteDatagrama pds3(pack3, tamMensaje, ip3, puerto3);
		PaqueteDatagrama pds4(pack4, tamMensaje, ip3, puerto4);

		sd.envia(pds1);
		sd.envia(pds2);
		sd.envia(pds3);
		sd.envia(pds4);

	}
	else
	{
		char pack4[tamMensaje];
		memcpy(pack4, nodoInicial, 9);
	
		tipoNodo = posicionNodoVacio(nodoInicial);
		printf("IF3: %d\n", tipoNodo );

		if(tipoNodo == 0)
		{
			expIzquierda(pack1, tipoNodo);
			expArriba(pack2, tipoNodo);
			memcpy(packAux, pack2, 9);
			memcpy(pack3, pack2, 9);
			expIzquierda(pack2, 3);
			expArriba(pack3, 3);
			inicializarPack( 1, nodoFinal, pack1 );
			inicializarPack( 1, nodoFinal, pack2 );
			inicializarPack( 3, nodoFinal, pack3 );

		}
		else if(tipoNodo == 2)
		{
			expDerecha(pack1, tipoNodo);
			expArriba(pack2, tipoNodo);
			memcpy(packAux, pack2, 9);
			memcpy(pack3, pack2, 9);
			expDerecha(pack2, 5);
			expArriba(pack3, 5);
			inicializarPack( 2, nodoFinal, pack1 );
			inicializarPack( 2, nodoFinal, pack2 );
			inicializarPack( 3, nodoFinal, pack3 );

		}
		else if(tipoNodo == 6)
		{
			expIzquierda(pack1, tipoNodo);
			expAbajo(pack2, tipoNodo);
			memcpy(packAux, pack2, 9);
			memcpy(pack3, pack2, 9);
			expIzquierda(pack2, 3);
			expAbajo(pack3, 3);
			inicializarPack( 1, nodoFinal, pack1 );
			inicializarPack( 1, nodoFinal, pack2 );
			inicializarPack( 4, nodoFinal, pack3 );
		}
		else if(tipoNodo == 8)
		{
			expDerecha(pack1, tipoNodo);
			expAbajo(pack2, tipoNodo);
			memcpy(packAux, pack2, 9);
			memcpy(pack3, pack2, 9);
			expDerecha(pack2, 5);
			expAbajo(pack3, 5);
			inicializarPack( 2, nodoFinal, pack1 );
			inicializarPack( 2, nodoFinal, pack2 );
			inicializarPack( 4, nodoFinal, pack3 );
		}

		PaqueteDatagrama pds1(pack1,tamMensaje,ip1,puerto1);
		PaqueteDatagrama pds2(pack2,tamMensaje,ip2,puerto2);
		PaqueteDatagrama pds3(pack3,tamMensaje,ip3,puerto3);


		sd.envia(pds1);
		sd.envia(pds2);
		sd.envia(pds3);
	}

	printf("Se han enviado los datos\n");
	int tamMensajeRec = 1024;
	char msjRec[tamMensajeRec];
	int niveles = 0;

	PaqueteDatagrama pdr(tamMensajeRec);
	sd.recibe(pdr);
	memcpy(msjRec,pdr.obtieneDatos(),tamMensajeRec);
	memcpy(&niveles, &msjRec[0], 1);

	bool en = false;
	char t = 0;
	if( strncmp(pack1, nodoFinal, 9) == 0 )
		en = true;
	if( strncmp(pack2, nodoFinal, 9) == 0 )
		en = true;
	if( strncmp(pack3, nodoFinal, 9) == 0 )
		en = true;
	if(caso == 3)
		if( strncmp(packAux, nodoFinal, 9) == 0 )
		{
			en = true;
			t=1;
		}
	if(en)
	{
		printf("Solucion en el cliente\n");
		imprimirNodo(nodoInicial);
		if(caso == 3 && t)
			imprimirNodo(packAux);
		imprimirNodo(nodoFinal);
	}


    if(!en)
    {
		if(niveles)
		{
			printf("Tiene solucion\n");
		//	printf("Numero de niveles: %d\n",niveles );
			imprimirNodo(nodoInicial);
			if(caso == 3)
				imprimirNodo(packAux);
			for(int i = 0; i < niveles; i++)
			{	
				memcpy(packAux , msjRec + 9 * i + 1, 9);
				imprimirNodo(packAux);
			}
		}
		else 
		{
			printf("No tiene solucion\n");
		}
	}

	return 0;
}
