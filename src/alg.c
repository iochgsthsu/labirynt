#include "lab.h"
#include "stos.h"
#include "io.h"
#include <stdio.h>
int a = 0;
int dfs(labirynt_t* l, postac_t* p, char* nazwa, int w, int k)
{
	wypisz_czesc(l);
	zamien_czesc(l, p, nazwa);
	char t = l->data[w][k];
printf("\n(%d, %d)\n czesc: %d \n, t: %c\n", w, k, l->nrc, t);

	if(t == 'K')
	{
		return 1;
	}
	else if( t == ' ' || t == 'P')
	{
		l->data[w][k] = 'O';
		if(dfs(l, p, nazwa, w+1, k))
		{
			printf("DOL\n");
			return 1;
		}
		if(dfs(l, p, nazwa, w, k+1))
		{
			printf("PRAWO\n");
			return 1;
		}
		if(dfs(l, p, nazwa, w-1, k))
		{
			printf("GORA\n");
			return 1;
		}
		if(dfs(l, p, nazwa,  w, k-1))
		{
			printf("LEWO\n");
			return 1;
		}
	}

	return 0;


		
}


