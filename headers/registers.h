/**
* Trabalho 01 - Estrutura de Dados III
*
* Integrantes do grupo:
* 
* Leonadro Hannas de Carvalho Santos  NUSP: 11800480
* Lucas Carvalho Freiberger Stapf     NUSP: 11800559
*/

#ifndef REGISTERS_H
#define REGISTERS_H

#include "constants.h"

typedef struct {
	
	char status;
	LONG_8 topoDaLista;
	int nroEstacoes;
	int nroParesEstacao;

} HeaderRegister;


typedef struct {
	
	char removido;
	int tamanhoRegistro;
	LONG_8 proxLista;
	int codEstacao;
	int codLinha;
	int codProxEstacao;
	int distProxEstacao;
	int codLinhaIntegra;
	int codEstIntegra;
	char nomeEstacao[MAX_SIZE_STR];
	char nomeLinha[MAX_SIZE_STR];

} DataRegister;

int sizeOfRegister(DataRegister dr); // ok
int compareRegister(DataRegister dr1, DataRegister dr2); // ok
void setEmptyDataRegister(DataRegister *dr); // ok
void fillFieldDataRegister(DataRegister *dr, char *field, char *value); // ok
void copyDataRegister(DataRegister *dr_destino, DataRegister *dr_origem);
void printRegister(DataRegister dr); // ok

#endif
