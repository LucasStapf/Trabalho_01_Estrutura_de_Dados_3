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

/**
 * @brief Constantes para identificao dos comandos digitados.
 */
enum command {

  create = 1, 
  selectData, 
  selectDataWhere, 
  deleteData, 
  insertData, 
  updateData

};

void cmdSelector();

void createTable(char *inputfilename, char *outputfilename);
void selectDataTable(char *inputfilename);
void selectDataWhereTable(char *inputfilename, int number);
void deleteDataTable(char *inputfilename, int number);
void insertDataTable(char *inputfilename, int number);
void updateDataTable(char *inputfilename, int number);

void binarioNaTela(char *nomeArquivoBinario);

char* strtok_custom(char* str, char delimitador);
void eraseCRLF(char *str);

#endif

