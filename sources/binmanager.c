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
#include "../headers/csvmanager.h"
#include "../headers/linkedlist.h"
#include "../headers/constants.h"



/**
  - Function: sizeOfRegister
  - Description: Esta funcao calcula o tamanho de um registro de dados no arquivo binario.
  - Note: O tamanho retornado nao eh o real tamanho do DataRegister em si, uma vez que a funcao contabiliza a presenca do pipe '|' no fim das strings, mesmo que no DataRegister em si nao tenha o pipe.
  - Parameters: 
    - dr: struct DataRegister
  - Returns: retorna o tamanho do registro no arquivo binario 
*/
int sizeOfRegister(DataRegister dr) {
  
  int size = (1 + 2 + strlen(dr.nomeEstacao) + strlen(dr.nomeLinha)) * sizeof(char); // + 2: contabilizando o pipe '|'
  size += (7 * sizeof(int));
	size += sizeof(long);

  return size;
}



/**
  - Function: compareRegister
  - Description: Esta funcao compara dois registros e verifica se os mesmos sao equivalentes. Campos vazios sao desconsiderados na comparacao.
  - Parameters: 
    - dr1: registro 1
    - dr2: registro 2
  - Returns: Retorna DIFFERENT_REGISTERS caso os registros sejam nao-equivalentes, e EQUIVALENT_REGISTERS caso contrario.
*/
int compareRegister(DataRegister dr1, DataRegister dr2) {

  if(dr1.codEstacao != EMPTY_FIELD_INTEGER && dr2.codEstacao != EMPTY_FIELD_INTEGER
  && dr1.codEstacao != dr2.codEstacao) return DIFFERENT_REGISTERS;

  if(dr1.codLinha != EMPTY_FIELD_INTEGER && dr2.codLinha != EMPTY_FIELD_INTEGER
  && dr1.codLinha != dr2.codLinha) return DIFFERENT_REGISTERS;

  if(dr1.codProxEstacao != EMPTY_FIELD_INTEGER && dr2.codProxEstacao != EMPTY_FIELD_INTEGER
  && dr1.codProxEstacao != dr2.codProxEstacao) return DIFFERENT_REGISTERS;

  if(dr1.distProxEstacao != EMPTY_FIELD_INTEGER && dr2.distProxEstacao != EMPTY_FIELD_INTEGER
  && dr1.distProxEstacao != dr2.distProxEstacao) return DIFFERENT_REGISTERS;

  if(dr1.codLinhaIntegra != EMPTY_FIELD_INTEGER && dr2.codLinhaIntegra != EMPTY_FIELD_INTEGER
  && dr1.codLinhaIntegra != dr2.codLinhaIntegra) return DIFFERENT_REGISTERS;

  if(dr1.codEstIntegra != EMPTY_FIELD_INTEGER && dr2.codEstIntegra != EMPTY_FIELD_INTEGER
  && dr1.codEstIntegra != dr2.codEstIntegra) return DIFFERENT_REGISTERS;

  if(dr1.codEstacao != EMPTY_FIELD_INTEGER && dr2.codEstacao != EMPTY_FIELD_INTEGER
  && dr1.codEstacao != dr2.codEstacao) return DIFFERENT_REGISTERS;

  if(dr1.nomeEstacao[0] != EMPTY_FIELD_STRING && dr2.nomeEstacao[0] != EMPTY_FIELD_STRING
  && strcmp(dr1.nomeEstacao, dr2.nomeEstacao) != 0) return DIFFERENT_REGISTERS;

  if(dr1.nomeLinha[0] != EMPTY_FIELD_STRING && dr2.nomeLinha[0] != EMPTY_FIELD_STRING
  && strcmp(dr1.nomeLinha, dr2.nomeLinha) != 0) return DIFFERENT_REGISTERS;
  
  return EQUIVALENT_REGISTERS;
}



