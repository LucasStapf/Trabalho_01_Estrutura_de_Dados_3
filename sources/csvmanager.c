/**
 * Trabalho 01 - Estrutura de Dados III
 *
 * Integrantes do grupo:
 *
 * Leonadro Hannas de Carvalho Santos  NUSP: 11800480
 * Lucas Carvalho Freiberger Stapf     NUSP: 11800559
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/binmanager.h"
#include "../headers/constants.h"
#include "../headers/registers.h"



/**
 * @brief Esta funcao ignora o cabecalho de dados e posiciona a 
 * leitura do arquivo para a primeira linha de dados (se houver).
 * OBS: O arquivo ja deve estar aberto para a leitura.
 * 
 * @param f FILE do arquivo de leitura (arquivo ja deve estar aberto).
 * 
 * @author Leonadro Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
void jumpHeaderCSV(FILE *f) {
  char c = fgetc(f);
  while(c != '\n') c = fgetc(f);
}


/**
 * @brief Esta funcao realiza a leitura de um campo do arquivo de dados CSV 
 * a partir da posicao corrente de leitura do arquivo, salvando o dado como 
 * uma string. Campos NULOS (sem dados armazenados) possuem valor NULL_FIELD_STRING.
 * OBS: O arquivo ja deve estar aberto para a leitura.
 * 
 * @param f FILE do arquivo de leitura (arquivo ja deve estar aberto).
 * @param str Variavel onde sera salva a string lida.
 * 
 * @author Leonadro Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
void readFieldCSV(FILE *f, char *str) {

  char c;
  int i = 0;

  c = fgetc(f);

  if(c == ',' || c == '\r' || c == '\n' || feof(f)) {
    str[0] = '\0';
    if (c == '\r') c = fgetc(f); // ler o \n e ir para proxima linha.
    return;
  }

  while(c != ',' && c != '\r' && c != '\n') {
    if(feof(f)) return;
    str[i] = c;
    c = fgetc(f);
    i++;
  }

  str[i] = '\0';
  if (c == '\r') c = fgetc(f); // ler o \n e ir para proxima linha.
}

/**
 * @brief Esta funcao faz a leitura de uma linha inteira do arquivo CSV de entrada
 * (partindo da posicao corrente de leitura) e salva os dados ja convertidos em um 
 * DataRegister. Campos do tipo (int) ou (LONG_8) que sao NULOS sao salvos com o 
 * valor NULL_FIELD_INTEGER, enquanto que campos do tipo (char *) que sao NULOS sao
 * identificados como NULL_FIELD_STRING. 
 * OBS: O arquivo ja deve estar aberto para a leitura.
 * 
 * @param f FILE do arquivo de leitura (arquivo ja deve estar aberto).
 * @param dr DataRegister onde serao armazenados os dados lidos do arquivo.
 * 
 * @author Leonadro Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
void readLineCSV(FILE *f, DataRegister *dr) {

  char str[MAX_SIZE_STR];

  readFieldCSV(f, str);
  dr->codEstacao = atoi(str);

  readFieldCSV(f, str);
  strcpy(dr->nomeEstacao, str);

  readFieldCSV(f, str);
  dr->codLinha = atoi(str);
  if(dr->codLinha == 0) dr->codLinha = -1;

  readFieldCSV(f, str);
  strcpy(dr->nomeLinha, str);

  readFieldCSV(f, str);
  dr->codProxEstacao = atoi(str);
  if(dr->codProxEstacao == 0) dr->codProxEstacao = -1;

  readFieldCSV(f, str);
  dr->distProxEstacao = atoi(str);
  if(dr->distProxEstacao == 0) dr->distProxEstacao = -1;

  readFieldCSV(f, str);
  dr->codLinhaIntegra = atoi(str);
  if(dr->codLinhaIntegra == 0) dr->codLinhaIntegra = -1;

  readFieldCSV(f, str);
  dr->codEstIntegra = atoi(str);
  if(dr->codEstIntegra == 0) dr->codEstIntegra = -1;

  dr->removido = '0';
  dr->proxLista = -1;
  dr->tamanhoRegistro = sizeOfRegister(*dr);
}