
#define FAILURE 0
#define SUCCESS 1

//Adjacency List
typedef struct _node_ Node;
struct _node_ {

	int vertex_no;
	int edge_weight;
	Node* next_ptr;
};

typedef struct _Vertex_list_ Vertex_list;
struct _Vertex_list_ {

	Node* head;
	Node* tail;
	int num_connection; //to store no. of  outgoing connections
	int partitioned_status; //Specifies wheter a particular edge is partitioned or not
};

int vertices_counter(); //To read no. of Vertices from the graph file.
Vertex_list* initialize_list(); //To allocate memory and initialize "Vertices_list"
Node* add_node(int vertex_no, int edge_weight); //To Create a vertex node wrt given vertex_no & edge_weight
int add_connections(Vertex_list* list); //Mapping the values directly to adjacentcy list


// Hierarchical clustering method Implementation

int hieararchical_clustering(Vertex_list* list, int num_partitions);
int merging_vertices(Vertex_list* list, int index1, int index2);
int clustering(Vertex_list* list);
int search_list(Vertex_list* list, int vertex_no);
int max_edgewieght(Vertex_list* list, int vertex_no);



