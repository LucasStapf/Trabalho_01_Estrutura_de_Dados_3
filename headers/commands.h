/**
* Trabalho 01 - Estrutura de Dados III
*
* Integrantes do grupo:
* 
* Leonardo Hannas de Carvalho Santos  NUSP: 11800480
* Lucas Carvalho Freiberger Stapf     NUSP: 11800559
*/

#ifndef COMMANDS_H
#define COMMANDS_H

enum command {
  create = 1, selectData, selectDataWhere, deleteData, insertData, updateData
};

int cmdSelector();

int createTable(char *inputfilename, char *outputfilename);
int selectDataTable(char *inputfilename);
int selectDataWhereTable(char *inputfilename, int number);
int deleteDataTable(char *inputfilename, int number);
int insertDataTable(char *inputfilename, int number);
int updateDataTable(char *inputfilename, int number);

void binarioNaTela(char *nomeArquivoBinario);

char* strtok_custom(char* str, char delimitador);



#endif

