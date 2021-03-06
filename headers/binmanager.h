/**
* Trabalho 01 - Estrutura de Dados III
*
* Integrantes do grupo:
* 
* Leonardo Hannas de Carvalho Santos  NUSP: 11800480
* Lucas Carvalho Freiberger Stapf     NUSP: 11800559
*/

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "registers.h"

void writeHeaderRegisterBIN(FILE *f, HeaderRegister *rc);
void readHeaderRegisterBIN(FILE *f, HeaderRegister *rc);

void writeDataRegisterBIN(FILE *f, DataRegister *dr);
int readDataRegisterBIN(FILE *f, DataRegister *dr);
int findDataRegistersBIN(FILE *f, DataRegister *dr);
int deleteDataRegisterBIN(FILE *f, DataRegister *dr);
int insertDataRegisterBIN(FILE *f, DataRegister *dr);
int updateDataRegisterBIN(FILE *f, DataRegister *dr_busca, DataRegister *dr_alteracao);

int createFileBIN(char *csvName, char *binName);
int printFileBIN(char *binName); 
int statusFileBIN(HeaderRegister hr);

void fillWithTrash(FILE *f, int numBytes);
long findAvailableSpaceRegister(FILE *f, LONG_8 topoDaLista, LONG_8 *byteAnterior, LONG_8 *byteProximo, long numBytes);
void updateRemovedRegisterListBIN(FILE *f, LONG_8 byteAtual, LONG_8 byteProximo);

#endif