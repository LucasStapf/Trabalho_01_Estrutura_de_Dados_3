/**
* Trabalho 01 - Estrutura de Dados III
*
* Integrantes do grupo:
* 
* Leonardo Hannas de Carvalho Santos  NUSP: 11800480
* Lucas Carvalho Freiberger Stapf     NUSP: 11800559
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct node node;
typedef struct linkedlist linkedlist;


struct node {
  void *data;
  node *next;
};

struct linkedlist {
  int size;
  node *head;
  node *currentnode;
};

void createLinkedList(linkedlist *l);

int addElementLinkedList(linkedlist *l, void *data);
void* getNextElementLinkedList(linkedlist *l);
int hasNextElementLinkedList(linkedlist *l);
int hasIntegerElementLinkedList(linkedlist *l, int n);

void addStringLinkedList(linkedlist *l, char *str);
void addParEstacoesLinkedList(linkedlist *l, int codEstacao, int codProxEstacao);

void deleteLinkedList(linkedlist *l);

void printStringLinkedList(linkedlist l);
void printParEstacoesLinkedList(linkedlist l);

#endif 