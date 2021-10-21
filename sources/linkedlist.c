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
#include "../headers/linkedlist.h"
#include "../headers/constants.h"

/**
 * @brief Inicializa com os valores padrao uma lista encadeada
 *
 * @param l Lista encadeada a ser inicializada.
 */
void createLinkedList(linkedlist *l) {
  l->size = 0;
  l->head = NULL;
  l->currentnode = NULL;
}

/**
 * @brief Libera todos os nodos alocados para a lista encadeada.
 * 
 * @param l Lista encadeada a ser apagada.
 */
void deleteLinkedList(linkedlist *l) {

  node *n = l->head;

  while (n != NULL) {
    l->head = l->head->next;
    free(n->data);
    free(n);
    n = l->head;
  }
}

/**
 * @brief Adiciona um elemento generico na lista encadeada.
 * 
 * @param l Lista onde o elemento sera adicionado.
 * @param data Elemento generico a ser adicionado.
 * @return TRUE caso o elemento tenha sido adicionado com sucesso e FALSE caso contrario. 
 */
int addElementLinkedList(linkedlist *l, void *data) {

  if(l == NULL || data == NULL) return FALSE;

  node *n = malloc(sizeof(node));
  if(n == NULL) return FALSE;

  n->data = data;
  n->next = NULL;

  if(l->head == NULL) { // Lista vazia

    l->head = n;
    l->currentnode = n;
    l->size++;
    return TRUE;
  
  } else {

    node *aux = l->head;
    while (aux->next != NULL) aux = aux->next;
    aux->next = n;
    l->size++;
    return TRUE;
  }
}

void *getNextElementLinkedList(linkedlist *l)
{

  node *n = l->currentnode;
  if (hasNextElementLinkedList(l))
    l->currentnode = l->currentnode->next;
  return (n == NULL) ? NULL : n->data;
}

int hasNextElementLinkedList(linkedlist *l)
{

  if (l->currentnode == NULL)
    return 0;
  else if (l->currentnode->next == NULL)
    return 0;
  else
    return 1;
}

/**
 * @brief Funcao que adiciona apenas strings em uma lista encadeada. Strings iguais nao serao
 * adicionadas.
 * 
 * @param l Lista onde a string sera adicionada.
 * @param str String a ser adicionada.
 */
void addStringLinkedList(linkedlist *l, char *str) {

  if(l == NULL || str == NULL) return;

  node *n = (node*) malloc(sizeof(node));
  if(n == NULL) return;

  n->data = malloc(sizeof(char) * MAX_SIZE_STR);

  if (n->data == NULL) {
    free(n);
    return;
  }

  n->next = NULL;
  strcpy(n->data, str);

  if(l->head == NULL) { // Lista vazia

    l->head = n;
    l->currentnode = n;
    l->size++;
    return;
  
  } else {

    node *aux = l->head;

    while(aux != NULL) {
      
      if(strcmp(aux->data, str) == 0) {
        free(n->data);
        free(n);
        return;
      
      } else if(aux->next == NULL) {
        aux->next = n;
        l->size++;
        return;
      
      } else aux = aux->next;
    }
  }
}

/**
 * @brief Adiciona um par de codigos de estacoes (x,y) na lista encadeada, desde que seja um par valido. 
 * Ou seja, os valores de "codEstacao" e "codProxEstacao" devem ser diferentes de NULL_FIELD_INTEGER. 
 * Pares repetidos nao sao adicionados e considera-se a nao comutatividade, ou seja: par (x,y) != par (y,x).
 * 
 * @param l Lista onde o par sera adicionado.
 * @param codEstacao Codigo da estacao (x).
 * @param codProxEstacao Codigo da proxima estacao (y).
 */
void addParEstacoesLinkedList(linkedlist *l, int codEstacao, int codProxEstacao) {

  if(l == NULL || codEstacao == NULL_FIELD_INTEGER || codProxEstacao == NULL_FIELD_INTEGER) return;

  node *n = (node *)malloc(sizeof(node));
  if(n == NULL) return;

  n->data = malloc(sizeof(int) * 2);
  if(n->data == NULL) {
    free(n);
    return;
  }

  n->next = NULL;

  int *v = n->data;
  v[0] = codEstacao;
  v[1] = codProxEstacao;

  if(l->head == NULL) { // Lista vazia

    l->head = n;
    l->currentnode = n;
    l->size++;
    return;
    
  } else {

    node *aux = l->head;

    while(aux != NULL) {

      int *v_aux = aux->data;

      if(v_aux[0] == codEstacao && v_aux[1] == codProxEstacao) {

        free(n->data);
        free(n);
        return;
      
      } else if(aux->next == NULL) {

        aux->next = n;
        l->size++;
        return;
      
      } else aux = aux->next;
    }
  }
}


int hasIntegerElementLinkedList(linkedlist *l, int n) {

  node *node = l->head;

  while (node != NULL) {

    int *i = (int *)node->data;
    if (*i == n) return TRUE;
    else node = node->next;
  }

  return FALSE;
}

/**
 * @brief Verifica se o numero passado como argumento ja esta presente na lista encadeada.
 * 
 * @param l Lista onde ocorrera a verificacao.
 * @param n Numero a ser verificado.
 * @return TRUE caso o numero esteja presente, FALSE caso contrario. 
 */
int hasLONG_8ElementLinkedList(linkedlist *l, LONG_8 n) {

  node *node = l->head;

  while (node != NULL) {

    LONG_8 *i = (LONG_8*) node->data;
    if (*i == n) return TRUE;
    else node = node->next;
  }

  return FALSE;
}

void printStringLinkedList(linkedlist l) {

  node *aux = l.head;
  while (aux != NULL) {
    printf("%s\n", (char *)aux->data);
    aux = aux->next;
  }
}

void printParEstacoesLinkedList(linkedlist l) {

  node *aux = l.head;
  int *v;
  while(aux != NULL) {
    v = aux->data;
    printf("%d, %d\n", v[0], v[1]);
    aux = aux->next;
  }
}