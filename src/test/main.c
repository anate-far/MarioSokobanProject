#include <stdio.h>
#include <stdlib.h>

#include "tools.h"

int main(int argc, char** argv)
{
	tools_memory_init();

	int** tab = NULL;
 	tab = tools_malloc(sizeof(int*) * 3);//y
	int i, j;

	for(i = 0; i < 3 ;i ++)
	{
		tab[i] = tools_malloc(sizeof(int) * 5);//x

	}
	

	for(i = 0; i < 3; i++)
	{
		for(j= 0; j < 5; j++)
		{
			tab[i][j] = 1;
			printf("%d", tab[i][j]);
		}

		printf("\n");
	}

	for(i = 0; i < 3; i ++)
	{
		for(j = 0; j < 5; j++)
			printf("%d", tab[i][j]);

		printf("\n");
	}

		


	for(i = 0; i < 3;i++)
	{
		tools_free(tab[i], sizeof(int) * 5);
	}
	tools_free(tab, sizeof(int*) * 3);



	
	
	tools_check_at_end_of_app();
	return 0; 
}

