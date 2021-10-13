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


void createLinkedList(linkedlist *l) {
  l->size = 0;
  l->head = NULL;
  l->currentnode = NULL;
}

void deleteLinkedList(linkedlist *l) {

  node *n = l->head;

  while(n != NULL) {
    l->head = l->head->next;
    free(n->data);
    free(n);
    n = l->head;
  }
}

int addElementLinkedList(linkedlist *l, void *data) {
  
  if(l == NULL || data == NULL) return 0;

  node *n = malloc(sizeof(node));
  if(n == NULL) return 0;

  n->data = data;
  n->next = NULL;

  if(l->head == NULL) { // Lista vazia

    l->head = n;
    l->currentnode = n;
    l->size++;

    return 1;

  } else {

		node *aux = l->head;
		while (aux->next != NULL) aux = aux->next;
		aux->next = n;
    l->size++;

    return 1;
  }
}

void* getNextElementLinkedList(linkedlist *l) {

  node *n = l->currentnode;
  if(hasNextElementLinkedList(l)) l->currentnode = l->currentnode->next;
  return (n == NULL) ? NULL : n->data;
}

int hasNextElementLinkedList(linkedlist *l) {

  if(l->currentnode == NULL) return 0;
  else if(l->currentnode->next == NULL) return 0;
  else return 1;
}

// adiciona somente strings diferentes
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


// Nao é comutativo: (1,2) != (2,1)
void addParEstacoesLinkedList(linkedlist *l, int codEstacao, int codProxEstacao) {
	
	if(l == NULL || codEstacao == -1 || codProxEstacao == -1) return;

	node *n = (node*) malloc(sizeof(node));
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
  
  while(node != NULL) {

    int *i = (int*) node->data;
    if(*i == n) return TRUE;
    else node = node->next;
  }

  return FALSE;
}

void printStringLinkedList(linkedlist l) {
  
  node *aux = l.head;
  while(aux != NULL) {
    printf("%s\n", aux->data);
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