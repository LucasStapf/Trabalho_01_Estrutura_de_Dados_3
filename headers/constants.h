/**
* Trabalho 01 - Estrutura de Dados III
*
* Integrantes do grupo:
* 
* Leonardo Hannas de Carvalho Santos  NUSP: 11800480
* Lucas Carvalho Freiberger Stapf     NUSP: 11800559
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define LONG_8 long long

#define TRUE  0
#define FALSE 1

#define SUCCESS 0

#define MAX_SIZE_STR 200

#define REMOVED     1
#define NOT_REMOVED 0

#define FILE_ERROR      1
#define END_OF_FILE_BIN 2

#define REGISTER_NOT_FOUND  3
#define REGISTER_FOUND      0

#define DIFFERENT_REGISTERS   4
#define EQUIVALENT_REGISTERS  5

// Definidos a partir do SEEK_SET.
#define SEEK_STATUS               0
#define SEEK_TOPO_LISTA           1
#define SEEK_NRO_ESTACOES         9
#define SEEK_NRO_PARES_ESTACOES   13
#define SEEK_FIRST_REGISTER       17

// Constantes para preencher os campos dos DataRegister.
#define NULL_FIELD_INTEGER    -1
#define NULL_FIELD_STRING     "\0"
#define EMPTY_FIELD_INTEGER   -2
#define EMPTY_FIELD_STRING    "#\0"
#define MEMORY_TRASH          '$'

#define FIELD_DELIMITER '|'

#endif
