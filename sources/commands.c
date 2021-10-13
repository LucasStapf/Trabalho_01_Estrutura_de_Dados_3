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

int cmdSelector() {

  char inputstr[MAX_SIZE_STR];
  char *str;

  fgets(inputstr, MAX_SIZE_STR, stdin);

  char filename[MAX_SIZE_STR], destinationfilename[MAX_SIZE_STR];
  int cmd;
  int number;

  inputstr[strlen(inputstr) - 1] = '\0'; 

  str = strtok(inputstr, " ");
  cmd = atoi(str);
  str = strtok(NULL, " ");
  strncpy(filename, str, MAX_SIZE_STR);

  switch (cmd) {

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
      return 0;
      break;
  }

  return 1;
}

int createTable(char *inputfilename, char *outputfilename) {
  createFileBIN(inputfilename, outputfilename);
  binarioNaTela(outputfilename);
  return 0;
}

int selectDataTable(char *inputfilename) {
  printFileBIN(inputfilename);
  binarioNaTela(inputfilename);
  return 0;
}

void fillDataRegister(DataRegister *dr, char *field, char *value) {

  if(strcmp("codEstacao", field) == 0) dr->codEstacao = atoi(value);
  else if(strcmp("codLinha", field) == 0) dr->codLinha = atoi(value);
  else if(strcmp("codProxEstacao", field) == 0) dr->codProxEstacao = atoi(value);
	else if(strcmp("distProxEstacao", field) == 0) dr->distProxEstacao = atoi(value);
	else if(strcmp("codLinhaIntegra", field) == 0) dr->codLinhaIntegra = atoi(value);
	else if(strcmp("codEstIntegra", field) == 0) dr->codEstIntegra = atoi(value);
	else if(strcmp("nomeEstacao", field) == 0) strcpy(dr->nomeEstacao, value);
	else if(strcmp("nomeLinha", field) == 0) strcpy(dr->nomeLinha, value);
}


int selectDataWhereTable(char *inputfilename, int number) {

  char str[MAX_SIZE_STR], fieldName[MAX_SIZE_STR], fieldValue[MAX_SIZE_STR];

  DataRegister dr;
	FILE *f = fopen(inputfilename, "rb");
	if (f == NULL) return 1;
  
  for(int i = 0; i < number; i++) {
    
    dr.codEstacao = EMPTY_FIELD_INTEGER;
    dr.codLinha = EMPTY_FIELD_INTEGER;
    dr.codProxEstacao = EMPTY_FIELD_INTEGER;
    dr.distProxEstacao = EMPTY_FIELD_INTEGER;
    dr.codLinhaIntegra = EMPTY_FIELD_INTEGER;
    dr.codEstIntegra = EMPTY_FIELD_INTEGER;
    dr.nomeEstacao[0] = EMPTY_FIELD_STRING;
    dr.nomeLinha[0] = EMPTY_FIELD_STRING;

    fgets(str, MAX_SIZE_STR, stdin);
    str[strlen(str) - 1] = '\0';

    char *p = strtok_custom(str, ' ');
    strcpy(fieldName, p);

    p = strtok_custom(NULL, ' ');
    strcpy(fieldValue, p);

    fillDataRegister(&dr, fieldName, fieldValue);
    findRegistersBIN(f, &dr);
  }

  fclose(f);

  binarioNaTela(inputfilename);
  return 0;
}

int deleteDataTable(char *inputfilename, int number) {
  
  char str[MAX_SIZE_STR], fieldName[MAX_SIZE_STR], fieldValue[MAX_SIZE_STR];

  DataRegister dr;
	FILE *f = fopen(inputfilename, "rb+");
	if (f == NULL) return 1;
  
  for(int i = 0; i < number; i++) {
    
    dr.codEstacao = EMPTY_FIELD_INTEGER;
    dr.codLinha = EMPTY_FIELD_INTEGER;
    dr.codProxEstacao = EMPTY_FIELD_INTEGER;
    dr.distProxEstacao = EMPTY_FIELD_INTEGER;
    dr.codLinhaIntegra = EMPTY_FIELD_INTEGER;
    dr.codEstIntegra = EMPTY_FIELD_INTEGER;
    dr.nomeEstacao[0] = EMPTY_FIELD_STRING;
    dr.nomeLinha[0] = EMPTY_FIELD_STRING;

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

      fillDataRegister(&dr, fieldName, fieldValue);
    }
    
    deleteRegisterBIN(f, &dr);
  }

  fclose(f);

  binarioNaTela(inputfilename);
  return 0;
}

int insertDataTable(char *inputfilename, int number) {
  printf("insert %s %d\n", inputfilename, number);
  binarioNaTela(inputfilename);
  return 0;
}

int updateDataTable(char *inputfilename, int number) {
  printf("update %s %d\n", inputfilename, number);
  binarioNaTela(inputfilename);
  return 0;
}


void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai pedrer pontos por isso se usar ela). */

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
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}

char* strtok_custom(char* str, char delimitador) {

  static char *pi, *pf;

	if (str != NULL) pi = pf = str;
  else pi = pf;

  if(pi == NULL) return NULL;

	int i = 0;

  if(pf[i] == delimitador) {
    for(; pf[i] == delimitador; i++);
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
    for(i = 0; pf[i] != '"'; i++);
    pf[i] = '\0';
    
    pf = &pf[i + 1];
    return pi;

  } else {

    if(i == 0) return NULL;
    else {
      pf = NULL;
      return pi;
    }
  }
}


