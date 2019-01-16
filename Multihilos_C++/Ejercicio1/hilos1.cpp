#include <iostream>
#include <unistd.h>
#include <thread>

using namespace std;
void funcion(int valor)
{
	std::thread::id this_id = this_thread::get_id();
	printf("Hilo %ld Valor recibido: %d\n", this_id, valor);    
	sleep(2);
}

int main()
{

	thread th1(funcion, 5), th2(funcion, 10);
	printf("Proceso principal espera que los hilos terminen\n");
	th1.join();
	th2.join();
	printf("El hilo principal termina\n");
	exit(0);
}