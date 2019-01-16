#ifndef INTERFAZCLIENTE_H
#define INTERFAZCLIENTE_H

void getNodoInicial(char* puzz);
void getNodoFinal(char* puzz);
char validacionPuzzle(char * entrada, char *puzz);
void imprimirNodo(char* nodo);
char verificarTipoNodo(char * nodo);
void inicializarPack( char tipoNodoIni, char* nodoFinal, char * pack );

void expIzquierda(char *puzzle);
void expDerecha(char* puzzle);
void expArriba(char* puzzle);
void expAbajo(char* puzzle);

void expIzquierda(char *puzzle, char pnv);
void expDerecha(char* puzzle, char pnv);
void expArriba(char* puzzle, char pnv);
void expAbajo(char* puzzle, char pnv);

int posicionNodoVacio(char* puzzle);

#endif