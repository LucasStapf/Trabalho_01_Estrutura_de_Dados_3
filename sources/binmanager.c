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
#include "../headers/registers.h"



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

  if(dr->removido == '1') { // logicamente removido
    // LONG_8 byteOffsetNextReg = dr->tamanhoRegistro - sizeof(dr->tamanhoRegistro) - sizeof(dr->removido);
    fseek(f, dr->tamanhoRegistro, SEEK_CUR);
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
  dr->nomeEstacao[i] = '\0'; // Substitui o '|' pelo '\0'
    
  i = 0;
  do { // Leitura do campo nomeLinha feita char a char

    fread(&dr->nomeLinha[i], sizeof(char), 1, f);
    if(dr->nomeLinha[i] == '|') break;
    else i++;

  } while (dr->nomeLinha[i] != '|');
  dr->nomeLinha[i] = '\0'; // Substitui o '|' pelo '\0'
  
	return NOT_REMOVED;
}



/**
  - Function: findDataRegistersBIN
  - Description: Esta funcao busca registros no arquivo de dados BIN com base nos campos nao vazios do DataRegister passado. Quando um registro eh encontrado, ele sera printado na tela.
  - Note: O arquivo ja deve estar aberto para a leitura no modo binario.
  - Parameters: 
    - f: FILE do arquivo binário de leitura
    - dr: Variavel que contem os campos de busca do registro
  - Returns: Retorna REGISTER_NOT_FOUND caso nao tenha encontrado o registro e
  REGISTER_FOUND caso contrario. 
*/
int findDataRegistersBIN(FILE *f, DataRegister *dr) {
	
  int found = REGISTER_NOT_FOUND;
  fseek(f, SEEK_FIRST_REGISTER, SEEK_SET); // Volta para primeiro registro do arquivo.
  
  DataRegister r;
  int ret;

  do {

    ret = readDataRegisterBIN(f, &r);
    if(ret == END_OF_FILE_BIN) break;
    
    if(ret == REMOVED) continue;
    else {
      
      if(compareRegister(*dr, r) == EQUIVALENT_REGISTERS) {
        found = REGISTER_FOUND;
        printRegister(r);
        printf("\n"); //////////////////////////////////////////
      }
    }

  } while (ret != END_OF_FILE_BIN);

  if(found == REGISTER_NOT_FOUND) printf("Registro inexistente."); // printar aqui msm?

  return found;
}



/**
  - Function: deleteDataRegisterBIN
  - Description: Esta funcao tenta removir um registro do arquivo binario com base nos campos nao vazios do DataRegister passado.
  - Note: O arquivo ja deve estar aberto para a leitura e escrita no modo binario.
  - Parameters: 
    - f: FILE do arquivo binário de leitura
    - dr: Variavel que contem os campos de busca do registro
  - Returns: ??????????????????????????????????????????????? 
*/
int deleteDataRegisterBIN(FILE *f, DataRegister *dr) {
  
  HeaderRegister hr;

  readHeaderRegisterBIN(f, &hr);
  hr.status = '0';
  writeHeaderRegisterBIN(f, &hr);

  fseek(f, SEEK_FIRST_REGISTER, SEEK_SET);

  // fwrite(&hr.status, sizeof(hr.status), 1, f);
  // fread(&hr.topoDaLista, sizeof(hr.topoDaLista), 1, f);
  // fread(&hr.nroEstacoes, sizeof(hr.nroEstacoes), 1, f);
  // fread(&hr.nroParesEstacao, sizeof(hr.nroParesEstacao), 1, f);

  DataRegister r;

  linkedlist nomesEstacoesRemovidas;
  createLinkedList(&nomesEstacoesRemovidas);
	
  linkedlist paresEstacoes;
	createLinkedList(&paresEstacoes);
	
	int ret;
  do {
		
    // LONG_8 byte = ftell(f);
    ret = readDataRegisterBIN(f, &r);
    if(ret == REMOVED) continue;
    else { // estacao nao removida
			
      if(compareRegister(*dr, r) == EQUIVALENT_REGISTERS) {
        
        addStringLinkedList(&nomesEstacoesRemovidas, r.nomeEstacao);
				
        fseek(f, -(r.tamanhoRegistro + sizeof(r.removido) + sizeof(r.tamanhoRegistro)), SEEK_CUR); // volta para o byteoffset do registro lido
			
        r.removido = '1';
        r.proxLista = hr.topoDaLista;
        hr.topoDaLista = ftell(f); // byte offset do registro removido

        writeDataRegisterBIN(f, &r);

      } else addParEstacoesLinkedList(&paresEstacoes, r.codEstacao,r.codProxEstacao);
    }
  } while (ret != END_OF_FILE_BIN);

  // fseek(f, SEEK_FIRST_REGISTER, SEEK_SET);

  // do {

  //   ret = readDataRegisterBIN(f, &r);
  //   if(ret == REMOVED) continue;
  //   else {

  //     if(hasIntegerElementLinkedList(&codigosEstacoesRemovidas, r.codProxEstacao) == TRUE) {
        
  //       r.codProxEstacao = NULL_FIELD_INTEGER;
  //       r.distProxEstacao = NULL_FIELD_INTEGER;
  //       fseek(f, -r.tamanhoRegistro, SEEK_CUR);
  //       writeDataRegisterBIN(f, &r);
  //       hr.nroParesEstacao--;
  //     }
  //   }

  // } while (ret != END_OF_FILE_BIN);

  hr.nroEstacoes -= nomesEstacoesRemovidas.size;
  hr.nroParesEstacao = paresEstacoes.size;
  hr.status = '1';

  writeHeaderRegisterBIN(f, &hr);

  // fseek(f, SEEK_TOPO_LISTA, SEEK_SET);
  // fwrite(&hr.topoDaLista, sizeof(hr.topoDaLista), 1, f);

  // fwrite(&hr.nroEstacoes, sizeof(hr.nroEstacoes), 1, f);

  // fwrite(&hr.nroParesEstacao, sizeof(hr.nroParesEstacao), 1, f);
  
	// hr.status = '1';
  // fseek(f, SEEK_STATUS, SEEK_SET);
  // fwrite(&hr.status, sizeof(hr.status), 1, f);

  deleteLinkedList(&nomesEstacoesRemovidas);
  deleteLinkedList(&paresEstacoes);

	// printHeaderBIN(f);
  
  return 1;
}


