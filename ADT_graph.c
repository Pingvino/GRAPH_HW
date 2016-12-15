#include"ADT_llist.h"
#include"ADT_graph.h"

// Inner Operations
int compare_vertex(void* x, void* y){
	VERTEX* left = (VERTEX*)x;
	VERTEX* right = (VERTEX*)y;

	return left->data - right->data;
}
void print_vertex(void* x){
	VERTEX* vertex = (VERTEX*)x;
	printf("vertex: %c\n", (char)vertex->data);
}
int compare_arc(void* x, void* y){
	ARC* left = (ARC*)x;
	ARC* right = (ARC*)y;

	return compare_vertex(left->to_vertex, right->to_vertex);
}
void print_arc(void* x){
	ARC* arc = (ARC*)x;
	printf("         -> : %c\n", (char)arc->to_vertex->data);
}

// Operations
GRAPH* create_graph(){
	GRAPH* graph = (GRAPH*)malloc(sizeof(GRAPH));
	graph->vertex_list = create_list(compare_vertex, print_vertex);
	return graph;
}

bool g_insert_vertex(GRAPH* graph, int data){
	int* datat = &data;
	int vertex_loc = find_data(graph->vertex_list, datat);
	if(vertex_loc != -1)
		return false;
	// Creating Vertex
	VERTEX* new_vertex = (VERTEX*)malloc(sizeof(VERTEX));
	new_vertex->data = data;
	new_vertex->arc_list = create_list(compare_arc, print_arc);

	// Inserting Vertex into list
	return add_node_at(graph->vertex_list, graph->vertex_list->count,
	new_vertex);
}
bool g_delete_vertex(GRAPH* graph, int data){
	int* datat = &data;
	VERTEX* temp_vertex;
	ARC* temp_arc;
	int vertex_loc = find_data(graph->vertex_list, datat);
	if(vertex_loc == -1)
		return false;
	temp_vertex = (VERTEX*)get_data_at(graph->vertex_list, vertex_loc);

	while(temp_vertex->arc_list->count !=0) {
		ARC* reverse_arc =
		(ARC*)get_data_at(temp_vertex->arc_list, 0);
		int another_vertex_data =  reverse_arc->to_vertex->data;

		delete_arc(graph, data, another_vertex_data);
	}
	destroy_list(temp_vertex->arc_list);

	free(temp_vertex);
	del_node_at(graph->vertex_list, vertex_loc);
}
void print_vertex_all(GRAPH* graph){
	VERTEX* vertex_now;
	for(int iter_i = 0;
	iter_i < graph->vertex_list->count; iter_i++) {
		vertex_now = (VERTEX*)get_data_at(graph->vertex_list, iter_i);
		printf(" - ");
		print_vertex(vertex_now);
	}
}

bool g_insert_arc(GRAPH* graph, int from, int to){
	// Searching from vertex
	VERTEX tmp_vertex1;
	tmp_vertex1.data = from;
	tmp_vertex1.arc_list = NULL;

	int vertex_loc = find_data(graph->vertex_list, &tmp_vertex1);
	if(vertex_loc == -1) {
		printf("from_vertex %c: not found\n", (char)from);
		return false; // error, there is no from vertex
	}

	// Getting a VERTEX with 'from' data
	VERTEX* from_vertex = (VERTEX*)get_data_at(graph->vertex_list,
	vertex_loc);

	// Searching to vertex
	VERTEX tmp_vertex2;
	tmp_vertex2.data = to;
	tmp_vertex2.arc_list = NULL;

	vertex_loc = find_data(graph->vertex_list, &tmp_vertex2);
	if(vertex_loc == -1) {
		printf("to_vertex %c: not found\n", (char)to);
		return false; // Nothing found
	}

	// Getting a VERTEX with 'from' data
	VERTEX* to_vertex = (VERTEX*)get_data_at(graph->vertex_list,
	vertex_loc);

	// Creating destination
	ARC* new_arc = (ARC*)malloc(sizeof(ARC));
	new_arc->to_vertex = to_vertex;

	// Inserting vertex into list
	return add_node_at(from_vertex->arc_list,
	from_vertex->arc_list->count, new_arc);
}

bool g_delete_arc(GRAPH* graph, int from, int to){
	// Searching from vertex
	VERTEX tmp_vertex1;
	int tempto = to;

	tmp_vertex1.data = from;
	tmp_vertex1.arc_list = NULL;

	int vertex_loc = find_data(graph->vertex_list, &tmp_vertex1);
	if(vertex_loc == -1) {
		printf("from_vertex %c: not found\n", (char)from);
		return false; // error, there is no from vertex
	}

	// Getting a VERTEX with 'from' data
	VERTEX* from_vertex = (VERTEX*)get_data_at(graph->vertex_list,
	vertex_loc);

	// Searching to vertex
	VERTEX tmp_vertex2;
	tmp_vertex2.data = from;
	tmp_vertex2.arc_list = NULL;

	vertex_loc = find_data(graph->vertex_list, &tmp_vertex2);
	if(vertex_loc == -1) {
		printf("to_vertex %c: not found\n", (char)tempto);
		return false; // Nothing found
	}

	int iter_i = 0;
	while(iter_i < from_vertex->arc_list->count) {
		ARC* to_arc = (ARC*)get_data_at(from_vertex
		->arc_list, iter_i);
		int todata = to_arc->to_vertex->data;
		if(compare_arc(&tempto, to_arc) == 0 )
			break;
	}

	// Inserting vertex into list
	return del_node_at(from_vertex->arc_list, iter_i);
}

bool insert_arc(GRAPH* graph, int from, int to) {
	return g_insert_arc(graph, from, to)&&g_insert_arc(graph, to, from);
}
bool delete_arc(GRAPH* graph, int from, int to) {
	return g_delete_arc(graph, from, to)&&g_delete_arc(graph, to, from);
}

void print_arc_all(GRAPH* graph){
	VERTEX* vertex_now;
	ARC* arc_now;
	for(int iter_i = 0;
	iter_i < (graph->vertex_list->count); iter_i++) {
		vertex_now = (VERTEX*)get_data_at(graph->vertex_list, iter_i);
		print_vertex(vertex_now);
		for(int iter_j = 0;
		iter_j < (vertex_now->arc_list->count); iter_j++){
			arc_now = (ARC*)get_data_at(vertex_now->arc_list, iter_j);
			print_arc(arc_now);
		}
	}
}

void destroy_graph(GRAPH* graph) {
	while(graph->vertex_list->count != 0) {
		VERTEX* v_temp = (VERTEX*)graph->vertex_list->front->data_ptr;

		while(v_temp->arc_list->count != 0) {
			ARC* arc_temp = (ARC*)v_temp->arc_list->front->data_ptr;
			free(arc_temp);
			del_node_at(v_temp->arc_list, 0);
		}

//		printf("\nlol\n");
//		print_arc_all(graph);
//		printf("\nlolol\n");
		free(v_temp->arc_list);
		free(v_temp);
		del_node_at(graph->vertex_list, 0);
	}

	free(graph->vertex_list);
	free(graph);
}
