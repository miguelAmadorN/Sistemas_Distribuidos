#include "Cajero.h"
#include <iostream>
Cajero::Cajero()
{
	nbd = 0;
}

void Cajero::agregar( int deposito )
{
	nbd+= deposito;
}

int Cajero::getNbd()
{
	return nbd;
}

Cajero::~Cajero()
{

}