/**
  - Function: printRegister
  - Description: Esta funcao imprime um registro na tela, com os campos sendo exibidos na seguinte ordem:
  - codEstacao | nomeEstacao | codLinha | nomeLinha | codProxEstacao | distProxEstacao | codLinhaIntegra | codEstIntegra
  - Note: Campos NULOS (NULL_FIELD_INTEGER ou NULL_FIELD_STRING) serao exibidos como 'NULO'
  - Parameters: 
    - dr: registro a ser exibido
*/
void printRegister(DataRegister dr) {

  printf("%d ", dr.codEstacao); //
  printf("%s ", dr.nomeEstacao); //

	(dr.codLinha != NULL_FIELD_INTEGER) ? printf("%d ", dr.codLinha) : printf("NULO ");
	(strlen(dr.nomeLinha) != 0) ? printf("%s ", dr.nomeLinha) : printf("NULO ");
	(dr.codProxEstacao != NULL_FIELD_INTEGER) ? printf("%d ", dr.codProxEstacao) : printf("NULO ");
	(dr.distProxEstacao != NULL_FIELD_INTEGER) ? printf("%d ", dr.distProxEstacao) : printf("NULO ");	
	(dr.codLinhaIntegra != NULL_FIELD_INTEGER) ? printf("%d ", dr.codLinhaIntegra) : printf("NULO ");
	(dr.codEstIntegra != NULL_FIELD_INTEGER) ? printf("%d", dr.codEstIntegra) : printf("NULO");
}



/**
  - Function: writeHeaderRegisterBIN
  - Description: Esta funcao escreve o registro de cabecalho no inicio do arquivo binario a partir de um HeaderRegister.
  - Note: O arquivo ja deve estar aberto para a escrita no modo binario. O campo status eh atualizado por ultimo.
  - Parameters: 
    - f: arquivo onde serao salvos os dados
    - hr: registro que tera os dados salvos no arquivo  
*/
void writeHeaderRegisterBIN(FILE *f, HeaderRegister *hr) {

  fseek(f, SEEK_TOPO_LISTA, SEEK_SET);
  fwrite(&hr->topoDaLista, sizeof(hr->topoDaLista), 1, f);
  fwrite(&hr->nroEstacoes, sizeof(hr->nroEstacoes), 1, f);
  fwrite(&hr->nroParesEstacao, sizeof(hr->nroParesEstacao), 1, f);
  fseek(f, SEEK_STATUS, SEEK_SET);
  fwrite(&hr->status, sizeof(hr->status), 1, f);
}



/**
  - Function: readHeaderRegisterBIN
  - Description: Esta funcao le o registro de cabecalho no inicio do arquivo binario e salva os dados em um HeaderRegister.
  - Note: O arquivo ja deve estar aberto para a leitura no modo binario.
  - Parameters: 
    - f: arquivo onde serao salvos os dados
    - dr: registro que tera os dados lidos do arquivo  
*/
void readHeaderRegisterBIN(FILE *f, HeaderRegister *hr) {

  fseek(f, SEEK_STATUS, SEEK_SET);

  fread(&hr->status, sizeof(hr->status), 1, f);
  fread(&hr->topoDaLista, sizeof(hr->topoDaLista), 1, f);
  fread(&hr->nroEstacoes, sizeof(hr->nroEstacoes), 1, f);
  fread(&hr->nroParesEstacao, sizeof(hr->nroParesEstacao), 1, f);
}



