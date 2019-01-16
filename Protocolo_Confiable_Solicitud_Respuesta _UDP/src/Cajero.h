#ifndef CAJERO_H
#define CAJERO_H

class Cajero
{
public:

	Cajero();
	~Cajero();
	void agregar( int deposito );
	int getNbd();

private:
	int nbd;
};



#endif