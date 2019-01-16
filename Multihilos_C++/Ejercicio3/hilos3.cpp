#include <iostream>
#include <unistd.h>
#include <thread>

using namespace std;

int contador;

void funcion_incrementa(int valor)
{
	std::thread::id this_id = this_thread::get_id();
	printf("Hilo %ld Valor recibido: %d\n", this_id, valor);  
	for(int i = 0; i < valor; i++)
		contador++;

	sleep(1);
}

void funcion_decrementa(int valor)
{
	std::thread::id this_id = this_thread::get_id();
	printf("Hilo %ld Valor recibido: %d\n", this_id, valor);
	for(int i = 0; i < valor; i++)
		contador--;   
	sleep(1);
}


int main()
{
	contador = 0;
	int n = 5000;
	thread th1(funcion_incrementa, n), th2(funcion_decrementa, n);
	printf("Proceso principal espera que los hilos terminen\n");
	th1.join();
	th2.join();
	printf("El hilo principal termina\n");
	printf("Valor de la variable global %d\n", contador);
	exit(0);
}