#include <iostream>
#include "SocketDatagrama.h"
#include <string.h>
#include <stdio.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>


using namespace std;

SocketDatagrama::SocketDatagrama( int puerto )
{
	s = socket(AF_INET, SOCK_DGRAM, 0);
	bzero((char *)&direccionLocal, sizeof(direccionLocal));
  direccionLocal.sin_family = AF_INET;
  direccionLocal.sin_addr.s_addr = INADDR_ANY;
  direccionLocal.sin_port = htons(puerto);
  bind(s, (struct sockaddr *)&direccionLocal,sizeof(direccionLocal)); 
}

int SocketDatagrama::recibe(PaqueteDatagrama & p)
{
	char datos[p.obtieneLongitud()]; 
	socklen_t len=sizeof(direccionForanea);
	int rc=recvfrom(s, (char *)datos , p.obtieneLongitud() * sizeof(char), 0, (struct sockaddr *)&direccionForanea, &len);  
  char cadena[16];
  p.inicializaPuerto(htons(direccionForanea.sin_port)); 
  memcpy(cadena,inet_ntoa(direccionForanea.sin_addr), 16);
  ip = (char *) malloc(sizeof(char) * 16);
  memcpy(ip, cadena, 16);
  p.inicializaIp(cadena);
  p.inicializaDatos(datos);
  cout<< "Ip:"<< cadena << " Puerto: " << p.obtienePuerto() <<endl;
  return rc;
}


int SocketDatagrama::envia(PaqueteDatagrama & p)
{ 
   	bzero((char *)&direccionForanea, sizeof(direccionForanea));
   	direccionForanea.sin_family = AF_INET;
    direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
    direccionForanea.sin_port = htons(p.obtienePuerto());
	 return sendto(s, (char *)p.obtieneDatos(), p.obtieneLongitud() * sizeof(char), 0, (struct sockaddr *) &direccionForanea, sizeof(direccionForanea));

}

int SocketDatagrama::getPuerto()
{
  return htons(direccionForanea.sin_port);
}

char* SocketDatagrama::getIP()
{
  return ip;
}


int SocketDatagrama::recibeTimeout(PaqueteDatagrama & p, time_t segundos, suseconds_t microsegundos)
{
  timeout.tv_sec = segundos;
  timeout.tv_usec = microsegundos;
  setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));

  char datos[p.obtieneLongitud()]; 
  socklen_t len=sizeof(direccionForanea);
  int rc=recvfrom(s, (char *)datos , p.obtieneLongitud() * sizeof(char), 0, (struct sockaddr *)&direccionForanea, &len);  
  
  if(rc < 0)
  {
    if (errno == EWOULDBLOCK)
    {
      fprintf(stderr, "Tiempo para recepción transcurrido\n");
      return -1;
    }
    else
    {
      fprintf(stderr, "Error en recvfrom\n");
      return -2;
    }
  }
  else
  {
    char cadena[16];
    p.inicializaPuerto(htons(direccionForanea.sin_port)); 
    memcpy(cadena,inet_ntoa(direccionForanea.sin_addr), 16);
    ip = (char *) malloc(sizeof(char) * 16);
    memcpy(ip, cadena, 16);
    p.inicializaIp(cadena);
    p.inicializaDatos(datos);
    cout<< "Ip:"<< cadena << " Puerto: " << p.obtienePuerto() <<endl;
  }

  return rc;
}

SocketDatagrama::~SocketDatagrama()
{
	
}