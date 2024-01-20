#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Header.h"


int number_of_vertice_reader()
{ //To read no. of Vertices from the graph file.
	FILE* fp;
	char ch; //= " ";
	int vertice_number = 0;

	fp = fopen("Circuit_graph_new.txt", "r");

	if (fp == NULL) return FAILURE; //Checking whether the file opens correctly.

	fscanf(fp, "%*s"); //Ignoring  the 1st line, since in the graph file 1st file indicates vertices names i.e "V1 V2 V3 V4 V5". 

	while (1) {  //counting no. of lines in the graph file assuming that values are entered in terms of square matrix.

		ch = getc(fp);

		if (ch == EOF)
			break;

		if (ch == '\n')
			vertice_number++; //no. of lines in the graph  file(Ignoring  the 1st line) gives the number of Vertices in the graph. 
	}

	fclose(fp);
	return vertice_number;
}

Vertex_node* add_vertex_node(int vertex_no, int edge_weight)
{ //To Create a vertex node wrt given vertex_no & edge_weight
	Vertex_node* node;

	node = (Vertex_node*)malloc(sizeof(Vertex_node));

	if (node == NULL) return NULL;  //Checking for memory allocation

	node->vertex_no = vertex_no;    //adding vertex number
	node->edge_weight = edge_weight;//adding  edge weight
	node->next_vertex_ptr = NULL;

	return node;
}

Vertices_list* initilize_Vertices_list(int number_of_vertices) //To allocate memory and initialize "Vertices_list"
{
	Vertices_list* my_vertice_list;

	my_vertice_list = (Vertices_list*)malloc(number_of_vertices * sizeof(Vertices_list)); //Allocating memory for "Vertices_list"

	if (my_vertice_list == NULL) return NULL; //Checking for memory allocation

	for (int i = 0; i < number_of_vertices; i++) {

		//Initializing my_vertice_list[i] head & tail with "Vetex_node" pointer of each vertex
		my_vertice_list[i].head = my_vertice_list[i].tail = add_vertex_node(i + 1, -1); //adding "1" because index 'i" starts 0 and vertex number from "1"

		my_vertice_list[i].outgoing_edge_count = 0;// Setting default outgoing_edge_count,incoming_edge_coun & partitioned_status  as zero
		my_vertice_list[i].incoming_edge_count = 0;
		my_vertice_list[i].partitioned_status = 0;
	}

	return my_vertice_list;
}

int insert_connection_direct(Vertices_list* my_vertice_list) {


	Vertex_node* node;
	FILE* fp2;
	int number_of_vertices;
	int data;


	if (my_vertice_list == NULL) return FAILURE; //Checking whether "my_vertice_list" have been initialized or not

	number_of_vertices = number_of_vertice_reader(); //reading number of vertices


	fp2 = fopen("Circuit_graph_new.txt", "r"); //Checking whether the file opens correctly.
	if (fp2 == NULL) return FAILURE; //Checking whether the file opens correctly.


	fscanf(fp2, "%*s %*s %*s %*s %*s"); //Ignoring  the 1st line, since in the graph file 1st file indicates vertices names i.e "V1 V2 V3 V4 V5". 


	for (int row_no = 0; row_no < number_of_vertices; row_no++) {

		fscanf(fp2, "%*s"); /*Ignoring starting String which indicates  "Vertex Number" i.e. "V1.....
																							  V2......
																							  V3...... etc from graph file.*/


		for (int column_no = 0; column_no < number_of_vertices; column_no++) {

			fscanf(fp2, "%d", &data);  //reading the edge_weights from the file

			//printf("\n%d",data);

			if (data != 0) { //Ignoring '0', since  '0' denotes "NO CONNECTION b/w vertices or "SELF CONNECTION b/w same vertex.

				if (data < 0) //'-ve edge weights'  denotes "INCOMING" edges.
					my_vertice_list[row_no].incoming_edge_count++;

				else {

					//printf("%d%d\n", row_no, column_no);
					node = add_vertex_node(column_no + 1, data); //adding "1" because index 'column_no" starts 0 and vertex number from "1"

					//(NOTE : Similar to add_node_at_end in linked list)
					my_vertice_list[row_no].tail->next_vertex_ptr = node; //connecting the new "node" to the list
					my_vertice_list[row_no].tail = node;              //Updating the tail of the list.
					my_vertice_list[row_no].outgoing_edge_count++; //Increasing the outgoing egde count of given vertex;
				}

			}
		}
	}

	return 1;
}

