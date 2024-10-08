#include<stdio.h>
#include<stdlib.h>

#include "graph.h"

int main() {
	Graph g = make_graph(10);
	add_capacity(&g, 2, 2, 8);
	print_graph(&g);
	free_graph(&g);
	return 0;
}
