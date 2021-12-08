#include <stdio.h>
#include <stdlib.h>

#include "tools.h"

void tools_memory_init(void)
{
	GLOBAL_MEMORY = 0; 
}

void* tools_malloc(int alloc)
{
	void* ptr = malloc(alloc); 
	GLOBAL_MEMORY += alloc;
	return ptr;  
}

void tools_free(void* ptr, int alloc)
{
	free(ptr);
	GLOBAL_MEMORY -= alloc; 
}

void tools_check_at_end_of_app(void)
{
	if(GLOBAL_MEMORY != 0)
		fprintf(stderr, "Il y a une fuite de memoire de %d octe\n", GLOBAL_MEMORY); 
}



int string_to_int(char* str)
{
	int result = 0, i;

	for(i = 0; str[i] != '\0'; i ++)
	{
		result *= 10; 
		result += str[i] - 48;


	}	

	return result; 
}

int char_to_int(char c)
{	
	int result = 0;

	result += c - 48;


	return result;
}


