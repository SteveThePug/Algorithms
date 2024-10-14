#include "list.h"
#include <stdio.h>
#include <stdlib.h>

List* makeList() {
  List* list = (List*)calloc(1, sizeof(List));
  return list;
}

void freeList(List* l) {
  Node* node = l->head;
  Node* next = l->head;
  while (next != NULL) {
    node=next;
    next=node->prev;
    free(node);
  }
  free(l);
}

Node* makeNode(int i) {
  Node* n = (Node *)calloc(1, sizeof(Node));
  n->val = i;
  return n;
}

void freeNode(Node* n) {
  free(n);
}

void printList(List* l) {
  Node* node = l->head;
  printf("Head <-- --> Tail\n");
  while (node != NULL) {
    printf("%d ", node->val);
    node = node->next;
  }
  printf("\n");
}

void push(List* l, int i) {
  Node* node = makeNode(i);

  if (l->n == 0) {
    node->next = node->prev = NULL;

    l->head = l->tail = node;
    l->n++;
    return;
  }

  Node* head = l->head;
  head->prev = node;

  node->prev = NULL;
  node->next = head;

  l->head=node;
  l->n++;
  return;
}

int pop(List* l) {
  Node* head = l->head;
  Node* next = head->next;
  int val = head->val;
  freeNode(head);

  next->prev = NULL;
  l->head = next;
  l->n--;
  return val;
}

int peek(List* l) {
  return l->head->val;
}

int getIndex(List* l, int i) {
  Node* node = l->head;
  int j = 0;
  while (node != NULL) {
    if (j==i) {
      return node->val;
    }
    node=node->next;
    j++;
  }
  return 0;
}

int getHead(List* l) {
  return l->head->val;
}

int getTail(List* l) {
  return l->tail->val;
}

int isEmpty(List* l) {
  return l->n==0;
}
 
void enqueue(List* l, int i) {
  Node* node = makeNode(i);

  if (l->n==0) {
    node->next = node->prev = NULL;    
    l->head = l->tail = node;
    l->n++;
    return;
  }

  Node* tail = l->tail;
  tail->next = node;
  node->prev = tail;
  l->tail = node;
  l->n++;
}

int dequeue(List* l) {
  Node* head = l->head;
  Node* next = head->next;
  int val = head->val;
  free(head);

  next->prev = NULL;
  l->head = next;
  l->n--;
  return val;
}