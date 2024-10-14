#include "list.h"
#include <stdio.h>

// typedef struct {
//   int val;
//   struct Node* next, prev;
// } Node;
// 
// typedef struct {
//   Node* head, tail;
//   int n;
// } List;

List* makeList() {
  List* list;
  list->head = NULL;
  list->tail = NULL;
  list->n=0;
  return list;
}

Node* makeNode(int i) {
  Node* n;
  n->val = i;
  n->next = NULL;
  n->prev =NULL;
  return n;
}

void printList(List* l) {
  Node* node = l->head;
  while (node != NULL) {
    printf("%d ", node->val);
    node = node->prev;
  }
}

void push(List* l, int i) {
  Node* node = makeNode(i);

  if (l->n == 0) {
    node->next = node->prev = NULL;
    l->head = l->tail = node;

    l->n++;
    return;
  }

  Node* prevNode = l->head;
  prevNode->next = node;
  node->prev = prevNode;
  node->next = NULL;
  l->head=node;
  l->n++;
  return;
}

// int pop(List* l);
// int peek(List* l);
// 
// int getIndex(List* l, int i);
// 
// int getFront(List* l);
// int getRear(List* l);
// int isEmpty(List* l);
// 
// int enqueue(List* l, int i);
// int dequeue(List* l);

