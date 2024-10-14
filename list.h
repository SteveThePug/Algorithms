#ifndef LIST_H
#define LIST_H

typedef struct Node {
  int val;
  struct Node* next;
  struct Node* prev;
} Node;

typedef struct {
  Node* head;
  Node* tail;
  int n;
} List;

List* makeList();
void freeList(List* l);

Node* makeNode(int i);
void freeNode(Node* n);

void printList(List* l);

int getIndex(List* l, int i);

int getFront(List* l);
int getRear(List* l);
int isEmpty(List* l);

void enqueue(List* l, int i);
int dequeue(List* l);

void push(List* l, int i);
int pop(List* l);
int peek(List* l);

#endif
