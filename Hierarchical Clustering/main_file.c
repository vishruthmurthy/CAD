#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Header.h"


void test_adajacency_list();
void test_hieararchical_clustering();

int main() {
	//test_adajacency_list();
	test_hieararchical_clustering();
}

void test_adajacency_list() {

	Vertex_list* list;

	assert(vertices_counter() == 10);

	list = initialize_list();

	assert(list[0].head->vertex_no == 1);
	assert(list[1].head->vertex_no == 2);
	assert(list[2].head->vertex_no == 3);
	assert(list[3].head->vertex_no == 4);
	assert(list[4].head->vertex_no == 5);
	assert(list[5].head->vertex_no == 6);
	assert(list[6].head->vertex_no == 7);
	assert(list[7].head->vertex_no == 8);
	assert(list[8].head->vertex_no == 9);
	assert(list[9].head->vertex_no == 10);

	add_connections(list);


	assert(list[0].head->next_ptr == NULL);
	assert(list[1].head->next_ptr->vertex_no == 1);
	assert(list[2].head->next_ptr->vertex_no == 2);
	assert(list[3].head->next_ptr->vertex_no == 3);
	assert(list[4].head->next_ptr->vertex_no == 3);
	assert(list[5].head->next_ptr->vertex_no == 3);
	assert(list[6].head->next_ptr->vertex_no == 5);
	assert(list[6].head->next_ptr->next_ptr->vertex_no == 6);
	assert(list[7].head->next_ptr->vertex_no == 7);
	assert(list[8].head->next_ptr->vertex_no == 5);
	assert(list[9].head->next_ptr->vertex_no == 4);

	assert(list[1].head->next_ptr->edge_weight == 5);

	assert(search_list(list + 7, 7));


}

void test_hieararchical_clustering()
{
	Vertex_list* list;

	assert(vertices_counter() == 10);

	list = initialize_list();

	add_connections(list);

	hieararchical_clustering(list, 3);
}