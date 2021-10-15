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
  - Function: sizeOfRegister
  - Description: Esta funcao calcula o tamanho de um registro de dados no arquivo binario.
  - Note: O tamanho retornado nao eh o real tamanho do DataRegister em si, uma vez que a funcao contabiliza a presenca do pipe '|' no fim das strings, mesmo que no DataRegister em si nao tenha o pipe.
  - Parameters: 
    - dr: struct DataRegister
  - Returns: Retorna o tamanho do registro no arquivo binario.
*/
int sizeOfRegister(DataRegister dr)
{

  int size = (1 + 2 + strlen(dr.nomeEstacao) + strlen(dr.nomeLinha)) * sizeof(dr.removido); // + 2: contabilizando o pipe '|'
  size += (7 * sizeof(dr.tamanhoRegistro));
  size += sizeof(LONG_8);

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
int compareRegister(DataRegister dr1, DataRegister dr2)
{

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

  if (dr1.nomeEstacao[0] != EMPTY_FIELD_STRING && dr2.nomeEstacao[0] != EMPTY_FIELD_STRING && strcmp(dr1.nomeEstacao, dr2.nomeEstacao) != 0)
    return DIFFERENT_REGISTERS;

  if (dr1.nomeLinha[0] != EMPTY_FIELD_STRING && dr2.nomeLinha[0] != EMPTY_FIELD_STRING && strcmp(dr1.nomeLinha, dr2.nomeLinha) != 0)
    return DIFFERENT_REGISTERS;

  return EQUIVALENT_REGISTERS;
}

/**
  - Function: setEmptyDataRegister
  - Description: Esta funcao inicializa todos os campos do DataRegister passado com valores vazios (EMPTY_FIELD_INTEGER ou EMPTY_FIELD_STRING).
  - Parameters: 
    - dr: Registro que tera seus campos atualizados para vazio.
*/
void setEmptyDataRegister(DataRegister *dr)
{

  dr->codEstacao = EMPTY_FIELD_INTEGER;
  dr->codLinha = EMPTY_FIELD_INTEGER;
  dr->codProxEstacao = EMPTY_FIELD_INTEGER;
  dr->distProxEstacao = EMPTY_FIELD_INTEGER;
  dr->codLinhaIntegra = EMPTY_FIELD_INTEGER;
  dr->codEstIntegra = EMPTY_FIELD_INTEGER;
  dr->nomeEstacao[0] = EMPTY_FIELD_STRING;
  dr->nomeLinha[0] = EMPTY_FIELD_STRING;
}

/**
  - Function: fillFieldDataRegister
  - Description: Esta funcao preenche um campo do DataRegister passado com base no nome do campo.
  - Note: Tanto o nome quando o valor do campo devem ser do tipo string(char*).
  - Parameters: 
    - dr: Registro que tera o campo atualizado.
    - field: Nome do campo a ser atualizado.
    - value: Valor do campo.
*/
void fillFieldDataRegister(DataRegister *dr, char *field, char *value)
{

  if (strcmp("codEstacao", field) == 0)
    dr->codEstacao = atoi(value);
  else if (strcmp("codLinha", field) == 0)
    dr->codLinha = atoi(value);
  else if (strcmp("codProxEstacao", field) == 0)
    dr->codProxEstacao = atoi(value);
  else if (strcmp("distProxEstacao", field) == 0)
    dr->distProxEstacao = atoi(value);
  else if (strcmp("codLinhaIntegra", field) == 0)
    dr->codLinhaIntegra = atoi(value);
  else if (strcmp("codEstIntegra", field) == 0)
    dr->codEstIntegra = atoi(value);
  else if (strcmp("nomeEstacao", field) == 0)
    strcpy(dr->nomeEstacao, value);
  else if (strcmp("nomeLinha", field) == 0)
    strcpy(dr->nomeLinha, value);
}

/**
  - Function: printRegister
  - Description: Esta funcao imprime um registro na tela, com os campos sendo exibidos na seguinte ordem:
  - codEstacao | nomeEstacao | codLinha | nomeLinha | codProxEstacao | distProxEstacao | codLinhaIntegra | codEstIntegra
  - Note: Campos NULOS (NULL_FIELD_INTEGER ou NULL_FIELD_STRING) serao exibidos como 'NULO'.
  - Parameters: 
    - dr: Registro a ser exibido.
*/
void printRegister(DataRegister dr)
{

  printf("%d ", dr.codEstacao);  //
  printf("%s ", dr.nomeEstacao); //

  (dr.codLinha != NULL_FIELD_INTEGER) ? printf("%d ", dr.codLinha) : printf("NULO ");
  (strlen(dr.nomeLinha) != 0) ? printf("%s ", dr.nomeLinha) : printf("NULO ");
  (dr.codProxEstacao != NULL_FIELD_INTEGER) ? printf("%d ", dr.codProxEstacao) : printf("NULO ");
  (dr.distProxEstacao != NULL_FIELD_INTEGER) ? printf("%d ", dr.distProxEstacao) : printf("NULO ");
  (dr.codLinhaIntegra != NULL_FIELD_INTEGER) ? printf("%d ", dr.codLinhaIntegra) : printf("NULO ");
  (dr.codEstIntegra != NULL_FIELD_INTEGER) ? printf("%d", dr.codEstIntegra) : printf("NULO");
}