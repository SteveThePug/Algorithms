#include<stdio.h>
#include<stdlib.h>

#include "graph.h"
#include "list.h"

int main(int argc, char* argv[]) {
	int n = 10;

	if (argc > 1) {
		n=atoi(argv[1]);
	}

	Graph g = make_graph(n);
	randomize_graph(&g, n);
	print_graph(&g);
	printf("\n");

	int len;
	int* arr = vertex_neighbors(&g, rand()%n, &len);

	int p_len;

	int u = rand()%n;
	int v = rand()%n;
	while (u == v) {
		int v = rand()%n;
	}

	printf("u:%2d, v:%2d\n", u, v);

	int* dfs_path = dfs_find_path(&g, u, v, &p_len);
	print_array(dfs_path, p_len);

	int* bfs_path = bfs_find_path(&g, u, v, &p_len);
	print_array(bfs_path, p_len);

	free_graph(&g);

	// List* l = makeList();	
	// push(l, 1);
	// push(l, 2);
	// push(l, 3);
	// push(l, 4);
	// printList(l);
	// printf("%d\n", pop(l));
	// printf("%d\n", pop(l));
	// printList(l);
	// enqueue(l, 5);
	// enqueue(l, 6);
	// printList(l);
	// printf("%d\n", dequeue(l));
	// printf("%d\n", dequeue(l));
	// printList(l);
	// freeList(l);

	return 0;
}
