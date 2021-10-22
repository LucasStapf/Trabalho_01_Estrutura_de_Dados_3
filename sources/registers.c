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
#include "../headers/registers.h"


/**
 * @brief Esta funcao calcula o tamanho de um registro de dados no arquivo binario.
 * OBS: O tamanho retornado nao eh o real tamanho do DataRegister em si, uma vez que a funcao
 * contabiliza a presenca FIELD_DELIMITER no DataRegister mesmo que o dr em si nao tenha o FIELD_DELIMITER.
 * O tamanho tambem nao leva em conta os campos 'removido' e 'tamanhoRegistro'.
 * 
 * @param dr Registro de dados que tera o tamanho calculado.
 * @return int Tamanho do registro de dados.
 * 
 * @author Leonadro Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf 
 */
int sizeOfRegister(DataRegister dr) {

  int size = (2 + strlen(dr.nomeEstacao) + strlen(dr.nomeLinha)) * sizeof(char); // + 2: contabilizando o pipe '|'
  size += (6 * sizeof(int));
  size += sizeof(LONG_8);

  return size;
}


/**
 * @brief Esta funcao compara dois registros de dados e verifica se os mesmos sao equivalentes. 
  Campos vazios e os campos 'removido', 'tamanhoRegistro' e 'proxLista' sao desconsiderados na comparacao.
 * 
 * @param dr1 Registro de dados 1.
 * @param dr2 Registro de dados 2.
 * @return DIFFERENT_REGISTERS caso os registros nao sejam equivalentes, EQUIVALENT_REGISTERS caso contrario.
 * 
 * @author Leonadro Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf 
 */
int compareRegister(DataRegister dr1, DataRegister dr2) {

  if (dr1.codEstacao != EMPTY_FIELD_INTEGER && dr2.codEstacao != EMPTY_FIELD_INTEGER && dr1.codEstacao != dr2.codEstacao)
    return DIFFERENT_REGISTERS;

  if (dr1.codLinha != EMPTY_FIELD_INTEGER && dr2.codLinha != EMPTY_FIELD_INTEGER && dr1.codLinha != dr2.codLinha)
    return DIFFERENT_REGISTERS;

  if (dr1.codProxEstacao != EMPTY_FIELD_INTEGER && dr2.codProxEstacao != EMPTY_FIELD_INTEGER && dr1.codProxEstacao != dr2.codProxEstacao)
    return DIFFERENT_REGISTERS;

  if (dr1.distProxEstacao != EMPTY_FIELD_INTEGER && dr2.distProxEstacao != EMPTY_FIELD_INTEGER && dr1.distProxEstacao != dr2.distProxEstacao)
    return DIFFERENT_REGISTERS;

  if (dr1.codLinhaIntegra != EMPTY_FIELD_INTEGER && dr2.codLinhaIntegra != EMPTY_FIELD_INTEGER && dr1.codLinhaIntegra != dr2.codLinhaIntegra)
    return DIFFERENT_REGISTERS;

  if (dr1.codEstIntegra != EMPTY_FIELD_INTEGER && dr2.codEstIntegra != EMPTY_FIELD_INTEGER && dr1.codEstIntegra != dr2.codEstIntegra)
    return DIFFERENT_REGISTERS;

  if (dr1.codEstacao != EMPTY_FIELD_INTEGER && dr2.codEstacao != EMPTY_FIELD_INTEGER && dr1.codEstacao != dr2.codEstacao)
    return DIFFERENT_REGISTERS;

  if (strcmp(dr1.nomeEstacao, EMPTY_FIELD_STRING) != 0 && strcmp(dr2.nomeEstacao, EMPTY_FIELD_STRING) && strcmp(dr1.nomeEstacao, dr2.nomeEstacao) != 0)
    return DIFFERENT_REGISTERS;

  if (strcmp(dr1.nomeLinha, EMPTY_FIELD_STRING) != 0 && strcmp(dr2.nomeLinha, EMPTY_FIELD_STRING) && strcmp(dr1.nomeLinha, dr2.nomeLinha) != 0)
    return DIFFERENT_REGISTERS;

  return EQUIVALENT_REGISTERS;
}


