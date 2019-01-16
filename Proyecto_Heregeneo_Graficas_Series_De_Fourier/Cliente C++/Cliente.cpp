#include "Solicitud.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "Generador.h"
#include <math.h> 
#include "Semaforo.h"
#include <thread>
#include <iostream>

using namespace std;
double an(int n)
{
	return (double)((double)1 - (double)pow(-1, n)) / ((double)M_PI * (double)pow(n, 2));
}

double bn(int n)
{
	return  (double)((double)1 / (double)n);
}


CPlano *coordenadas;
const int ANCHO = 800;
const int ALTO = 600;
const int NUMT = 400;
Semaforo sem1, sem2;
char *ip;
int puerto;
Generador generador( M_PI/2, an, bn,  M_PI , NUMT);
Solicitud cliente1;
int i=0;
void generar()
{
	char informacion[sizeof(short)*NUMT*2];
	CPlano *coor;
	Coordenada *coors;
	while(1)
	{
		coors = generador.getCoordenadas(i);
		coor = generador.convertirCoordenadasPlanoCartesiano(ANCHO, ALTO, coors);
		free(coors);
		i++;
		sem1.wait();
		coordenadas = coor;
		free(coor);
		memcpy(informacion, coordenadas, sizeof(CPlano) * NUMT);
		cliente1.doOperation (ip, puerto, 1, i, informacion);
		//sleep(1);
		sem2.post();
	}
}


void eliminar()
{
	char informacion[sizeof(short)*NUMT*2];
	while(1)
	{	
		i++;
		sem2.wait();
		memcpy(informacion, coordenadas, sizeof(CPlano) * NUMT);
		cliente1.doOperation (ip, puerto, 2, i, informacion);
		sem1.post();
	}
}




int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		printf("Ejecute con los argumentos: [ip] [puerto] \n"); 
		exit(1);
	}

	i = 0;
	ip = argv[1];
	puerto = atoi(argv[2]);
	sem1.init(1);
	sem2.init(0);
	thread th1(generar), th2(eliminar);
	th1.join();
	th2.join();

	return 0;
}

