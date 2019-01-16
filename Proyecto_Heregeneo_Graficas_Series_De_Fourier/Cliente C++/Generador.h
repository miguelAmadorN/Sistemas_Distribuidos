#ifndef GENERADOR_H
#define GENERADOR_H
#include "Coordenada.h"
#include "FuncionesAuxiliares.h"

class Generador
{

private:
	double a0;
	double (* an)(int);
	double (* bn)(int);
	double T;
	double getValorSerieFourier( int n, double t );
	int Resolucion;


public:
	Generador(double a0_, double (* an_)(int), double (* bn_)(int), double T_, int Resolucion);
	Coordenada *getCoordenadas( int n );
	CPlano* convertirCoordenadasPlanoCartesiano(int Ancho_plano, int Alto_plano, Coordenada *coordenadas);
};

#endif