/**
 * @brief Esta funcao inicializa todos os campos do DataRegister passado com
 * valores vazios (EMPTY_FIELD_INTEGER ou EMPTY_FIELD_STRING). Os campos
 * 'removido', 'tamanhoRegistro' e 'proxLista' nao sao atualizados.
 * 
 * @param dr Registro que tera seus campos atualizados para vazio.
 * 
 * @author Leonadro Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
void setEmptyDataRegister(DataRegister *dr) {

  dr->codEstacao = EMPTY_FIELD_INTEGER;
  dr->codLinha = EMPTY_FIELD_INTEGER;
  dr->codProxEstacao = EMPTY_FIELD_INTEGER;
  dr->distProxEstacao = EMPTY_FIELD_INTEGER;
  dr->codLinhaIntegra = EMPTY_FIELD_INTEGER;
  dr->codEstIntegra = EMPTY_FIELD_INTEGER;
  strcpy(dr->nomeEstacao, EMPTY_FIELD_STRING);
  strcpy(dr->nomeLinha, EMPTY_FIELD_STRING);
}


/**
 * @brief Esta funcao preenche um campo do DataRegister passado com base no nome do campo.
 * OBS:  Tanto o nome quando o valor do campo devem ser do tipo string (char*).
 * 
 * @param dr Registro que tera o campo atualizado.
 * @param field Nome do campo a ser atualizado.
 * @param value Valor do campo.
 * 
 * @author Leonadro Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
void fillFieldDataRegister(DataRegister *dr, char *field, char *value) {

  if (strcmp("codEstacao", field) == 0) // Nao pode ser nulo
    dr->codEstacao = atoi(value);
  else if (strcmp("nomeEstacao", field) == 0) // Nao pode ser nulo
    strcpy(dr->nomeEstacao, value);
  else if (strcmp("codLinha", field) == 0)
    dr->codLinha = atoi(value) != 0 ? atoi(value) : NULL_FIELD_INTEGER;
  else if (strcmp("codProxEstacao", field) == 0)
    dr->codProxEstacao = atoi(value) != 0 ? atoi(value) : NULL_FIELD_INTEGER;
  else if (strcmp("distProxEstacao", field) == 0)
    dr->distProxEstacao = atoi(value) != 0 ? atoi(value) : NULL_FIELD_INTEGER;
  else if (strcmp("codLinhaIntegra", field) == 0)
    dr->codLinhaIntegra = atoi(value) != 0 ? atoi(value) : NULL_FIELD_INTEGER;
  else if (strcmp("codEstIntegra", field) == 0)
    dr->codEstIntegra = atoi(value) != 0 ? atoi(value) : NULL_FIELD_INTEGER;
  else if (strcmp("nomeLinha", field) == 0)
    strcmp(value, "NULO") != 0 ? strcpy(dr->nomeLinha, value) : strcpy(dr->nomeLinha, NULL_FIELD_STRING);
}


/**
 * @brief Esta funcao copia os campos nao vazios do DataRegister de origem
 * nos respectivos campos do DataRegister de destino.
 * 
 * @param dr_destino DataRegister que tera os campos alterados.
 * @param dr_origem DataRegister que tera os campos nao vazios copiados.
 * 
 * @author Leonadro Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf 
 */
void copyDataRegister(DataRegister *dr_destino, DataRegister *dr_origem) {

  if (dr_origem->codEstacao != EMPTY_FIELD_INTEGER)
    dr_destino->codEstacao = dr_origem->codEstacao;
  if (dr_origem->codLinha != EMPTY_FIELD_INTEGER)
    dr_destino->codLinha = dr_origem->codLinha;
  if (dr_origem->codProxEstacao != EMPTY_FIELD_INTEGER)
    dr_destino->codProxEstacao = dr_origem->codProxEstacao;
  if (dr_origem->distProxEstacao != EMPTY_FIELD_INTEGER)
    dr_destino->distProxEstacao = dr_origem->distProxEstacao;
  if (dr_origem->codLinhaIntegra != EMPTY_FIELD_INTEGER)
    dr_destino->codLinhaIntegra = dr_origem->codLinhaIntegra;
  if (dr_origem->codEstIntegra != EMPTY_FIELD_INTEGER)
    dr_destino->codEstIntegra = dr_origem->codEstIntegra;

  if (strcmp(dr_origem->nomeEstacao, EMPTY_FIELD_STRING) != 0)
    strcpy(dr_destino->nomeEstacao, dr_origem->nomeEstacao);
  if (strcmp(dr_origem->nomeLinha, EMPTY_FIELD_STRING) != 0)
    strcpy(dr_destino->nomeLinha, dr_origem->nomeLinha);
}


/**
 * @brief Esta funcao imprime um registro na tela, com os campos sendo exibidos na seguinte ordem:
 *        codEstacao | nomeEstacao | codLinha | nomeLinha | codProxEstacao | distProxEstacao |
 *        codLinhaIntegra | codEstIntegra
 * OBS: Campos NULOS (NULL_FIELD_INTEGER ou NULL_FIELD_STRING) serao exibidos como 'NULO'.
 * 
 * @param dr Registro a ser exibido.
 * 
 * @author Leonadro Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
void printRegister(DataRegister dr) {

  printf("%d ", dr.codEstacao);  //
  printf("%s ", dr.nomeEstacao); //

  (dr.codLinha != NULL_FIELD_INTEGER) ? printf("%d ", dr.codLinha) : printf("NULO ");
  (strlen(dr.nomeLinha) != 0) ? printf("%s ", dr.nomeLinha) : printf("NULO ");
  (dr.codProxEstacao != NULL_FIELD_INTEGER) ? printf("%d ", dr.codProxEstacao) : printf("NULO ");
  (dr.distProxEstacao != NULL_FIELD_INTEGER) ? printf("%d ", dr.distProxEstacao) : printf("NULO ");
  (dr.codLinhaIntegra != NULL_FIELD_INTEGER) ? printf("%d ", dr.codLinhaIntegra) : printf("NULO ");
  (dr.codEstIntegra != NULL_FIELD_INTEGER) ? printf("%d", dr.codEstIntegra) : printf("NULO");
}