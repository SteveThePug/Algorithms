#include<stdio.h>
#include<stdlib.h>

#include "graph.h"
#include "list.h"
#include "array.h"

int main(int argc, char* argv[]) {
	int n = 10;
	int max = 5;

	if (argc > 1) {
		n=atoi(argv[1]);
	}

	if (argc > 2) {
		max = atoi(argv[2]);
	}

	// Using gdb, you can inspect the values using breakpoints
	// call print_array(int*, n)
	// call print_graph(Graph* g)
	Graph* g = make_graph(n);
	randomize_graph(g, max);

	int len;
	Array* arr = vertex_neighbors(g, rand()%n);

	int u = rand()%n;
	int v = rand()%n;
	while (u == v) {
		v = rand()%n;
	}

	printf("Finding path from %d to %d\n", u, v);
	Array* bfs_path = bfs_find_path(g, u, v);
	Array* dfs_path = dfs_find_path(g, u, v);
	print_array(bfs_path);
	print_array(dfs_path);
	free_graph(g);
	free_array(bfs_path);
	free_array(dfs_path);

 	// List* l = make_list();	
 	// push(l, 1);
	// push(l, 2);
	// push(l, 3);
	// push(l, 4);
	// print_list(l);
	// printf("Pop: %d\n", pop(l));
	// printf("Dequeue: %d\n", dequeue(l));
	// print_list(l);
	// enqueue(l, 6);
	// push(l, 7);
	// print_list(l);
	// reverse_list(l);
	// free_list(l);

	return 0;
}