/**
  - Function: writeDataRegisterBIN
  - Description: Esta funcao escreve os dados referente a um DataRegister em um arquivo binario. O processo ocorre na posicao corrente de escrita do arquivo.
  - Note: O arquivo ja deve estar aberto para a escrita no modo binario.
  - Parameters: 
    - f: arquivo onde serao salvos os dados
    - dr: registro que tera os dados salvos no arquivo  
*/
void writeDataRegisterBIN(FILE* f, DataRegister *dr) {

  char pipe = NULL_FIELD_STRING;
  
	fwrite(&dr->removido, sizeof(dr->removido), 1, f);
	fwrite(&dr->tamanhoRegistro, sizeof(dr->tamanhoRegistro), 1, f);
	fwrite(&dr->proxLista, sizeof(dr->proxLista), 1, f);
	fwrite(&dr->codEstacao, sizeof(dr->codEstacao), 1, f);
	fwrite(&dr->codLinha, sizeof(dr->codLinha), 1, f);
	fwrite(&dr->codProxEstacao, sizeof(dr->codProxEstacao), 1, f);
	fwrite(&dr->distProxEstacao, sizeof(dr->distProxEstacao), 1, f);
	fwrite(&dr->codLinhaIntegra, sizeof(dr->codLinhaIntegra), 1, f);
	fwrite(&dr->codEstIntegra, sizeof(dr->codEstIntegra), 1, f);
	
  fwrite(dr->nomeEstacao, sizeof(char), strlen(dr->nomeEstacao), f);
  fwrite(&pipe, sizeof(char), 1, f); // adicao do pipe no fim da string
	fwrite(dr->nomeLinha, sizeof(char), strlen(dr->nomeLinha), f);
  fwrite(&pipe, sizeof(char), 1, f); // adicao do pipe no fim da string
}



/**
  - Function: readDataRegisterBIN
  - Description: Esta função realiza a leitura de 1 registro do arquivo binario a partir da posicao corrente de leitura do arquivo.
  - Note: O arquivo ja deve estar aberto para a leitura no modo binario.
  - Parameters: 
    - f: FILE do arquivo binário de leitura
    - dr: Variável onde serao salvos os dados do registro (se este nao estiver removido)
  - Returns: Retorna END_OF_FILE_BIN caso o final do arquivo seja alcancado, REMOVED caso o registro lido esteja logicamente removido ou NOT_REMOVED caso tenha ocorrido uma leitura com sucesso.
*/
int readDataRegisterBIN(FILE *f, DataRegister *dr) {

  int ret = fread(&dr->removido, sizeof(dr->removido), 1, f);
	if (ret == 0) return END_OF_FILE_BIN;
	
	fread(&dr->tamanhoRegistro, sizeof(dr->tamanhoRegistro), 1, f);

  if(dr->removido == '1') {
    long byteOffsetNextReg = dr->tamanhoRegistro - sizeof(dr->tamanhoRegistro) - sizeof(dr->removido);
    fseek(f, byteOffsetNextReg, SEEK_CUR);
    return REMOVED;
  }
  
	fread(&dr->proxLista, sizeof(dr->proxLista), 1, f);
	fread(&dr->codEstacao, sizeof(dr->codEstacao), 1, f);
	fread(&dr->codLinha, sizeof(dr->codLinha), 1, f);
	fread(&dr->codProxEstacao, sizeof(dr->codProxEstacao), 1, f);
	fread(&dr->distProxEstacao, sizeof(dr->distProxEstacao), 1, f);
	fread(&dr->codLinhaIntegra, sizeof(dr->codLinhaIntegra), 1, f);
	fread(&dr->codEstIntegra, sizeof(dr->codEstIntegra), 1, f);

  int i = 0;

  do { // Leitura do campo nomeEstacao feita char a char

    fread(&dr->nomeEstacao[i], sizeof(char), 1, f);
    if(dr->nomeEstacao[i] == '|') break;
    else i++;

  } while (dr->nomeEstacao[i] != '|');

  dr->nomeEstacao[i] = '\0';
    
  i = 0;

  do { // Leitura do campo nomeLinha feita char a char

    fread(&dr->nomeLinha[i], sizeof(char), 1, f);
    if(dr->nomeLinha[i] == '|') break;
    else i++;

  } while (dr->nomeLinha[i] != '|');

  dr->nomeLinha[i] = '\0';
  
	return NOT_REMOVED;
}



