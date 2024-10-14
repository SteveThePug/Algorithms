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

List* make_list();
void free_list(List* l);

Node* make_node(int i);
void free_node(Node* n);

void print_list(List* l);

int get_index(List* l, int i);

int get_head(List* l);
int get_tail(List* l);
int is_empty(List* l);

void enqueue(List* l, int i);
int dequeue(List* l);

void push(List* l, int i);
int pop(List* l);
int peek(List* l);

#endif
