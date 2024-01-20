#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Header.h"


void test_adjacency_list();
void test_connected();

int main() {

	test_adjacency_list();
	test_connected();

}

void test_adjacency_list() {

	int number_of_vertices;
	Vertices_list* my_vertice_list;
	Vertex_node* node;


	number_of_vertices = number_of_vertice_reader();

	assert(number_of_vertices == 5);

	my_vertice_list = initilize_Vertices_list(number_of_vertices);

	assert(insert_connection_direct(my_vertice_list));

	assert(my_vertice_list[0].head->vertex_no == 1);
	assert(my_vertice_list[0].head->next_vertex_ptr->edge_weight == 2);
	assert(my_vertice_list[0].head->next_vertex_ptr->next_vertex_ptr->vertex_no == 3);
	assert(my_vertice_list[0].head->next_vertex_ptr->next_vertex_ptr->edge_weight == 5);
	assert(my_vertice_list[0].outgoing_edge_count == 3);
	assert(my_vertice_list[0].incoming_edge_count == 0);


	assert(my_vertice_list[1].head->next_vertex_ptr == NULL);
	assert(my_vertice_list[1].outgoing_edge_count == 0);
	assert(my_vertice_list[1].incoming_edge_count == 2);

	assert(my_vertice_list[2].head->next_vertex_ptr->vertex_no == 2);
	assert(my_vertice_list[2].head->next_vertex_ptr->edge_weight == 3);
	assert(my_vertice_list[2].outgoing_edge_count == 1);
	assert(my_vertice_list[2].incoming_edge_count == 3);

	assert(my_vertice_list[3].head->vertex_no == 4);
	assert(my_vertice_list[3].outgoing_edge_count == 2);
	assert(my_vertice_list[3].incoming_edge_count == 1);

	assert(my_vertice_list[4].head->vertex_no == 5);
	assert(my_vertice_list[4].outgoing_edge_count == 1);
	assert(my_vertice_list[3].incoming_edge_count == 1);
}

void test_connected()
{
	int number_of_vertices, number_of_clusters;
	Vertices_list* my_vertice_list;
	Vertex_node* node;
	Partition_array* part_array;


	number_of_vertices = number_of_vertice_reader();

	assert(number_of_vertices == 5);

	my_vertice_list = initilize_Vertices_list(number_of_vertices);

	assert(insert_connection_direct(my_vertice_list));

	part_array = cluster_growth_array(my_vertice_list, 3);

	assert(part_array[0].vertex_count == 3);
	//assert(part_array[1].vertex_count == 1);
printf("-------%d",part_array[1].vertex_count);

	number_of_clusters = cluster_size_finder(number_of_vertices, 3);

	display_partition(part_array, number_of_clusters);


}
