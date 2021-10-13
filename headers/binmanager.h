/**
* Trabalho 01 - Estrutura de Dados III
*
* Integrantes do grupo:
* 
* Leonadro Hannas de Carvalho Santos  NUSP: 11800480
* Lucas Carvalho Freiberger Stapf     NUSP: 11800559
*/

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "../headers/constants.h"

typedef struct {
	
	char status;
	long topoDaLista;
	int nroEstacoes;
	int nroParesEstacao;

} HeaderRegister;


typedef struct {
	
	char removido;
	int tamanhoRegistro;
	long proxLista;
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
void printRegister(DataRegister dr); // ok

void writeHeaderRegisterBIN(FILE *f, HeaderRegister *rc); // ok
void readHeaderRegisterBIN(FILE *f, HeaderRegister *rc); // ok

void writeDataRegisterBIN(FILE *f, DataRegister *dr); // ok
int readDataRegisterBIN(FILE *f, DataRegister *dr); // ok
int findRegistersBIN(FILE *f, DataRegister *dr); // ok

void createFileBIN(char *csvName, char *binName);
void printFileBIN(char *binName);

int deleteRegisterBIN(FILE *f, DataRegister *dr);

void printHeaderBIN(FILE *f);

#endif