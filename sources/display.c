/**
 * Trabalho 01 - Estrutura de Dados III
 *
 * Integrantes do grupo:
 *
 * Leonardo Hannas de Carvalho Santos  NUSP: 11800480
 * Lucas Carvalho Freiberger Stapf     NUSP: 11800559
 */

#include <stdio.h>
#include "../headers/display.h"
#include "../headers/constants.h"

/**
  - Function: showMessage
  - Description: Esta funcao printa na tela uma mensagem de acordo com o parametro passado.
  - Parameters:
    - cod: Codigo da mensagem.
  - Returns:
    - cod: O proprio codigo passado
*/
int showMessage(int cod) {

    switch(cod) {
    
    case FILE_ERROR:
        printf("Falha no processamento do arquivo.");
        break;

    case REGISTER_NOT_FOUND:
        printf("Registro inexistente.");
        break;

    default:
        break;
    }

    return cod;
}