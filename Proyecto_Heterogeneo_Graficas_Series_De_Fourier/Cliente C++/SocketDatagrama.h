#ifndef SOCKETDATAGRAMA_H
#define SOCKETDATAGRAMA_H
#include "PaqueteDatagrama.h"
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

class SocketDatagrama
{

public:
	SocketDatagrama( int );
	~SocketDatagrama();
	int recibe(PaqueteDatagrama & p);
	int envia(PaqueteDatagrama & p);
	int getPuerto();
	char* getIP();
	int recibeTimeout(PaqueteDatagrama & p, time_t segundos, suseconds_t microsegundos);

private:
	struct sockaddr_in direccionLocal;
	struct sockaddr_in direccionForanea;
	char *ip;
	int s; //ID socket
	struct timeval timeout;
};

#endif