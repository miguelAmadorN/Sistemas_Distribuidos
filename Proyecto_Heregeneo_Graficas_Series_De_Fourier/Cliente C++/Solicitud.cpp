#include "Solicitud.h"
#include "Mensaje.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
 #include <unistd.h>
#include <stdio.h>
using namespace std;

Solicitud::Solicitud()
{
	socketlocal = new SocketDatagrama(0);
}

char * Solicitud:: doOperation(char *IP, int puerto, int operationId, int requestId,char *arguments)
{

	struct mensaje strmensaje;
	size_t tam = sizeof(struct mensaje);
	//unsigned short tamCadena = strlen(arguments);
	unsigned short tamCadena = 3200;
	char informacion[tam];
	int bytesRecibidos, intentos = 0;

	
	strmensaje.messageType = 0;
	strmensaje.requestId = requestId;
	memcpy(strmensaje.IP, IP, 16);
	strmensaje.puerto = puerto;
	strmensaje.operationId = operationId;
	memcpy(strmensaje.arguments, &tamCadena, 2);
	memcpy(strmensaje.arguments + 2, arguments, tamCadena);
	memcpy(informacion, &strmensaje, tam);

	PaqueteDatagrama paquete_a_enviar(informacion, tam, IP, puerto);
	PaqueteDatagrama paquete_recibido(tam);
		
	do
	{
		socketlocal -> envia(paquete_a_enviar);
		bytesRecibidos = socketlocal -> recibeTimeout(paquete_recibido, 3,0);
		intentos++;
		printf("Intentos: %d\n", intentos );
		if(bytesRecibidos != -1)
		{
			memcpy(&strmensaje, paquete_recibido.obtieneDatos(), tam);
			if(requestId != strmensaje.requestId )
			{
				printf("MsT: %d",strmensaje.messageType);
				printf("OpId: %d", strmensaje.operationId);
				printf("Puerto: %d",strmensaje.puerto);
				printf("Idrecibido %d\n",strmensaje.requestId);
				printf("Id esperado %d\n", requestId);
				bytesRecibidos = -1;
				intentos--;
			}
 		}

	}while(( bytesRecibidos == -1 && intentos < 7 ));


	if(intentos > 6)
	{
		printf("El servidor está ocupado, por favor intente más tarde\n");
		exit(0);
	}

	cout << "\nTipo mensaje:" << strmensaje.messageType << "\nId:" << strmensaje.requestId << "\nIP:"<< strmensaje.IP << "\nPuerto: " << strmensaje.puerto << endl;

	return NULL;
}
