#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"
//#include "list.c"


int main()
{
	List *test;
	int count;

	test = initialise_list();

	assert(vertices_counter() == 5);

	add_connections (test);

	display_list(test);

	return 0;
}
