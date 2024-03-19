#include "lab.h"
#include "stos.h"
#include <stdio.h>
int dfs(labirynt_t* l, int w, int k)
{	

	char t = l->data[w][k];
	//printf("(%d, %d) ", w, k);

	if(t == 'K')
	{
		return 1;
	}
	else if( t == ' ' || t == 'P')
	{
		l->data[w][k] = 'O';
		if(dfs(l, w+1, k))
		{
			printf("DOL\n");
			return 1;
		}
		if(dfs(l, w, k+1))
		{
			printf("PRAWO\n");
			return 1;
		}
		if(dfs(l, w-1, k))
		{
			printf("GORA\n");
			return 1;
		}
		if(dfs(l, w, k-1))
		{
			printf("LEWO\n");
			return 1;
		}
	}

	return 0;


		
}
