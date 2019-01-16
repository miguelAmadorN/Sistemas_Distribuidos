#ifndef SOLICITUD_H
#define SOLICITUD_H
#include "SocketDatagrama.h"
const int INTENTOS = 7; 


class Solicitud
{
	public:
		Solicitud();
		char * doOperation(char *IP, int puerto, int operationId, unsigned int requestId,char *arguments);
	private:
		SocketDatagrama *socketlocal;
};

#endif
