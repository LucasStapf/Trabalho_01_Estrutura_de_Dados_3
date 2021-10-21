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
#include "../headers/linkedlist.h"
#include "../headers/constants.h"
#include "../headers/commands.h"
#include "../headers/registers.h"
#include "../headers/display.h"

/**
  - Function: cmdSelector
  - Description: Funcao responsavel por ler e realizar um determinado comando passado no stdin.
*/
void cmdSelector() {

  char inputstr[MAX_SIZE_STR];
  char *str;

  fgets(inputstr, MAX_SIZE_STR, stdin);

  char filename[MAX_SIZE_STR], destinationfilename[MAX_SIZE_STR];
  int cmd;
  int number;

  if(inputstr[strlen(inputstr) - 1] == '\n') inputstr[strlen(inputstr) - 1] = '\0'; // Tira o '\n' se houver.

  str = strtok(inputstr, " ");
  cmd = atoi(str);
  str = strtok(NULL, " ");
  strncpy(filename, str, MAX_SIZE_STR);

  switch(cmd) {

  case create:
    str = strtok(NULL, " ");
    strncpy(destinationfilename, str, MAX_SIZE_STR);
    createTable(filename, destinationfilename);
    break;

  case selectData:
    selectDataTable(filename);
    break;

  case selectDataWhere:
    str = strtok(NULL, " ");
    number = atoi(str);
    selectDataWhereTable(filename, number);
    break;

  case deleteData:
    str = strtok(NULL, " ");
    number = atoi(str);
    deleteDataTable(filename, number);
    break;

  case insertData:
    str = strtok(NULL, " ");
    number = atoi(str);
    insertDataTable(filename, number);
    break;

  case updateData:
    str = strtok(NULL, " ");
    number = atoi(str);
    updateDataTable(filename, number);
    break;

  default:
    break;
  }
}

/**
  - Function: createTable
  - Description: Esta funcao simula o comando CREATE TABLE de um SQL.
  - Parameters:
    - inputfilename: Nome do arquivo csv de leitura dos dados.
    - outputfilename: Nome do arquivo binario a ser gerado.
*/
void createTable(char *inputfilename, char *outputfilename) {
  showMessage(createFileBIN(inputfilename, outputfilename));
  binarioNaTela(outputfilename);
}

/**
  - Function: selectDataTable
  - Description: Esta funcao simula o comando SELECT de um SQL.
  - Parameters:
    - inputfilename: Nome do arquivo binario para leitura dos dados.
*/
void selectDataTable(char *inputfilename) {
  showMessage(printFileBIN(inputfilename));
}

/**
  - Function: selectDataTable
  - Description: Esta funcao simula o comando SELECT WHERE de um SQL.
  - Parameters:
    - inputfilename: Nome do arquivo binario para leitura dos dados.
    - number: Numero de campos utilizados para realizar a busca.
*/
void selectDataWhereTable(char *inputfilename, int number) {

  char str[MAX_SIZE_STR], fieldName[MAX_SIZE_STR], fieldValue[MAX_SIZE_STR];

  DataRegister dr;
  setEmptyDataRegister(&dr);

  FILE *f = fopen(inputfilename, "rb");
  if(f == NULL) {
    showMessage(FILE_ERROR);
    return;
  }

  for(int i = 0; i < number; i++) {

    fgets(str, MAX_SIZE_STR, stdin);
    if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = '\0';

    char *p = strtok_custom(str, ' ');
    strcpy(fieldName, p);

    p = strtok_custom(NULL, ' ');
    strcpy(fieldValue, p);

    fillFieldDataRegister(&dr, fieldName, fieldValue);
  }

  showMessage(findDataRegistersBIN(f, &dr));
  fclose(f);
}

/**
  - Function: deleteDataTable
  - Description: Esta funcao simula o comando DELETE de um SQL.
  - Parameters:
    - inputfilename: Nome do arquivo binario para leitura dos dados.
    - number: Numero de delecoes que serao realizadas.
*/
void deleteDataTable(char *inputfilename, int number) {

  char str[MAX_SIZE_STR], fieldName[MAX_SIZE_STR], fieldValue[MAX_SIZE_STR];

  DataRegister dr;
  FILE *f = fopen(inputfilename, "rb+");
  if(f == NULL) {
    showMessage(FILE_ERROR);
    return;
  }

  for(int i = 0; i < number; i++) {

    setEmptyDataRegister(&dr);

    fgets(str, MAX_SIZE_STR, stdin);
    if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = '\0';

    int n; // numero de campos
    char *p = strtok_custom(str, ' ');
    n = atoi(p);

    for(int j = 0; j < n; j++) {
      
      p = strtok_custom(NULL, ' ');
      strcpy(fieldName, p);

      p = strtok_custom(NULL, ' ');
      strcpy(fieldValue, p);

      fillFieldDataRegister(&dr, fieldName, fieldValue);
    }

    deleteDataRegisterBIN(f, &dr);
  }

  fclose(f);

  binarioNaTela(inputfilename);
}

