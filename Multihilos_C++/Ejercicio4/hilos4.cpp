#include <iostream>
#include <unistd.h>
#include <thread>
#include <atomic>

using namespace std;

int n = 10000;

void funcion_incrementa(atomic<int>& contador)
{
	std::thread::id this_id = this_thread::get_id();
	printf("Hilo %ld Valor recibido: %d\n", this_id, n);  
	for(int i = 0; i < n; i++)
		contador++;

	sleep(1);
}

void funcion_decrementa(atomic<int>& contador)
{
	std::thread::id this_id = this_thread::get_id();
	printf("Hilo %ld Valor recibido: %d\n", this_id, n);
	for(int i = 0; i < n; i++)
		contador--;   
	sleep(1);
}


int main()
{
	atomic<int> contador(0);
	thread th1(funcion_incrementa, ref(contador) ), th2(funcion_decrementa, ref(contador));
	printf("Proceso principal espera que los hilos terminen\n");
	th1.join();
	th2.join();
	printf("El hilo principal termina\n");
	cout << "El valor de la variable global es: " << contador << endl;
	exit(0);
}