#include "postac.h"
#include <stdlib.h>
#include <stdio.h>
postac_t* utworz_postac(int x, int y){

	postac_t* p = (postac_t*) malloc(sizeof(postac_t));
	if(p == NULL)
	{
		fprintf(stderr, "utworz_postac: nie udalo sie utworzyc postaci\n");
		return NULL;
	}
	p->x = x;
       	p->y = y;
	return p;
}

void aktualizacja(postac_t*p, int w, int k)
{

}

void zwolnij_postac(postac_t* p)
{
	free(p);
}
