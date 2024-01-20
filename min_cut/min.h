
#define NOT_FOUND 0
#define FOUND 1


typedef struct _vertex_ Vertex;
typedef struct _v_list_ Vlist;
typedef struct _hash_table_ Hash;


struct _hash_table_
{
	int vertex_no;

	struct _v_list_ *ptr;
};

struct _vertex_
{
	int vertex_no;
	int ic;	// ic = 1 internal, ic =0 external
	struct _vertex_ *ptr;

};


struct _v_list_
{
	struct _vertex_ *head, *tail;
	int count;
};

Hash* initialize_hash(int vertex_count);
Vertex* get_vertex(int vertex_no, int ic);
void display_hash(Hash *hash, int vertex_count);
int insert_connection(Vlist *vlist,int vertex_no,int ic  );
int insert_from_file(Hash *hash1, Hash *hash2);
int search(Hash *hash, int vertex_count, int vertex_no);
int display_connection_list(Hash *hash, int vertex_count);
int gain(Hash *hash1, Hash *hash2,int vertex_no1, int vertex_no2, int vertex_count);

