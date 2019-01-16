#include <iostream>
#include "Respuesta.h"
#include <bits/stdc++.h>
#include <string.h>
using namespace std;

struct mensaje mensajeCS;

Respuesta::Respuesta (int pl) 
{
	socketlocal = new SocketDatagrama(pl);
}

struct mensaje *Respuesta::getRequest(void)
{
	size_t tamStructMensaje = sizeof(struct mensaje);
	struct mensaje *mensajeCliente = (struct mensaje*) malloc(sizeof(struct mensaje)*1);
	PaqueteDatagrama paquete(tamStructMensaje);
	socketlocal-> recibe(paquete);
	memcpy(mensajeCliente, paquete.obtieneDatos(), tamStructMensaje);
		
	return mensajeCliente;
}
void Respuesta::sendReply(char *respuesta, char *ipCliente, int requestId,int puertoCliente)
{
	struct mensaje resp;
	//size_t tamCadena = strlen(respuesta), tam = sizeof( struct mensaje);
	size_t tamCadena = 4, tam = sizeof( struct mensaje);  //MODIFICAR tamCadena a la informacion de la respuesta
	
	char informacion[tam];
	resp.messageType = 1;
	resp.requestId = requestId;
	memcpy(resp.IP, ipCliente, 16);
	resp.puerto = puertoCliente;
	resp.operationId = 1;
	memcpy(resp.arguments, &tamCadena, 2);
	//memcpy(resp.arguments + 2, respuesta, tamCadena);
	memcpy(resp.arguments + 2, respuesta, tamCadena);
	memcpy(informacion, &resp, tam);
	PaqueteDatagrama paquete(informacion, tam , socketlocal -> getIP(), socketlocal -> getPuerto());
	socketlocal->envia(paquete);

}