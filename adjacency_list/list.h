#define SUCCESS 1
#define FAILURE 0

typedef struct _node_ Node;
struct _node_
{
	int vertex_no;
	int edge_weight;
	Node *ptr;
};

typedef struct _list_ List;
struct _list_
{
	Node *head,*tail;
	int num_connections;
	int partitioned_status;
};

int vertices_counter();

List * initialise_list();

Node * add_node(int vertex_no,int edge_weight);

int add_connections (List *);

void display_list(List* adj_list);
