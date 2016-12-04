#ifndef ADT_GRAPH
#define ADT_GRAPH

#include <stdio.h>
#include <stdlib.h>

// Vertex node
typedef struct vertex {
	int data;
	LLIST* arc_list;
} VERTEX;

// Arc node
typedef struct arc {
	struct vertex* to_vertex;
} ARC;

// GRAPH
typedef struct {
	LLIST* vertex_list;
} GRAPH;

// Inner Operations;
int compare_vertex(void* x, void* y);
void print_vertex(void* x);
int compare_arc(void* x, void* y);
void print_arc(void* x);

// Operations;
GRAPH* create_graph();
bool g_insert_vertex(GRAPH* graph, int data);
bool g_delete_vertex(GRAPH* graph, int data);
void print_vertex_all(GRAPH* graph);

bool g_insert_arc(GRAPH* graph, int from, int to);
bool g_delete_arc(GRAPH* graph, int from, int to);
bool insert_arc(GRAPH* graph, int from, int to);
bool delete_arc(GRAPH* graph, int from, int to);
void print_arc_all(GRAPH* graph);

#endif
