#include "Solicitud.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
 #include <unistd.h>
#include <time.h>
int main(int argc, char* argv[])
{
	if(argc < 4)
	{
		printf("Ejecute con los argumentos: [ip] [puerto] [cantidad]\n"); 
		exit(1);
	}

	Solicitud cliente1;
	char mensaje[4];
	int  cantidad, deposito;
	int nbd;
	cantidad = atoi(argv[3]);
	unsigned int total = 0;	
	srand(time(NULL));

	for(register unsigned int i = 0; i < cantidad; i++ )
	{
	/*	memcpy(&nbd, cliente1.doOperation (argv[1], atoi(argv[2]), 1, i + 1,mensaje), 4);
		printf("Solicitud id %d\n", nbd);
		if(nbd != (i + 1))
		{
			printf("Inconsitencia de datos\n");
			exit(1);
		}	
		*/ 
		deposito = rand()% 20 +1;
		//deposito = 1;
		printf("Hacer un deposito de %d\n", deposito );
		total += deposito;
		memcpy(mensaje, &deposito, 4);
		memcpy(&nbd, cliente1.doOperation (argv[1], atoi(argv[2]), 2, (i + 1), mensaje), 4);

		printf("En la cuenta hay %d \n", nbd);
		printf("La cuenta debe tener %d\n", total );
		if(nbd != total)
		{
			printf("Inconsitencia de datos\n");
			exit(1);
		}	
		printf("\n\n\n\n");	
	}
	
	return 0;
}

