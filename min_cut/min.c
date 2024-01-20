
#include <stdlib.h>
#include <stdio.h>
#include "min.h"
/*
Hash* initialize_hash(int vertex_count)
{
	// our first line of file will have vertex count

	Hash *hash;
	int i;

	hash = (Hash *)malloc(sizeof(Hash)*vertex_count);
	for(i=0; i<vertex_count; i++)
	{
	hash[i].ptr = (Vlist *)malloc(sizeof(Vlist));
	hash[i].ptr->head = hash[i].ptr->tail = NULL;
	hash[i].ptr->count = 0; 	
	}

	return hash;

}



Vertex* get_vertex(int vertex_no, int ic)
{
	Vertex *new;

	new = (Vertex *)malloc(sizeof(Vertex));
	new->vertex_no = vertex_no;
	new->ic = ic;
	new->ptr = NULL;

	return new;
}

int insert_from_file(Hash *hash1, Hash *hash2)
{
	FILE *fp;
	int vertex_no, ic;
	int vertex_count;


	// for hash 1

	// second line of the file will have all the vertex numbers in that list

	fp = fopen("hash1.txt", "r");
	fscanf(fp,"%d", &vertex_count);

	int vertex_arr[vertex_count];

	fscanf(fp, "%d%d%d",&vertex_arr[0], &vertex_arr[1], &vertex_arr[2] );
	for(int i=0; i<vertex_count; i++)
	{
		hash1[i].vertex_no = vertex_arr[i];
	}


	fclose(fp);

}

int search(Hash *hash, int vertex_count, int vertex_no)
{
	
	for(int i=0; i<vertex_count; i++)
	{
		if(hash[i].vertex_no == vertex_no )
			return FOUND;
	}
	return NOT_FOUND;
}*/


Hash* initialize_hash(int vertex_count)
{
	// our first line of file will have vertex count

	Hash *hash;
	int i;

	hash = (Hash *)malloc(sizeof(Hash)*vertex_count);
	for(i=0; i<vertex_count; i++)
	{
	hash[i].ptr = (Vlist *)malloc(sizeof(Vlist));
	hash[i].ptr->head = hash[i].ptr->tail = NULL;
	hash[i].ptr->count = 0; 	
	}

	return hash;

}

Vertex* get_vertex(int vertex_no, int ic)
{
	Vertex *new;

	new = (Vertex *)malloc(sizeof(Vertex));
	new->vertex_no = vertex_no;
	new->ic = ic;
	new->ptr = NULL;

	return new;
}

void display_hash(Hash *hash, int vertex_count)
{	
	int i;
	for(i=0; i<vertex_count; i++)
	{
		printf("vertex_no :%d\n", hash[i].vertex_no );
	}

}


int insert_connection(Vlist *vlist,int vertex_no,int ic  )
{

	Vertex *new;

	new = get_vertex(vertex_no, ic);
	if(vlist->head == NULL)
	{
		vlist->head = vlist->tail = new;	
	}
	else
	{
		vlist->tail->ptr = new;
		vlist->tail = new;
	}
	vlist->count++;
	return 1;
}

