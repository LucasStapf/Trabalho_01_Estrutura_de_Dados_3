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

#include "registers.h"

void writeHeaderRegisterBIN(FILE *f, HeaderRegister *rc); // ok
void readHeaderRegisterBIN(FILE *f, HeaderRegister *rc); // ok

void writeDataRegisterBIN(FILE *f, DataRegister *dr); // ok
int readDataRegisterBIN(FILE *f, DataRegister *dr); // ok
int findDataRegistersBIN(FILE *f, DataRegister *dr); // ok
void deleteDataRegisterBIN(FILE *f, DataRegister *dr); // ok
int insertDataRegisterBIN(FILE *f, DataRegister *dr);
void updateDataRegisterBIN(FILE *f, DataRegister *dr_busca, DataRegister *dr_alteracao);

int createFileBIN(char *csvName, char *binName); // ok
int printFileBIN(char *binName); // ok

void fillWithTrash(FILE *f, int numBytes);
long findAvailableSpaceRegister(FILE *f, long topoDaPilha, long *byteAnterior, long *byteProximo, long numBytes);
void printHeaderBIN(FILE *f);

#endif