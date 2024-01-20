#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"


int vertices_counter()
{
	FILE* fp;
	int count = 0;
	char ch;

	fp = fopen("E:\\Program Files\\Microsoft Visual Studio\\Source\\CAD_Lab_test\\graph.txt", "r");

	if (fp == NULL) return FAILURE; //Checking whether the file opens correctly.

	fscanf(fp, "%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s"); //Ignoring  the 1st line, since in the graph file 1st file indicates vertices names i.e "V1 V2 V3 V4 V5....".

	ch = getc(fp);

	while (ch != EOF) { //counting no. of lines in the graph file assuming that values are entered in terms of square matrix.

		if (ch == '\n')
			count++; //no. of lines in the graph  file(Ignoring  the 1st line) gives the number of Vertices in the graph

		ch = getc(fp);
	}

	fclose(fp);
	//printf("%d", count);
	return count;
}


Node* add_node(int vertex_no, int edge_weight)
{//To Create a vertex node wrt given vertex_no & edge_weight
	Node* node;

	node = (Node*)malloc(sizeof(Node));

	if (node == NULL) return FAILURE; //Checking for memory allocation

	node->vertex_no = vertex_no;
	node->edge_weight = edge_weight;
	node->next_ptr = NULL;

	return node;
}

Vertex_list* initialize_list()
{
	Vertex_list* list;
	int vertex_count;

	vertex_count = vertices_counter();

	list = (Vertex_list*)malloc(vertex_count * sizeof(Vertex_list));  //Allocating memory for "Vertices_list"

	if (list == NULL) return FAILURE; //Checking for memory allocation

	//Initializing my_vertice_list[i] head & tail with "Vetex_node" pointer of each vertex
	for (int i = 0; i < vertex_count; i++) {

		list[i].head = list[i].tail = add_node(i + 1, 0); //adding "1" because index 'i" starts 0 and vertex number from "1"
		list[i].num_connection = 0;
		list[i].partitioned_status = 0; //By deafault no vertex is partitioned.
	}


	return list;
}

int add_connections(Vertex_list* list)
{
	Node* node;
	FILE* fp;
	int vertex_count, temp;

	vertex_count = vertices_counter();

	if (list == NULL) return FAILURE;

	fp = fopen("E:\\Program Files\\Microsoft Visual Studio\\Source\\CAD_Lab_test\\graph.txt", "r");

	if (fp == NULL) return FAILURE;

	fscanf(fp, "%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s"); //Ignoring  the 1st line, since in the graph file 1st file indicates vertices names i.e "V1 V2 V3 V4 V5...". 

	for (int i = 0; i < vertex_count; i++) {

		fscanf(fp, "%*s"); /*Ignoring starting String which indicates  "Vertex Number" i.e. "V1.....
																							  V2......
																							  V3...... etc from graph file.*/

		for (int j = 0; j < vertex_count; j++) {

			fscanf(fp, "%d", &temp);  //reading the data from the graph file

			if (temp != 0) { //if data read is zero "0", it means on connection or repeated connection since the grpah is un directed

				node = add_node(j + 1, temp);
				list[i].tail->next_ptr = node; //adding "1" because index 'column_no" starts 0 and vertex number from "1"
				list[i].tail = node;

				list[i].num_connection++; //Increasing the connection count of given vertex;

			}
		}
	}

	return 0;
}

int hieararchical_clustering(Vertex_list* list, int num_partitions)
{
	int vertex_count, partition_size;
	int max_wieght = 0, cluster_no = 0, index1 = 0, index2 = 0;
	Node* temp;

	if (list == NULL) return FAILURE; //Checking if memory is intialized or not

	vertex_count = vertices_counter();

	for (int j = 0; j < num_partitions; j++) {

		for (int i = 0; i < vertex_count; i++) {

			temp = list[i].head->next_ptr;

			for (; temp != NULL; temp = temp->next_ptr) {

				if (temp->edge_weight > max_wieght) { //Finding the connection with max wieght
					max_wieght = temp->edge_weight;
					index1 = temp->vertex_no; //storing the vertex no. of vertices with max edge wieght
					index2 = list[i].head->vertex_no;
				}
			}

		}

		cluster_no = index1 * 10 + index2;

		printf("V%d\n", cluster_no);

		merging_vertices(list, index1, index2);
	}


	//printf("%d %d %d", max_wieght, index1, index2);



	return 0;
}

int merging_vertices(Vertex_list* list, int index1, int index2)
{
	if (list == NULL) return FAILURE; //Checking if memory is intialized or not

	int temp,temp_wieght;
	Node* temp1, * temp2;

	if (list[index2 - 1].num_connection > list[index1 - 1].num_connection) { //if Vertex with index2 has more connections then swap the index1, so the we can add(merge) smaller list to the bigger list

		temp = index1;
		index1 = index2;
		index1 = temp;
	}

	temp1 = list[index2 - 1].head->next_ptr; // to traverse the list
	//temp2 = list[index1 - 1].head;

	for (; temp1 != NULL; temp1 = temp1->next_ptr) {

		temp = (temp1->vertex_no);

		if (list[temp - 1].partitioned_status == 1) { //if vertex is already merged then skip iteration

			continue;
		}

		if (search_list((list + index1 - 1), temp1->vertex_no)) {

			temp_wieght = temp1->edge_weight;

			max_edgewieght(list, temp1->vertex_no); //if 2 list have connection to the same vertices, choose the vertex with grater max_edgewieght
		}

	}


	return 0;
}

int search_list(Vertex_list* list, int vertex_no)
{
	if (list == NULL) return FAILURE; //Checking if memory is intialized or not

	Node* temp;

	temp = list->head->next_ptr;

	for (; temp != NULL; temp = temp->next_ptr) {

		if (temp->vertex_no == vertex_no)
			return SUCCESS;
	}
	return FAILURE;
}

int max_edgewieght(Vertex_list* list, int vertex_no)
{
	return 0;
}