/**
  - Function: findRegisterBIN
  - Description: Esta funcao busca registros no arquivo de dados BIN com base nos campos nao vazios do DataRegister passado.
  - Note: O arquivo ja deve estar aberto para a leitura no modo binario.
  - Parameters: 
    - f: FILE do arquivo binário de leitura
    - dr: Variavel que contem os campos de busca do registro
  -Returns: Retorna REGISTER_NOT_FOUND caso nao tenha encontrado o registro e
  REGISTER_FOUND caso contrario. 
*/
int findRegistersBIN(FILE *f, DataRegister *dr) {
	
  int found = REGISTER_NOT_FOUND;
  fseek(f, SEEK_FIRST_REGISTER, SEEK_SET); // Volta para primeiro registro do arquivo.
  
  DataRegister r;
  int ret;

  do {

    ret = readDataRegisterBIN(f, &r);
    if(ret == REMOVED) continue;
    else {
      
      if(compareRegister(*dr, r) == EQUIVALENT_REGISTERS) {
        found = REGISTER_FOUND;
        printRegister(r);
        printf("\n"); //////////////////////////////////////////
      }
    }

  } while (ret != END_OF_FILE_BIN);

  if(found == REGISTER_NOT_FOUND) printf("Registro inexistente.");

  return found;
}



/**
  - Function: createFileBIN
  - Description: Esta funcao cria  do zero um arquivo de dados binario a partir de um arquivo CSV.
  - Parameters: 
    - csvName: nome do arquivo csv
    - binName: nome do arquivo binario  
*/
void createFileBIN(char *csvName, char *binName) {

	FILE *fin = fopen(csvName, "r");
	if (fin == NULL) return;

	FILE *fout = fopen(binName, "wb");
	if (fout == NULL) {
    fclose(fin);
    return;
  }

	HeaderRegister hr;
  hr.status = '0';
  fwrite(&hr.status, sizeof(hr.status), 1, fout);
  hr.topoDaLista = -1;
  fwrite(&hr.topoDaLista, sizeof(hr.topoDaLista), 1, fout);
  hr.nroEstacoes = 0; // arrumar
  fwrite(&hr.nroEstacoes, sizeof(hr.nroEstacoes), 1, fout);
  hr.nroParesEstacao = 0; // arrumar
  fwrite(&hr.nroParesEstacao, sizeof(hr.nroParesEstacao), 1, fout);

  jumpHeaderCSV(fin);
  
  DataRegister dr;

  linkedlist nomesEstacoes;
  createLinkedList(&nomesEstacoes);

	linkedlist paresDistintosEstacoes; // Nao comutativo: (1,2) != (2,1)
	createLinkedList(&paresDistintosEstacoes);

  while(!feof(fin)) {
    readLineCSV(fin, &dr);
		addStringLinkedList(&nomesEstacoes, dr.nomeEstacao);
    addParEstacoesLinkedList(&paresDistintosEstacoes, dr.codEstacao, dr.codProxEstacao);
    writeDataRegisterBIN(fout, &dr);
	}

  // printStringLinkedList(nomesEstacoes);

  fseek(fout, SEEK_NRO_ESTACOES, SEEK_SET);
  hr.nroEstacoes = nomesEstacoes.size;
  fwrite(&hr.nroEstacoes, sizeof(int), 1, fout);
	deleteLinkedList(&nomesEstacoes);

  hr.nroParesEstacao = paresDistintosEstacoes.size;
  fwrite(&hr.nroParesEstacao, sizeof(int), 1, fout);
	deleteLinkedList(&paresDistintosEstacoes);

  fseek(fout, SEEK_STATUS, SEEK_SET);
  hr.status = '1';
  fwrite(&hr.status, sizeof(char), 1, fout);

  fclose(fin);
  fclose(fout);
}

// msg de erro
// no lugar do | printar NULO
void printFileBIN(char *binName) {
  
  FILE *f = fopen(binName, "rb");
  if(f == NULL) return;

  DataRegister dr;
	HeaderRegister rc;
  fseek(f, SEEK_FIRST_REGISTER, SEEK_SET);

	int ret;
  
  while(!feof(f)) {

    ret = readDataRegisterBIN(f, &dr);

    if(ret == END_OF_FILE_BIN) break;
    else if (ret == NOT_REMOVED) printRegister(dr);
    else continue;

    printf("\n");
  }

	fclose(f);
} 


