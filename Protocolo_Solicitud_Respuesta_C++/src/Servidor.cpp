#include "Respuesta.h"
#include <stdlib.h>
#include <string.h>
#include "Operaciones.h"
#include <stdio.h>
#include <iostream>

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
	char *datos, *resultado;

	while(1)
	{
		memcpy(&informacion, servidor.getRequest() , sizeof(struct mensaje));
		memcpy(&tamInformacion, informacion.arguments, 2);
		datos = (char *) malloc(sizeof(char) * tamInformacion);
		memcpy(datos, &informacion.arguments[0] + 2, tamInformacion);
		cout << "Total informacion: " << tamInformacion <<endl;

		for(int i = 0 ; i < tamInformacion; i++)
			printf("%c",datos[i] );
		printf("\n");
	

		switch(informacion.operationId)
		{
			case 1:
				printf("Invertir cadena\n");
				break;
			default:
				printf("ID de operacion invalida");
		}

		servidor.sendReply(datos,informacion.IP, informacion.puerto);

	}

	return 0;
}