Vertex_node* connected(Vertices_list* my_vertice_list) {
	int temp = 0, temp_index = 0, temp_in = 0, flag = 0;
	int number_of_vertices;

	number_of_vertices = number_of_vertice_reader(); //reads no.of Vertices from the graph file

	for (int i = 0; i < number_of_vertices; i++) {//NOTE: selecting a vertex can based on any criteria, code below returns the vertex with highest no. outgoing connections.

		if (my_vertice_list[i].partitioned_status == 0) { //checking if the vertices is partitioned or not, if not then assign the vertex to a partition group/cluster. 

			flag = 1;

			//Vertex with highest number of outgoing connection assigned partition group 1st.
			if (my_vertice_list[i].outgoing_edge_count >= temp) {

				if (my_vertice_list[i].outgoing_edge_count == temp) {
					//if two vetices have same number outgoing connection then the vetex with highest incoming connections are choosen.
					if (my_vertice_list[i].incoming_edge_count > temp_in) { //Assigning partition group/cluster to the Vertex
						temp = my_vertice_list[i].outgoing_edge_count;
						temp_in = my_vertice_list[i].incoming_edge_count;
						temp_index = i;
					}
					//if two vetices have same number outgoing connection and incoming connection then vertex that appears 1st in oreder is given preference. EX: V1,V2,V3....V1 appears before V2, hence V2 is assigned 1st.
				}

				else {
					//Assigning partition group/cluster to the Vertex
					temp = my_vertice_list[i].outgoing_edge_count;
					temp_in = my_vertice_list[i].incoming_edge_count;
					temp_index = i;
				}

			}

		}
	}

	if (flag) {
		my_vertice_list[temp_index].partitioned_status = 1; //indicates the vertexed has been assigned a partition group/cluster.
		return my_vertice_list[temp_index].head;  //returning the address of the partioned vertex.
	}
	else { //if all the vertex are partitioned off, then the flag bit isn't set to "1", 
		return NULL; // hence returning NULL inreturn saying that there's no more vertices left to be partitioned. 
	}

}


Partition_array* initilize_Partition_array(int number_of_clusters, int cluster_size)
{
	Partition_array* part_array;

	part_array = (Partition_array*)malloc(number_of_clusters * sizeof(Partition_array*)); //allocating memory to Partition array

	for (int i = 0; i < number_of_clusters; i++) {

		part_array[i].arr = (int*)malloc(cluster_size * sizeof(int)); //allocating memory to array
		part_array[i].vertex_count = 0;
	}

	return part_array;
}


Partition_array* cluster_growth_array(Vertices_list* my_vertice_list, int cluster_size)
{//Partitions vertices into different cluster as per of cluster_size required as per specified by the user and returns partitioned aarray_list
	Partition_array* part_array;
	Vertex_node* seed_node, * secondary_node;
	int number_of_vertices, number_of_clusters;

	number_of_vertices = number_of_vertice_reader();  //reads no.of Vertices from the graph file
	number_of_clusters = cluster_size_finder(number_of_vertices, cluster_size); //finding the number of clusters/partitions required as per number_of_vertices& cluster_size

	part_array = initilize_Partition_array(number_of_clusters, cluster_size); //intializing and allocating memory to part_array.

	for (int i = 0; i < number_of_clusters; i++) {

		seed_node = connected(my_vertice_list); //selecting a seed node based on criteria assigned in the "connected" function.
		part_array[i].arr[0] = seed_node->vertex_no; //adding seed_node to partition group/cluster as its 1st element 
		part_array[i].vertex_count++; //increasing vertex count in a partition group/cluster now that seed_node as been added.

		//Filling the cluster with other vertices
		for (int j = 0; j < cluster_size - 1; j++) { //NOTE: cluster_size is decremented by 1 here, since a element(seed_node) is already been added.

			secondary_node = connected(my_vertice_list); ////selecting a vertex based on criteria assigned in the "connected" function.

			if (secondary_node == NULL) //if all the vertices are partitioned off, "connected" function returns "NULL" hence indicating to stop the partition. 
				break;

			part_array[i].arr[j + 1] = secondary_node->vertex_no; //adding vertex to partition group/cluster,array index starts from 1 (since seed_node is already been added) hence "j+1" (j starts from "0")
			part_array[i].vertex_count++; //increasing vertex count in a partition group/cluster
		}

	}

	return part_array; //returning the partitioned aarray_list.
}


int display_partition(Partition_array* part_array, int number_of_clusters)
{ //Displays the vertices in thier respective clusters
	int number_of_vertices;

	number_of_vertices = number_of_vertice_reader(); //reads no.of Vertices from the graph file

	for (int i = 0; i < number_of_clusters; i++) {
		printf("\npart%d\n", i + 1);

		for (int j = 0; j < part_array[i].vertex_count; j++) {

			if (number_of_vertices == 0)
				break;
			printf("VertexNo %d\n", part_array[i].arr[j]);
			number_of_vertices--; //decreasing vertex count after printing
		}
	}

	return 0;
}


int cluster_size_finder(int number_of_vertices, int cluster_size)
{//Calculates number of clusters based on number of vertices and cluster_size required as per specified by the user
	double temp; //ceil() function takes double as input argument
	long a;

	temp = (double)number_of_vertices / (double)cluster_size;

	a = (long)temp;
	

	return a;
}
