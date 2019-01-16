#include "Generador.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Generador::Generador(double a0_, double (* an_)(int), double (* bn_)(int), double T_, int Resolucion_)
{
	a0 = a0_ / 2;
	an = an_;
	bn = bn_;
	T = T_;
	Resolucion = Resolucion_;
}

double Generador::getValorSerieFourier( int n, double t )
{
	double valor = a0;
	double c = 2 * M_PI * t / T;
	for(register int i = 1; i <= n; i++)
	{
		valor += an(i) * cos( c * i ) + bn(i) * sin( c * i );
	}
	return valor;
}

Coordenada * Generador::getCoordenadas( int n )
{
	double incremento = T / Resolucion;
	Coordenada *coors = (Coordenada *)malloc(Resolucion * sizeof(Coordenada));
	register int i = 0;
	double j = T / 2 * (-1);   
	//double fin = T / 2;
	do
	{
		coors[i].x = j; 
		coors[i].y = getValorSerieFourier(n, j);
		i++;
		j += incremento;
	}while(i < Resolucion);
	
	return coors;
}


CPlano* Generador::convertirCoordenadasPlanoCartesiano(int Ancho_plano, int Alto_plano, Coordenada *coordenadas)
{
	CPlano *coors = (CPlano *) malloc(sizeof(CPlano) * Resolucion);
	int ajusteAlto = (Alto_plano / 2);
	int ajusteAncho = (Ancho_plano / 2) - (Resolucion/2);
	double amplificacion;

	double valorMaximo = absX(coordenadas[0].y);
	register int i;
	for(i = 1; i < Resolucion; i++)
	{
		if( valorMaximo < absX(coordenadas[i].y) )
			valorMaximo = absX(coordenadas[i].y);
	}

	amplificacion = (double)((double)ajusteAlto / (double)valorMaximo);

	for(i = 0; i < Resolucion; i++)
	{
		coors[i].y = coordenadas[i].y * amplificacion;
		coors[i].y  = ajusteAlto - coors[i].y;
		coors[i].x = ajusteAncho + i;
	}
	return coors;
}