int insert_from_file(Hash *hash1, Hash *hash2)
{
	FILE *fp1, *fp2;
	int vertex_no, ic;
	int vertex_count1, vertex_count2, i;
	char ch;
	char ver1[2], ver2[2];
	int k=0;
	//int ecount=0,icount=0;


	// for hash 1

	// second line of the file will have all the vertex numbers in that list

	fp1 = fopen("hash1.txt", "r");
	fp2 = fopen("hash2.txt", "r");

	fscanf(fp1, "%d", &vertex_count1);
	fscanf(fp2, "%d", &vertex_count2);


	int vertex_arr1[vertex_count1], vertex_arr2[vertex_count2];

	fscanf(fp1, "%d%d%d",&vertex_arr1[0], &vertex_arr1[1], &vertex_arr1[2] );
	fscanf(fp2, "%d%d%d",&vertex_arr2[0], &vertex_arr2[1], &vertex_arr2[2] );

	for(i=0; i<vertex_count1; i++)
	{
		hash1[i].vertex_no = vertex_arr1[i];
		hash2[i].vertex_no = vertex_arr2[i];

	}


	fclose(fp1);
	fclose(fp2);

	fp1 = fopen("hash1.txt", "r");
	while((ch = fgetc(fp1)) !='\n');
	while((ch = fgetc(fp1)) !='\n');

	while(!(feof(fp1)))
	{
		fscanf(fp1, "%s%s", ver1, ver2 );
		for(i=0; i<vertex_count1; i++)
		{	

			if(atoi(&ver1[1]) == hash1[i].vertex_no)
			{
				if(search(hash1, vertex_count1,atoi(&ver2[1]) ))
				{
					ic = 1;
					
					
				}
				else
				{
					ic = 0;
				}
				insert_connection(hash1[i].ptr, atoi(&ver2[1]), ic);
			}
			
			
		}
	}
	fp2 = fopen("hash2.txt", "r");
	while((ch = fgetc(fp2)) !='\n');
	while((ch = fgetc(fp2)) !='\n');

	while(!(feof(fp2)))
	{
		fscanf(fp2, "%s%s", ver1, ver2 );
		for(i=0; i<vertex_count2; i++)
		{	
			
			if(atoi(&ver1[1]) == hash2[i].vertex_no)
			{
				if(search(hash2, vertex_count2,atoi(&ver2[1]) ))
					ic = 1;
				else
					ic = 0;
				insert_connection(hash2[i].ptr, atoi(&ver2[1]), ic);
			}
			
			
		}
	}

	

	fclose(fp1);
	fclose(fp2);
	return 1;

}

int search(Hash *hash, int vertex_count, int vertex_no)
{
	int i;
	for(i=0; i<vertex_count; i++)
	{
		if(hash[i].vertex_no == vertex_no )
			return FOUND;
	}
	return NOT_FOUND;
}


int display_connection_list(Hash *hash, int vertex_count)
{	
	Vertex *temp;
	int i;
	for(i=0; i<vertex_count; i++)
	{	printf("main Vertex : %d\n", hash[i].vertex_no);
		for(temp = hash[i].ptr->head; temp!=NULL; temp= temp->ptr)
			printf("Vertex no: %d, IC = %d\t", temp->vertex_no, temp->ic);
	}
	return 1;
}


int gain(Hash *hash1, Hash *hash2,int vertex_no1, int vertex_no2, int vertex_count)
{
	// assumption vertex 1 will be in hash1
	// and vertex 2 will be in hash2
	int i;
	int EC1 = 0, IC1 = 0, EC2 = 0, IC2 = 0, CIJ=0;
	Vertex *temp;
	int Gain, D1, D2;

	for(i=0; i<vertex_count; i++)
	{
		if(hash1[i].vertex_no == vertex_no1)
		{
			for(temp = hash1[i].ptr->head; temp!= NULL; temp = temp->ptr)
			{	
				if(temp->vertex_no == vertex_no2)
				{
					CIJ = 1;
				}
				if(temp->ic == 0)
					EC1++;
				else
					IC1++;
			}
		}
	}
	for(i=0; i<vertex_count; i++)
	{
		if(hash2[i].vertex_no == vertex_no2)
		{
			for(temp = hash2[i].ptr->head; temp!= NULL; temp = temp->ptr)
			{
				if(temp->ic == 0)
					EC2++;
				else
					IC2++;
			}
		}
	}

	printf("EC1 : %d, IC1 : %d EC2 : %d, IC2 : %d, CIJ : %d ", EC1, IC1, EC2, IC2, CIJ);

	D1 = EC1-IC1;
	D2 = EC2 - IC2;
	Gain = D1+D2-2*CIJ;

	printf("\ngain : %d\n", Gain);

	return 1;

}

