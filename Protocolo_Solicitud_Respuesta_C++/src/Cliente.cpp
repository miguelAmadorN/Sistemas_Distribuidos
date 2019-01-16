#include "Solicitud.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		printf("Ejecute con los argumentos: [ip] [puerto]\n"); 
		exit(1);
	}

	Solicitud cliente1;
	int ordenaCadena = 0;
	char mensaje[] = "Este mensaje se va a invertir";
	char *cadenota = mensaje;

	printf("La respuesta del servidor es <%s>\n",cliente1.doOperation (argv[1], atoi(argv[2]), ordenaCadena, cadenota));

	return 0;
}

