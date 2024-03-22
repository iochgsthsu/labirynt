#include "lab.h"
#include "stos.h"
#include "io.h"
#include <stdio.h>
int dfs(labirynt_t* l, char* nazwa, int w, int k)
{
	
	
	int tw = w%DATA_WIERSZE;
	int tk = k%DATA_KOLUMNY;

//	wypisz_czesc(l);
	zamien_czesc(l, w, k, nazwa);
	char t = l->data[tw][tk];

//	printf("\n(%d, %d)\nczesc: %d\nt: %c\n", w, k, l->nrc, t);

	if(t == 'K')
	{
		return 1;
	}
	else if( t == ' ' || t == 'P')
	{
		l->data[tw][tk] = 'O';
		if(dfs(l, nazwa, w+1, k))
		{
			printf("DOL\n");
			return 1;
		}
		if(dfs(l, nazwa, w, k+1))
		{
			printf("PRAWO\n");
			return 1;
		}
		if(dfs(l, nazwa, w-1, k))
		{
			printf("GORA\n");
			return 1;
		}
		if(dfs(l, nazwa,  w, k-1))
		{
			printf("LEWO\n");
			return 1;
		}
	}

	return 0;


		
}


