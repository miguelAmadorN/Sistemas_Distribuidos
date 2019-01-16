#ifndef RESPUESTA_H
#define RESPUESTA_H
#include "Mensaje.h"
#include "SocketDatagrama.h"

class Respuesta
{
public:
	Respuesta(int pl);
	struct mensaje *getRequest(void);
	void sendReply( char *respuesta, char *ipCliente, int puertoCliente );
private:
	SocketDatagrama *socketlocal;
};

#endif