#include "Solicitud.h"
#include "Mensaje.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

Solicitud::Solicitud()
{
	socketlocal = new SocketDatagrama(0);
}

char * Solicitud:: doOperation(char *IP, int puerto, int operationId, char *arguments)
{
	struct mensaje strmensaje;
	size_t tam = sizeof(struct mensaje);
	unsigned short tamCadena = strlen(arguments);
	char informacion[tam];
	
	strmensaje.messageType = 0;
	strmensaje.requestId = 1;
	memcpy(strmensaje.IP, IP, 16);
	strmensaje.puerto = puerto;
	strmensaje.operationId = 1;
	memcpy(strmensaje.arguments, &tamCadena, 2);
	memcpy(strmensaje.arguments + 2, arguments, tamCadena);
	memcpy(informacion, &strmensaje, tam);

	PaqueteDatagrama paquete_a_enviar(informacion, tam, IP, puerto);
	socketlocal -> envia(paquete_a_enviar);

	PaqueteDatagrama paquete_recibido(tam);
	socketlocal -> recibe(paquete_recibido);

	memcpy(&strmensaje, paquete_recibido.obtieneDatos(), tam);
	cout << "\nTipo mensaje:" << strmensaje.messageType << "\nId:" << strmensaje.requestId << "\nIP:"<< strmensaje.IP << "\nPuerto: " << strmensaje.puerto << endl;
	tamCadena=0;
	memcpy(&tamCadena, strmensaje.arguments, 2);
	char *argumentos = (char *) malloc(sizeof(char) * tamCadena);
	memcpy(argumentos, strmensaje.arguments + 2, tamCadena);

	return argumentos;
}
