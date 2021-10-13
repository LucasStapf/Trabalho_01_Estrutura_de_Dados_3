/**
* Trabalho 01 - Estrutura de Dados III
*
* Integrantes do grupo:
* 
* Leonardo Hannas de Carvalho Santos  NUSP: 11800480
* Lucas Carvalho Freiberger Stapf     NUSP: 11800559
*/

#ifndef CSVMANAGER_H
#define CSVMANAGER_H

void jumpHeaderCSV(FILE *f);
void readFieldCSV(FILE *f, char *str);
void readLineCSV(FILE *f, DataRegister *dr);

#endif