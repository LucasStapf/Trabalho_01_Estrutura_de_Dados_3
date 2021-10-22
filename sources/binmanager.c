/**
 * Trabalho 01 - Estrutura de Dados III
 *
 * Integrantes do grupo:
 *
 * Leonardo Hannas de Carvalho Santos  NUSP: 11800480
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
 * @brief Esta funcao escreve o registro de cabecalho no inicio do arquivo 
 * binario a partir de um HeaderRegister. 
 * OBS: O arquivo ja deve estar aberto para a escrita no modo binario.
 * O campo status eh atualizado por ultimo.
 * 
 * @param f Arquivo onde sera escrito o cabecalho.
 * @param hr Registro do cabecalho a ser escrito no arquivo.
 * 
 * @author Leonardo Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
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
 * @brief Esta funcao le o registro de cabecalho no inicio do arquivo binario e salva
 * os dados em um HeaderRegister.
 * OBS: O arquivo ja deve estar aberto para a leitura no modo binario.
 * 
 * @param f Arquivo onde serao salvos os dados.
 * @param hr Registro que tera os dados lidos do arquivo.
 *
 * @author Leonardo Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
void readHeaderRegisterBIN(FILE *f, HeaderRegister *hr) {

  fseek(f, SEEK_STATUS, SEEK_SET);

  fread(&hr->status, sizeof(hr->status), 1, f);
  fread(&hr->topoDaLista, sizeof(hr->topoDaLista), 1, f);
  fread(&hr->nroEstacoes, sizeof(hr->nroEstacoes), 1, f);
  fread(&hr->nroParesEstacao, sizeof(hr->nroParesEstacao), 1, f);
}

/**
 * @brief Esta funcao escreve os dados referente a um DataRegister em um arquivo binario. 
 * O processo ocorre na posicao corrente de escrita do arquivo.
 * OBS: O arquivo ja deve estar aberto para a escrita no modo binario.
 * 
 * @param f Arquivo onde serao salvos os dados.
 * @param dr Registro que tera os dados salvos no arquivo.
 *
 * @author Leonardo Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
void writeDataRegisterBIN(FILE *f, DataRegister *dr) {

  char fd = FIELD_DELIMITER;

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
  fwrite(&fd, sizeof(char), 1, f); // adicao do pipe no fim da string
  fwrite(dr->nomeLinha, sizeof(char), strlen(dr->nomeLinha), f);
  fwrite(&fd, sizeof(char), 1, f); // adicao do pipe no fim da string
}

/**
 * @brief Esta função realiza a leitura de 1 registro do arquivo binario a partir da
 * posicao corrente de leitura do arquivo.
 * OBS: O arquivo ja deve estar aberto para leitura no modo binario.
 * 
 * @param f FILE do arquivo binario de leitura.
 * @param dr Variável onde serao salvos os dados do registro (se este nao estiver removido).
 * @return END_OF_FILE_BIN caso o final do arquivo seja alcancado, REMOVED caso o registro 
 * lido esteja logicamente removido ou NOT_REMOVED caso tenha ocorrido uma leitura com sucesso.
 *
 * @author Leonardo Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
int readDataRegisterBIN(FILE *f, DataRegister *dr) {

  int ret = fread(&dr->removido, sizeof(dr->removido), 1, f);
  if (ret == 0) return END_OF_FILE_BIN;

  fread(&dr->tamanhoRegistro, sizeof(dr->tamanhoRegistro), 1, f);

  LONG_8 pi = ftell(f);
  LONG_8 pf;

  fread(&dr->proxLista, sizeof(dr->proxLista), 1, f);

  if(dr->removido == '1') { // logicamente removido
    fseek(f, dr->tamanhoRegistro - sizeof(dr->proxLista), SEEK_CUR);
    return REMOVED;
  }

  fread(&dr->codEstacao, sizeof(dr->codEstacao), 1, f);
  fread(&dr->codLinha, sizeof(dr->codLinha), 1, f);
  fread(&dr->codProxEstacao, sizeof(dr->codProxEstacao), 1, f);
  fread(&dr->distProxEstacao, sizeof(dr->distProxEstacao), 1, f);
  fread(&dr->codLinhaIntegra, sizeof(dr->codLinhaIntegra), 1, f);
  fread(&dr->codEstIntegra, sizeof(dr->codEstIntegra), 1, f);

  int i = 0;
  do { // Leitura do campo nomeEstacao feita char a char

    fread(&dr->nomeEstacao[i], sizeof(char), 1, f);

    if (dr->nomeEstacao[i] == FIELD_DELIMITER) break;
    else i++;

  } while (dr->nomeEstacao[i] != FIELD_DELIMITER);
  dr->nomeEstacao[i] = '\0'; // Substitui o FIELD_DELIMITER pelo '\0'

  i = 0;
  do { // Leitura do campo nomeLinha feita char a char

    fread(&dr->nomeLinha[i], sizeof(char), 1, f);

    if (dr->nomeLinha[i] == FIELD_DELIMITER) break;
    else i++;

  } while (dr->nomeLinha[i] != FIELD_DELIMITER);
  dr->nomeLinha[i] = '\0'; // Substitui o FIELD_DELIMITER pelo '\0'

  pf = ftell(f);
  LONG_8 bytesLidos = pf - pi;

  char c;
  while (dr->tamanhoRegistro > bytesLidos) { // pular o lixo de memoria.
    fread(&c, sizeof(char), 1, f);
    bytesLidos++;
  } 

  return NOT_REMOVED;
}

/**
 * @brief Esta funcao busca registros no arquivo de dados BIN com base nos campos nao vazios
 * do DataRegister passado. Quando um registro eh encontrado, ele sera printado na tela.
 * OBS: O arquivo ja deve estar aberto para a leitura no modo binario.
 * 
 * @param f FILE do arquivo binario de leitura.
 * @param dr Variavel que contem os campos de busca do registro.
 * @return REGISTER_NOT_FOUND caso nao tenha encontrado o registro ou REGISTER_FOUND caso o 
 * registro tenha sido encontrado. 
 *
 * @author Leonardo Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
int findDataRegistersBIN(FILE *f, DataRegister *dr) {

  int found = REGISTER_NOT_FOUND;
  fseek(f, SEEK_FIRST_REGISTER, SEEK_SET); // Volta para primeiro registro do arquivo.

  DataRegister r;
  int ret;

  do {
    ret = readDataRegisterBIN(f, &r);
    
    if (ret == END_OF_FILE_BIN) break;
    if (ret == REMOVED) continue;
    else {

      if (compareRegister(*dr, r) == EQUIVALENT_REGISTERS) {
        found = REGISTER_FOUND;
        printRegister(r);
        printf("\n");
      }
    }

  } while (ret != END_OF_FILE_BIN);

  return found;
}

/**
 * @brief Esta funcao tenta removir um registro do arquivo binario com base nos campos 
 * nao vazios do DataRegister passado.
 * OBS: O arquivo ja deve estar aberto para a leitura e escrita no modo binario.
 * 
 * @param f FILE do arquivo binario de leitura.
 * @param dr Variavel que contem os campos de busca do registro.
 *
 * @author Leonardo Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
void deleteDataRegisterBIN(FILE *f, DataRegister *dr) {

  HeaderRegister hr;

  readHeaderRegisterBIN(f, &hr);
  hr.status = '0';
  writeHeaderRegisterBIN(f, &hr);

  fseek(f, SEEK_FIRST_REGISTER, SEEK_SET);

  DataRegister r;

  linkedlist nomesEstacoes;
  createLinkedList(&nomesEstacoes);

  linkedlist paresEstacoes;
  createLinkedList(&paresEstacoes);

  int ret;

  do {

    LONG_8 byteAtual = ftell(f);
    ret = readDataRegisterBIN(f, &r);

    if (ret == REMOVED) continue;
    else if (ret == END_OF_FILE_BIN) break;
    else { // estacao nao removida

      if(compareRegister(*dr, r) == EQUIVALENT_REGISTERS) {

        fseek(f, byteAtual, SEEK_SET); // volta para o byteoffset do registro lido

        r.removido = '1';
        r.proxLista = hr.topoDaLista;
        hr.topoDaLista = byteAtual; // byte offset do registro removido

        writeDataRegisterBIN(f, &r);
      
      } else {
        addStringLinkedList(&nomesEstacoes, r.nomeEstacao);
        addParEstacoesLinkedList(&paresEstacoes, r.codEstacao, r.codProxEstacao);
      }
    }
  } while (ret != END_OF_FILE_BIN);

  hr.nroEstacoes = nomesEstacoes.size;
  hr.nroParesEstacao = paresEstacoes.size;
  hr.status = '1';

  writeHeaderRegisterBIN(f, &hr);

  deleteLinkedList(&nomesEstacoes);
  deleteLinkedList(&paresEstacoes);
}


/**
 * @brief Esta funcao adiciona um novo registro no arquivo binario. O novo registro 
 * sobrescrevera algum registro logicamente removido se possivel ou entao sera 
 * escrito no final do arquivo.
 * OBS: O arquivo ja deve estar aberto para a leitura e escrita no modo binario.
 * 
 * @param f FILE do arquivo binario de leitura.
 * @param Variavel que contem os campos de busca do registro. 
 *
 * @author Leonardo Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
void insertDataRegisterBIN(FILE *f, DataRegister *dr) {

  HeaderRegister hr;
  readHeaderRegisterBIN(f, &hr);
  hr.status = '0';
  writeHeaderRegisterBIN(f, &hr);

  DataRegister r; // o que a gente le

  LONG_8 byteAnterior, byteProximo;
  LONG_8 byteDisponivel = findAvailableSpaceRegister(f, hr.topoDaLista, &byteAnterior, &byteProximo, dr->tamanhoRegistro);

  if(byteDisponivel == -1) { // registro escrito no final do arquivo
    fseek(f, 0, SEEK_END);
    writeDataRegisterBIN(f, dr);
  } else {

    if (byteAnterior == byteDisponivel) hr.topoDaLista = byteProximo; // registro topo da lista
    else updateRemovedRegisterListBIN(f, byteAnterior, byteProximo);

    fseek(f, byteDisponivel, SEEK_SET);
    readDataRegisterBIN(f, &r);

    int tamanhoAntigo = dr->tamanhoRegistro;
    dr->tamanhoRegistro = r.tamanhoRegistro;

    fseek(f, byteDisponivel, SEEK_SET);
    writeDataRegisterBIN(f, dr);
    fillWithTrash(f, r.tamanhoRegistro - tamanhoAntigo);
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

  deleteLinkedList(&nomesEstacoes);
  deleteLinkedList(&paresDistintosEstacoes);
}

/**
 * @brief Esta funcao atualiza registros no arquivo binario. A busca pelos registro 
 * a serem alterados utiliza os campos nao vazios do DataRegister dr_busca e as 
 * alteracoes a serem feitas estao salvas nos campos nao vazios do DataRegister dr_alteracao.
 * OBS: O arquivo ja deve estar aberto para a leitura e escrita no modo binario.
 * 
 * @param f FILE do arquivo binario.
 * @param dr_busca Variavel que contem os campos de busca do registro.
 * @param dr_alteracao Variavel que contem os novos dados a serem salvos nos registros.
 *
 * @author Leonardo Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
void updateDataRegisterBIN(FILE *f, DataRegister *dr_busca, DataRegister *dr_alteracao) {

  HeaderRegister hr;
  readHeaderRegisterBIN(f, &hr);
  hr.status = '0';
  writeHeaderRegisterBIN(f, &hr);

  linkedlist nomesEstacoes;
  createLinkedList(&nomesEstacoes);

  linkedlist paresEstacoes;
  createLinkedList(&paresEstacoes);

  linkedlist bytesOffsetUpdate;
  createLinkedList(&bytesOffsetUpdate);

  fseek(f, SEEK_FIRST_REGISTER, SEEK_SET);

  DataRegister r;

  while(!feof(f)) {

    LONG_8 byteOffset = ftell(f);
    int ret = readDataRegisterBIN(f, &r);

    if (ret == END_OF_FILE_BIN) break;
    else if (ret == REMOVED) continue;

    LONG_8 nextByteOffset = ftell(f);

    if(compareRegister(r, *dr_busca) == EQUIVALENT_REGISTERS && hasLONG_8ElementLinkedList(&bytesOffsetUpdate, byteOffset) == FALSE) {

      LONG_8 *b = (LONG_8*) malloc(sizeof(LONG_8)); // Guarda o byte offset de onde o registro sera atualizado
      if (b == NULL) return;

      int tamanhoAntigo = r.tamanhoRegistro;
      copyDataRegister(&r, dr_alteracao);
      r.tamanhoRegistro = sizeOfRegister(r);

      fseek(f, byteOffset, SEEK_SET);

      if(r.tamanhoRegistro <= tamanhoAntigo) { // Pode escrever o registro no mesmo lugar.

        int t = r.tamanhoRegistro;
        r.tamanhoRegistro = tamanhoAntigo;
        writeDataRegisterBIN(f, &r);
        fillWithTrash(f, tamanhoAntigo - t);

      } else {

        char rem = '1';
        fwrite(&rem, sizeof(char), 1, f); // Altera o registro para logicamente removido nesta posicao.

        fseek(f, sizeof(r.tamanhoRegistro), SEEK_CUR); // Pula campo tamanhoRegistro

        LONG_8 proxLista = hr.topoDaLista;
        fwrite(&proxLista, sizeof(r.proxLista), 1, f);
        hr.topoDaLista = byteOffset;

        LONG_8 byte, byteAnterior, byteProximo;
        byte = findAvailableSpaceRegister(f, hr.topoDaLista, &byteAnterior, &byteProximo, r.tamanhoRegistro);

        if(byte == -1) { // Escrever no final do arquivo.

          fseek(f, 0, SEEK_END);
          *b = ftell(f);
          writeDataRegisterBIN(f, &r);

        } else {

          if (byte == byteAnterior) hr.topoDaLista = byteProximo; // Topo da lista.
          else updateRemovedRegisterListBIN(f, byteAnterior, byteProximo);

          fseek(f, byte, SEEK_SET);
          *b = byte;

          DataRegister aux;
          readDataRegisterBIN(f, &aux);

          fseek(f, byte, SEEK_SET);

          int t_aux = r.tamanhoRegistro;
          r.tamanhoRegistro = aux.tamanhoRegistro;
          writeDataRegisterBIN(f, &r);
          fillWithTrash(f, aux.tamanhoRegistro - t_aux);
        }
      }

      addElementLinkedList(&bytesOffsetUpdate, b);
      fseek(f, nextByteOffset, SEEK_SET);
    }

    addStringLinkedList(&nomesEstacoes, r.nomeEstacao);
    addParEstacoesLinkedList(&paresEstacoes, r.codEstacao, r.codProxEstacao);
  }

  hr.status = '1';
  hr.nroEstacoes = nomesEstacoes.size;
  hr.nroParesEstacao = paresEstacoes.size;

  writeHeaderRegisterBIN(f, &hr);

  deleteLinkedList(&nomesEstacoes);
  deleteLinkedList(&paresEstacoes);
  deleteLinkedList(&bytesOffsetUpdate);
}

/**
 * @brief Esta funcao cria  do zero um arquivo de dados binario a partir de um 
 * arquivo CSV.
 * 
 * @param csvName Nome do arquivo csv.
 * @param binName Nome do arquivo binario.
 * @return FILE_ERROR caso os arquivos nao possam ser abertos ou SUCCESS caso a 
 * operacao chegue ao fim.
 *
 * @author Leonardo Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
int createFileBIN(char *csvName, char *binName) {

  FILE *fin = fopen(csvName, "r");
  if(fin == NULL) return FILE_ERROR;

  FILE *fout = fopen(binName, "wb");
  if(fout == NULL) {
    fclose(fin);
    return FILE_ERROR;
  }

  HeaderRegister hr;
  hr.status = '0';
  hr.topoDaLista = NULL_FIELD_INTEGER;
  hr.nroEstacoes = 0;
  hr.nroParesEstacao = 0;

  fwrite(&hr.status, sizeof(hr.status), 1, fout);
  fwrite(&hr.topoDaLista, sizeof(hr.topoDaLista), 1, fout);
  fwrite(&hr.nroEstacoes, sizeof(hr.nroEstacoes), 1, fout);
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

  hr.nroEstacoes = nomesEstacoes.size;
  hr.nroParesEstacao = paresDistintosEstacoes.size;
  hr.status = '1';

  writeHeaderRegisterBIN(fout, &hr);

  deleteLinkedList(&paresDistintosEstacoes);
  deleteLinkedList(&nomesEstacoes);

  fclose(fin);
  fclose(fout);

  return SUCCESS;
}


/**
 * @brief  Esta funcao printa todos os registros nao removidos do arquivo binario.
 * 
 * @param binName Nome do arquivo binario.
 * @return FILE_ERROR (caso o arquivo nao possa ser aberto),
 *         REGISTER_NOT_FOUND (caso nenhum registro tenha sido encontrado),
 *         REGISTER_FOUND (caso ao menos 1 registro tenha sido encontrado).
 *
 * @author Leonardo Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
int printFileBIN(char *binName) {

  FILE *f = fopen(binName, "rb");
  if(f == NULL) return FILE_ERROR;

  int found = REGISTER_NOT_FOUND;

  DataRegister dr;
  HeaderRegister rc;
  fseek(f, SEEK_FIRST_REGISTER, SEEK_SET);

  int ret;

  while(!feof(f)) {

    ret = readDataRegisterBIN(f, &dr);

    if (ret == END_OF_FILE_BIN) break;
    else if(ret == NOT_REMOVED) {
      printRegister(dr);
      found = REGISTER_FOUND;
    } else continue;

    printf("\n");
  }

  fclose(f);

  return found;
}


/**
 * @brief Esta funcao escreve o caracter MEMORY_TRASH na posicao corrente de escrita 
 * do arquivo binario.
 * OBS: O arquivo ja deve estar aberto para escrita no modo binario.
 * 
 * @param f FILE do arquivo binario (arquivo ja deve estar aberto).
 * @param numBytes Numero de MEMORY_TRASH que serao escritos.
 *
 * @author Leonardo Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
void fillWithTrash(FILE *f, int numBytes) {
  char trash = MEMORY_TRASH;
  for(int i = 0; i < numBytes; i++) fwrite(&trash, sizeof(char), 1, f);
}


/**
 * @brief Esta funcao percorre a lista de arquivos logicamente removidos em 
 * busca de um registro que possua tamanho maior ou igual ao tamanho buscado.
 * OBS: O arquivo ja deve estar aberto para a leitura no modo binario. 
 * 
 * @param f FILE do arquivo binario (arquivo ja deve estar aberto).
 * @param topoDaLista Primeiro registro logicamente removido da lista.
 * @param byteAnterior Byte offset do registro removido anterior (da lista) 
 * ao registro removido que atende as necessidades buscas.
 * @param byteProximo Byte offset do  proximo registro removido (da lista) ao 
 * registro removido que atende as necessidas buscadas.
 * @param numBytes Tamanho do espaco requerido.
 * @return -1, caso nenhum registro removido possua espaco suficiente, ou o byte offset
 * do registro que possui tamanho suficiente.
 *
 * @author Leonardo Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
long findAvailableSpaceRegister(FILE *f, LONG_8 topoDaLista, LONG_8 *byteAnterior, LONG_8 *byteProximo, long numBytes) {

  if(topoDaLista == NULL_FIELD_INTEGER) return -1;

  fseek(f, topoDaLista, SEEK_SET);
  DataRegister dr;

  *byteAnterior = topoDaLista;

  do {

    LONG_8 byteAtual = ftell(f);

    fread(&dr.removido, sizeof(dr.removido), 1, f);
    fread(&dr.tamanhoRegistro, sizeof(dr.tamanhoRegistro), 1, f);
    fread(&dr.proxLista, sizeof(dr.proxLista), 1, f);

    *byteProximo = dr.proxLista;

    if (dr.tamanhoRegistro >= numBytes) return byteAtual;
    else if (dr.proxLista != NULL_FIELD_INTEGER) {
      fseek(f, dr.proxLista, SEEK_SET);
      *byteAnterior = byteAtual;
    }

  } while(dr.proxLista != NULL_FIELD_INTEGER);

  return -1;
}


/**
 * @brief Esta funcao atualiza a lista de registros logicamente removidos alterando 
 * o byte offset salvo no campo 'proxLista' do registro removido passado (byteAtual).
 * OBS: O arquivo ja deve estar aberto para a leitura/escrita no modo binario.
 
 * @param f FILE do arquivo binario (arquivo ja deve estar aberto).
 * @param byteAtual Byte offset do registro que tera o campo 'proxLista' alterado.
 * @param byteProximo Valor que sera salvo no campo 'proxLista' do registro passado.
 *
 * @author Leonardo Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
void updateRemovedRegisterListBIN(FILE *f, LONG_8 byteAtual, LONG_8 byteProximo) {
  
  DataRegister dr;
  dr.proxLista = byteProximo;
  LONG_8 byte = byteAtual + sizeof(dr.removido) + sizeof(dr.tamanhoRegistro);

  fseek(f, byte, SEEK_SET);
  fwrite(&dr.proxLista, sizeof(dr.proxLista), 1, f);
}