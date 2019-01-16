#include <iostream>
#include "SocketDatagrama.h"
using namespace std;

int main()
{
	int puerto=7200;
	int tamMensaje=2;

	char res;
	char *num =(char *) malloc(sizeof(char) * tamMensaje);

	PaqueteDatagrama pdr(tamMensaje);
	SocketDatagrama sd(puerto);

	while(1)
	{
		sd.recibe(pdr);
		num = pdr.obtieneDatos();
		res = num[0] + num[1];
		PaqueteDatagrama pds(&res, 1, pdr.obtieneDireccion(), pdr.obtienePuerto());
		sd.envia(pds);
	}

	free(num);
	return 0;
}