int insertDataRegisterBIN(FILE *f, DataRegister *dr) {
	
  HeaderRegister hr;
  readHeaderRegisterBIN(f, &hr);
  hr.status = '0';
  writeHeaderRegisterBIN(f, &hr);

  DataRegister r;
  LONG_8 nextByte = hr.topoDaLista;

  do {

    fseek(f, nextByte, SEEK_SET);
    readDataRegisterBIN(f, &r);

    if(r.tamanhoRegistro >= dr->tamanhoRegistro) {
      fseek(f, nextByte, SEEK_SET);
      writeDataRegisterBIN(f, dr);
			fillWithTrash(f, r.tamanhoRegistro - dr->tamanhoRegistro);
      hr.topoDaLista = r.proxLista;
    } else nextByte = r.proxLista;

  } while(nextByte != -1 && r.tamanhoRegistro < dr->tamanhoRegistro);

  if(nextByte == -1) {
    fseek(f, 0, SEEK_END);
    writeDataRegisterBIN(f, dr);
  }

  fseek(f, SEEK_FIRST_REGISTER, SEEK_SET);
  
	linkedlist nomesEstacoes;
  createLinkedList(&nomesEstacoes);

	linkedlist paresDistintosEstacoes; // Nao comutativo: (1,2) != (2,1)
	createLinkedList(&paresDistintosEstacoes);

  while(!feof(f)) {
    if(readDataRegisterBIN(f, &r) != REMOVED) {
      addStringLinkedList(&nomesEstacoes, r.nomeEstacao);
      addParEstacoesLinkedList(&paresDistintosEstacoes, r.codEstacao, r.codProxEstacao);
    }
	}
  
  hr.status = '1';
  hr.nroEstacoes = nomesEstacoes.size;
  hr.nroParesEstacao = paresDistintosEstacoes.size;  
  writeHeaderRegisterBIN(f, &hr);
  
  return 1;
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

  fseek(fout, SEEK_NRO_ESTACOES, SEEK_SET);
  hr.nroEstacoes = nomesEstacoes.size;
  fwrite(&hr.nroEstacoes, sizeof(hr.nroEstacoes), 1, fout);
	deleteLinkedList(&nomesEstacoes);

  hr.nroParesEstacao = paresDistintosEstacoes.size;
  fwrite(&hr.nroParesEstacao, sizeof(hr.nroParesEstacao), 1, fout);
	deleteLinkedList(&paresDistintosEstacoes);

  fseek(fout, SEEK_STATUS, SEEK_SET);
  hr.status = '1';
  fwrite(&hr.status, sizeof(hr.status), 1, fout);

  fclose(fin);
  fclose(fout);
}


/**
  - Function: printFileBIN
  - Description: Esta funcao printa todos os registro nao removidos do arquivo binario.
  - Parameters: 
    - binName: nome do arquivo binario  
*/
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

void fillWithTrash(FILE *f, int numBytes) {
  char trash = MEMORY_TRASH; 
	for(int i = 0; i < numBytes; i++) 
    fwrite(&trash, sizeof(char), 1, f);
}


// void printHeaderBIN(FILE *f) {
// 	fseek(f, SEEK_STATUS, SEEK_SET);
// 	HeaderRegister rc;
// 	fread(&rc.status, sizeof(rc.status), 1, f);
// 	fread(&rc.topoDaLista, sizeof(rc.topoDaLista), 1, f);
// 	fread(&rc.nroEstacoes, sizeof(rc.nroEstacoes), 1, f);
// 	fread(&rc.nroParesEstacao, sizeof(rc.nroParesEstacao), 1, f);
// 	printf("%c %lld %d %d\n", rc.status, rc.topoDaLista, rc.nroEstacoes, rc.nroParesEstacao);
// }

// .....
// aaaaaaaa 1 2 -> n add
// sdfsgsdg 3 4 -> add
// aaaaaaaa 1 2 -> n add