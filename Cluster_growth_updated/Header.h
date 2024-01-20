#define _CRT_SECURE_NO_WARNINGS
#define SUCCESS 1
#define FAILURE 0



typedef struct _vertex_node_ Vertex_node;
struct _vertex_node_ {

	int vertex_no;
	int edge_weight;
	Vertex_node* next_vertex_ptr;
};

typedef struct _vertices_list_ Vertices_list;
struct _vertices_list_ {

	Vertex_node* head;
	Vertex_node* tail;
	int outgoing_edge_count; //to store no. of  outgoing connections
	int incoming_edge_count; //to store no. of  incoming connections
	int partitioned_status; //Specifies wheter a particular edge is partitioned or not 

};


typedef struct _partition_array_ Partition_array;
struct _partition_array_ { //Array list to store the partioned vertices

	int* arr;
	int vertex_count; //indicates number of vertex in each partition

};

int number_of_vertice_reader(); //To read no. of Vertices from the graph file. (NOTE: The 1st line of the graph file gives the no. of vertices)

Vertices_list* initilize_Vertices_list(int number_of_vertices); //To allocate memory and initialize "Vertices_list"

Vertex_node* add_vertex_node(int vertex_no, int edge_weight); //To Create a vertex node wrt given vertex_no & edge_weight

int insert_connection_direct(Vertices_list* my_vertice_list); //Mapping the values directly to adjacentcy list

Vertex_node* connected(Vertices_list* my_vertice_list); //returns the node with highest no. outgoing connections

Partition_array* cluster_growth_array(Vertices_list* my_vertice_list, int cluster_size); //Partitions vertices into different cluster as per of cluster_size required as per specified by the user and returns partitioned aarray_list

Partition_array* initilize_Partition_array(int number_of_clusters, int cluster_size); //To allocate memory and initialize "Partition_array"

int display_partition(Partition_array* part_array, int number_of_clusters); //Displays the vertices in thier respective clusters.

int cluster_size_finder(int number_of_vertices, int number_of_clusters); //Calculates number of clusters based on number of vertices and cluster_size required as per specified by the user
