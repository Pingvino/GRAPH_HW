// ADT Graph
#include <stdio.h>
#include "ADT_llist.h"
#include "ADT_graph.h"

int main() {
	int i;
	GRAPH* graph = create_graph();
	int vertex[6] = {'A', 'B', 'C', 'D', 'E', 'F'};

	//vertex insertion test
	for(i = 0; i < 6; i++) {
		if(!g_insert_vertex(graph, vertex[i]))
			printf("graph vertex insersion failed: %c\n", (char)vertex[i]);
		else
			printf("graph vertex insersion ok: %c\n", (char)vertex[i]);
	}
	
	if(!g_insert_vertex(graph, 'C'))
		printf("graph vertex insersion failed: %c already exist\n", 'C');
	else
		printf("graph vertex insersion ok: %c\n", 'C');

	printf("\nGraph's Vertex:\n");
	print_vertex_all(graph);
	printf("\n");

	if(!g_delete_vertex(graph, 'B'))
		printf("graph vertex delete failed: %c\n", 'B');
	else
		printf("graph vertex delete ok: %c\n", 'B');

	printf("\nGraph's Vertex:\n");
	print_vertex_all(graph);
	printf("\n");

	//arc insertion test
	if(!insert_arc(graph, 'A', 'B'))
		printf("graph arc insertion failed: %c -> %c\n", 'A', 'B');
	else
		printf("graph arc insertion ok: %c -> %c\n", 'A', 'B');
	
	if(!g_insert_vertex(graph, 'B'))
		printf("graph vertex insersion failed: %c already exist\n", 'B');
	else
		printf("graph vertex insersion ok: %c\n", 'B');
// re-try arc insertion
	if(!insert_arc(graph, 'A', 'B'))
		printf("graph arc insertion failed: %c -> %c\n", 'A', 'B');
	else
		printf("graph arc insertion ok: %c -> %c\n", 'A', 'B');
	
	if(!insert_arc(graph, 'B', 'C'))
		printf("graph arc insertion failed: %c -> %c\n", 'B', 'C');
	if(!insert_arc(graph, 'B', 'E'))
		printf("graph arc insertion failed: %c -> %c\n", 'B', 'E');

	if(!insert_arc(graph, 'C', 'D'))
		printf("graph arc insertion failed: %c -> %c\n", 'C', 'D');
	if(!insert_arc(graph, 'C', 'E'))
		printf("graph arc insertion failed: %c -> %c\n", 'C', 'E');

	if(!insert_arc(graph, 'D', 'E'))
		printf("graph arc insertion failed: %c -> %c\n", 'D', 'E');

	if(!insert_arc(graph, 'E', 'F'))
		printf("graph arc insertion failed: %c -> %c\n", 'E', 'F');


	printf("\nGraph's Arc:\n");
	print_arc_all(graph);
	printf("\n");

	destroy_graph(graph);

	return 0;
}
