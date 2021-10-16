#include <stdio.h>
#include "../headers/display.h"
#include "../headers/constants.h"

/**
  - Function: showMessage
  - Description: Esta funcao printa na tela uma mensagem de acordo com o parametro passado.
  - Parameters: 
    - cod: codigo da mensagem.
  - Returns: 
    - cod
*/
int showMessage(int cod) {

    switch (cod)
    {
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