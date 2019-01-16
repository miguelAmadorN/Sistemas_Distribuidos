#include "Respuesta.h"
#include <stdlib.h>
#include <string.h>
#include "Operaciones.h"
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include "Cajero.h"

using namespace std;

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		printf("Ejecute con el argumento: [puerto]\n");
		exit(1);
	}

	Respuesta servidor( atoi(argv[1]) );
	struct mensaje informacion;
	unsigned short tamInformacion = 0;
	char *datos, resultado[4];
	int respuesta;

	Cajero cajero;
	bool repetido = false;
	unsigned int id = 0;
	int deposito = 0;
	while(1)
	{
		memcpy(&informacion, servidor.getRequest() , sizeof(struct mensaje));
		memcpy(&tamInformacion, informacion.arguments, 2);
		datos = (char *) malloc(sizeof(char) * tamInformacion);
		memcpy(datos, &informacion.arguments[0] + 2, tamInformacion);
		cout << "Total informacion: " << tamInformacion <<endl;
		memcpy(&deposito, informacion.arguments + 2, 4);

/*
		for(int i = 0 ; i < tamInformacion; i++)
			printf("%c",datos[i] );
		printf("\n");
*/		
		repetido = false;
		if(id==informacion.requestId)	
			repetido = true;
			
		
	
		if(repetido == false)
		{
			printf("requestId %d\n", informacion.requestId);
			printf("Hacer un deposito de %d\n", deposito );
			id = informacion.requestId;		
			switch(informacion.operationId)
			{
				case 1:
					respuesta = cajero.getNbd();
					printf("Valor nbd: %d\n", respuesta);
					break;
				case 2: 
					cajero.agregar( deposito );
					respuesta = cajero.getNbd();
					printf("Actualizar nbd %d\n", respuesta);
					break;
				default:
					printf("ID de operacion invalida");
			}
			memcpy(resultado, &respuesta, 4);
			servidor.sendReply(resultado,informacion.IP, informacion.requestId,informacion.puerto);
		}
		else
		{
			printf("requestId repetido%d\n", informacion.requestId);
			respuesta = cajero.getNbd();
			printf("Valor nbd rep: %d\n", respuesta);
			memcpy(resultado, &respuesta, 4);
			servidor.sendReply(resultado,informacion.IP, informacion.requestId, informacion.puerto);
		}

	}

	return 0;
}



