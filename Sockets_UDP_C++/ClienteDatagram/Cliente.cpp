#include <iostream>
#include "SocketDatagrama.h"
using namespace std;

int main()
{
	int puerto=7200;
	int tamMensaje=2;
	char ip[]="127.0.0.1";

	char res;
	char num[2];
	num[0] = 2;
	num[1] = 5;

	
	PaqueteDatagrama pds(num,tamMensaje,ip,puerto);

	SocketDatagrama sd(7200);
	

	sd.envia(pds);
	sd.recibe(pds);
	res = *(pds.obtieneDatos());
	printf("2 + 5 = %d\n", res);

	return 0;
}