int deleteRegisterBIN(FILE *f, DataRegister *dr) {
  
  fseek(f, SEEK_STATUS, SEEK_SET);

  HeaderRegister rc;
  rc.status = '0';

  fwrite(&rc.status, sizeof(rc.status), 1, f);
  fread(&rc.topoDaLista, sizeof(rc.topoDaLista), 1, f);
  fread(&rc.nroEstacoes, sizeof(rc.nroEstacoes), 1, f);
  fread(&rc.nroParesEstacao, sizeof(rc.nroParesEstacao), 1, f);

  DataRegister r;
  
  int ret;

  linkedlist nomesEstacoesRemovidas;
  createLinkedList(&nomesEstacoesRemovidas);
	
  linkedlist codigosEstacoesRemovidas;
  createLinkedList(&codigosEstacoesRemovidas);

  do {

    ret = readDataRegisterBIN(f, &r);
    if(ret == REMOVED) continue;
    else {
			
      if(compareRegister(*dr, r) == EQUIVALENT_REGISTERS) {
        
        addStringLinkedList(&nomesEstacoesRemovidas, r.nomeEstacao);
        
        int *codEstacao = malloc(sizeof(int));
				if (codEstacao == NULL) return 1;
				
				*codEstacao = r.codEstacao;
        addElementLinkedList(&codigosEstacoesRemovidas, codEstacao);

        fseek(f, - r.tamanhoRegistro, SEEK_CUR); // volta para o byteoffset do registro lido
			
        r.removido = '1';
        r.proxLista = rc.topoDaLista;
        rc.topoDaLista = ftell(f); // byte offset do registro removido

        writeDataRegisterBIN(f, &r);
        
        if(r.codProxEstacao != -1) rc.nroParesEstacao--;
      }

    }
  } while (ret != END_OF_FILE_BIN);

  fseek(f, SEEK_FIRST_REGISTER, SEEK_SET);

  do {

    ret = readDataRegisterBIN(f, &r);
    if(ret == REMOVED) continue;
    else {

      if(hasIntegerElementLinkedList(&codigosEstacoesRemovidas, r.codProxEstacao) == TRUE) {
        
        r.codProxEstacao = NULL_FIELD_INTEGER;
        r.distProxEstacao = NULL_FIELD_INTEGER;
        fseek(f, -r.tamanhoRegistro, SEEK_CUR);
        writeDataRegisterBIN(f, &r);
        rc.nroParesEstacao--;
      }
    }

  } while (ret != END_OF_FILE_BIN);

  fseek(f, SEEK_TOPO_LISTA, SEEK_SET);
  fwrite(&rc.topoDaLista, sizeof(rc.topoDaLista), 1, f);

  rc.nroEstacoes -= nomesEstacoesRemovidas.size;
  fwrite(&rc.nroEstacoes, sizeof(rc.nroEstacoes), 1, f);

  fwrite(&rc.nroParesEstacao, sizeof(rc.nroParesEstacao), 1, f);
  
	rc.status = '1';
  fseek(f, SEEK_STATUS, SEEK_SET);
  fwrite(&rc.status, sizeof(rc.status), 1, f);

  deleteLinkedList(&nomesEstacoesRemovidas);
  deleteLinkedList(&codigosEstacoesRemovidas);

	printHeaderBIN(f);
  
  return 1;
}

void printHeaderBIN(FILE *f) {
	fseek(f, SEEK_STATUS, SEEK_SET);
	HeaderRegister rc;
	fread(&rc.status, sizeof(rc.status), 1, f);
	fread(&rc.topoDaLista, sizeof(rc.topoDaLista), 1, f);
	fread(&rc.nroEstacoes, sizeof(rc.nroEstacoes), 1, f);
	fread(&rc.nroParesEstacao, sizeof(rc.nroParesEstacao), 1, f);
	printf("%c %ld %d %d\n", rc.status, rc.topoDaLista, rc.nroEstacoes, rc.nroParesEstacao);
}