#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "list.h"

int vertices_counter()
{
	FILE *fp;
	int count = 0;
	char ch;

	fp = fopen("graph.txt","r");
	//fp = fopen("cad.txt", "r");

	if(fp == NULL ) printf("Erorr\n");

	//fscanf(fp , "%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s ");
	while((ch = fgetc(fp)) != '\n');

	ch = fgetc(fp);

	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch=='\n')
			count ++;
	}
	fclose(fp);
	return count;
}

//To Create a vertex node wrt given vertex_no & edge_weight

Node * add_node(int vertex_no,int edge_weight)
{
	Node* node;

	node = (Node*)malloc(sizeof(Node));

	//if (node == NULL) return FAILURE; //Checking for memory allocation

	node->vertex_no = vertex_no;
	node->edge_weight = edge_weight;
	node->ptr = NULL;

	return node;
}

List * initialise_list()
{
	List *adj_list;
	int vertex_count, i;

	vertex_count = vertices_counter();

	adj_list = (List*)malloc(vertex_count * sizeof(List));  //Allocating memory for "Vertices_list"

	if (adj_list == NULL) return NULL; //Checking for memory allocation

	//Initializing my_vertice_list[i] head & tail with "Vetex_node" pointer of each vertex
	for ( i = 0; i < vertex_count; i++) {

		adj_list[i].head = adj_list[i].tail = add_node(i + 1, 0); //adding "1" because index 'i" starts 0 and vertex number from "1"
		adj_list[i].num_connections = 0;
		adj_list[i].partitioned_status = 0; //By deafault no vertex is partitioned.
		//printf("list is %d",adj_list[i]->vertex_no);
	}


	return adj_list;
}

int add_connections (List * adj_list)
{
	Node* node;
	FILE* fp;
	int vertex_count,temp, i, j,k;
	char ch;

	vertex_count = vertices_counter();
	//printf("%d count",vertex_count);

	if (adj_list == NULL) return FAILURE;

	fp = fopen("graph.txt", "r");
	//fp = fopen("cad.txt", "r");

	if (fp == NULL) return FAILURE;

	//fscanf(fp, "%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s"); //Ignoring  the 1st line, since in the graph file 1st file indicates vertices names i.e "V1 V2 V3 V4 V5...".

	while((ch = fgetc(fp)) != '\n');

	for ( i = 0; i < vertex_count; i++)
	{

		fscanf(fp, "%*s"); /*Ignoring starting String which indicates  "Vertex Number" i.e. "V1.....
																							  V2......
																							  V3...... etc from graph file.*/

		for ( j = 0; j < vertex_count; j++)
		 {

			fscanf(fp, "%d", &temp);  //reading the data from the graph file

			if (temp != 0) { //if data read is zero "0", it means on connection or repeated connection since the grpah is un directed

					node = add_node(j + 1, temp);
					adj_list[i].tail->ptr = node; //adding "1" because index 'column_no" starts 0 and vertex number from "1"
					adj_list[i].tail = node;

					adj_list[i].num_connections++; //Increasing the connection count of given vertex;

			}
		}
	}//printf("%d connections",adj_list[i].num_connections);
fclose(fp);
}

void display_list(List* adj_list)
{
	/*int i , j,vertex_count;
	Node *temp;
	vertex_count = vertices_counter();

	for ( i = 1;i <= vertex_count;i++)
	{


		for (; temp!=NULL; temp = temp->ptr)
		{
			printf("%d vertex number",temp->vertex_no);
			printf("%d \n",temp->edge_weight);

		}
	}
*/

	int i, j, vertex_count;
	Node *temp;

	vertex_count = vertices_counter();
	for(i=0; i<vertex_count; i++)
	{
		temp = adj_list[i].head;
		if(adj_list[i].num_connections == 0){
		printf("Vetex %d has No connections\n", adj_list[i].head->vertex_no);
		continue;

		}
		printf("Vertex %d \t  connected to \n", i+1); // printf("Vertex %d", adj_list[i].head->vertex_no);


		for(j=0; j<adj_list[i].num_connections; j++)	// for(temp = adj_list[i].head->ptr; temp != NULL; temp= temp->ptr)
		{
			temp= temp->ptr;
			printf(" vertex %d, Edge Weight%d\n",temp->vertex_no, temp->edge_weight );

		}
	printf("\n");
	}




}

int random_split(List *adj_list,int no_ele)
 {
 	int i,j,k;
	int vertex_count;
 	vertex_count = vertices_counter();
 	int partion_vertices=0;
 	int cluster_size = ceil((float)vertex_count/(float) no_ele);
 	printf(" No of clusters is %d\n",cluster_size );

 	for(j=0;j<cluster_size;j++)
 	{
 		for(i=0;i<no_ele;i++)
 		{
 			k=rand()%vertex_count;
 			if(partion_vertices == vertex_count)
 				break;
 			if(adj_list[k+1].partitioned_status == 1)
			{
 				i--;
 				continue;
 			}

 			printf("cluster  = %d , selected vertices = %d\n",j,k+1);

 			adj_list[k+1].partitioned_status =1;
 			partion_vertices ++;
 		}
 	}

 	return 1;
}

 int random_split_group(List *adj_list,int no_group)
 {
 	int i,j,k;
 	int vertex_count;
 	vertex_count = vertices_counter();
 	int partion_vertices=0;
 	int Number_ele = ceil((float)vertex_count/(float) no_group);
 	printf(" Number of elements in group is %d\n",Number_ele );

 	for(j=0;j<Number_ele;j++)
 	{
 		for(i=0;i<no_group;i++)
 		{
 			k=rand()%vertex_count;
 			if(partion_vertices == vertex_count)
 				break;
 			if(adj_list[k+1].partitioned_status == 1)
			{
 				i--;
 				continue;
 			}

 			printf("cluster_block = %d , selected list = %d\n",i+1 ,k+1);
 			adj_list[k+1].partitioned_status =1;
			partion_vertices ++;
 		}
 	}

 	return 1;
 }






