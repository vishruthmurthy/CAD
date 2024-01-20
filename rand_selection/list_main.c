#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"


int main()
{
	List *test;
	int count;


	test = initialise_list();

	assert(vertices_counter() == 6);

	add_connections (test);
	
	display_list(test);

    	//random_split(test ,4);

	random_split_group(test ,3);
	
	return 0;
}