/**
  - Function: insertDataTable
  - Description: Esta funcao simula o comando INSERT INTO de um SQL.
  - Parameters:
    - inputfilename: Nome do arquivo binario para leitura dos dados.
    - number: Numero de insercoes que serao realizadas.
*/
void insertDataTable(char *inputfilename, int number) {

  FILE *f = fopen(inputfilename, "rb+");

  if(f == NULL) {
    showMessage(FILE_ERROR);
    return;
  }

  DataRegister dr;
  char str[MAX_SIZE_STR];
  char *p;

  for(int i = 0; i < number; i++) {

    fgets(str, MAX_SIZE_STR, stdin);
    if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = '\0';

    p = strtok_custom(str, ' '); // codEstacao
    fillFieldDataRegister(&dr, "codEstacao", p);

    p = strtok_custom(NULL, ' '); // nomeEstacao
    fillFieldDataRegister(&dr, "nomeEstacao", p);

    p = strtok_custom(NULL, ' '); // codLinha
    fillFieldDataRegister(&dr, "codLinha", p);

    p = strtok_custom(NULL, ' '); // nomeLinha
    fillFieldDataRegister(&dr, "nomeLinha", p);

    p = strtok_custom(NULL, ' '); // codProxEstacao
    fillFieldDataRegister(&dr, "codProxEstacao", p);

    p = strtok_custom(NULL, ' '); // distProxEstacao
    fillFieldDataRegister(&dr, "distProxEstacao", p);

    p = strtok_custom(NULL, ' '); // codLinhaIntegra
    fillFieldDataRegister(&dr, "codLinhaIntegra", p);

    p = strtok_custom(NULL, ' '); // codEstIntegra
    fillFieldDataRegister(&dr, "codEstIntegra", p);

    dr.removido = '0';
    dr.tamanhoRegistro = sizeOfRegister(dr);
    dr.proxLista = NULL_FIELD_INTEGER;

    insertDataRegisterBIN(f, &dr);
  }

  fclose(f);

  binarioNaTela(inputfilename);
}

/**
  - Function: updateDataTable
  - Description: Esta funcao simula o comando UPDATE de um SQL.
  - Parameters:
    - inputfilename: Nome do arquivo binario para leitura dos dados.
    - number: Numero de atualizacoes que serao realizadas.
*/
void updateDataTable(char *inputfilename, int number) {

  char str[MAX_SIZE_STR], fieldName[MAX_SIZE_STR], fieldValue[MAX_SIZE_STR];

  DataRegister dr_busca, dr_alteracao;
  FILE *f = fopen(inputfilename, "rb+");
  if (f == NULL) {
    showMessage(FILE_ERROR);
    return;
  }

  for(int i = 0; i < number; i++) {

    setEmptyDataRegister(&dr_busca);
    setEmptyDataRegister(&dr_alteracao);

    fgets(str, MAX_SIZE_STR, stdin);
    str[strlen(str) - 1] = '\0';

    int n; // numero de campos
    char *p = strtok_custom(str, ' ');
    n = atoi(p);

    for(int j = 0; j < n; j++) {
      
      p = strtok_custom(NULL, ' ');
      strcpy(fieldName, p);

      p = strtok_custom(NULL, ' ');
      strcpy(fieldValue, p);

      fillFieldDataRegister(&dr_busca, fieldName, fieldValue);
    }

    fgets(str, MAX_SIZE_STR, stdin);
    if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = '\0';

    p = strtok_custom(str, ' ');
    n = atoi(p);

    for (int j = 0; j < n; j++) {
      
      p = strtok_custom(NULL, ' ');
      strcpy(fieldName, p);

      p = strtok_custom(NULL, ' ');
      strcpy(fieldValue, p);

      fillFieldDataRegister(&dr_alteracao, fieldName, fieldValue);
    }

    updateDataRegisterBIN(f, &dr_busca, &dr_alteracao);
  }

  fclose(f);

  binarioNaTela(inputfilename);
}

/**
  - Function: binarioNaTela
  - Description: Funcao de comparacao no run.codes - Fornecida
  - Parameters:
    - nomeArquivoBinario: Nome do arquivo binario.
*/
void binarioNaTela(char *nomeArquivoBinario) {

  unsigned long i, cs;
  unsigned char *mb;
  size_t fl;
  FILE *fs;
  
  if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
    fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
    return;
  }

  fseek(fs, 0, SEEK_END);
  fl = ftell(fs);
  fseek(fs, 0, SEEK_SET);
  mb = (unsigned char *)malloc(fl);
  fread(mb, 1, fl, fs);

  cs = 0;
  for (i = 0; i < fl; i++) {
    cs += (unsigned long)mb[i];
  }
  
  printf("%lf\n", (cs / (double)100));
  free(mb);
  fclose(fs);
}

/**
  - Function: strtok_custom
  - Description: Esta funcao possui a mesma funcionalidade da funcao original stktok da string.h, porem 
  a string nao eh quebrada no delimitador se estiver entre aspas duplas, sendo quebrado o bloco inteiro
  de caracteres dentro das aspas.
  - Parameters:
    - inputfilename: Nome do arquivo binario para leitura dos dados.
    - number: Numero de delecoes que serao realizadas.
*/
char *strtok_custom(char *str, char delimitador) {

  static char *pi, *pf;

  if(str != NULL) pi = pf = str;
  else pi = pf;

  if(pi == NULL) return NULL;

  int i = 0;

  if(pf[i] == delimitador) {
    for (; pf[i] == delimitador; i++);
    pi = pf = &pf[i];
  }

  for(i = 0; pf[i] != delimitador && pf[i] != '"' && pf[i] != '\0'; i++);

  if(pf[i] == delimitador) {
    
    pf[i] = '\0';
    pf = &pf[i + 1];
    return pi;
  
  } else if(pf[i] == '"') {

    pi++;
    pf++;
    for (i = 0; pf[i] != '"'; i++);
    pf[i] = '\0';
    pf = &pf[i + 1];
    return pi;

  } else {

    if (i == 0) return NULL;
    else {
      pf = NULL;
      return pi;
    }
  }
}
