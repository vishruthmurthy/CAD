

#include <stdio.h>
#include <stdlib.h>
#include "min.h"

int main()
{
	FILE *fp1, *fp2;
	int vertex_count1, vertex_count2;
	Hash *hash1, *hash2;

	fp1 = fopen("hash1.txt","r");
	fp2 = fopen("hash2.txt", "r");


	fscanf(fp1, "%d", &vertex_count1);
	fscanf(fp2, "%d", &vertex_count2);

	hash1 = initialize_hash(vertex_count1);
	hash2 = initialize_hash(vertex_count2);

	fclose(fp1);
	fclose(fp2);
	insert_from_file(hash1, hash2);

	display_hash(hash1, vertex_count1);
	printf("hash 2\n");
	display_hash(hash2, vertex_count2);

	display_connection_list(hash1, vertex_count1);
	printf("\nhash 2\n");
	display_connection_list(hash2, vertex_count2);

	gain(hash1, hash2,1, 5, 3 );
	return 0;

}
