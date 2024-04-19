#include <stdio.h>
#include <stdlib.h>
#include "kolejka.h"
#include "komorka.h"
kolejka_t* k_dodaj(kolejka_t* k, kmk_t x){
	kolejka_t* nowy = (kolejka_t*)malloc(sizeof(kolejka_t));
	if(nowy == NULL)
	{
		fprintf(stderr, "k_dodaj: nie mozna dodac nowego elementu do kolejki\n");
		return NULL;
	}
	nowy->n = x;
	nowy->nast = k;
	k = nowy;
	return k;
}
kolejka_t* k_usun(kolejka_t* k)
{
	if(k == NULL)
	{
		fprintf(stderr, "k_usun: pusta kolejka\n");
		return NULL;
	}	
	kolejka_t* tmp = k;
	kolejka_t* poprz = NULL;
	while(tmp->nast != NULL){
		poprz = tmp;
		tmp = tmp->nast;
	}
	free(tmp);
	if(poprz == NULL)
	{
		k = NULL;
	}
	else
	{
		poprz->nast = NULL;
	}
	return k;
}
int czypusta(kolejka_t* k)
{
	if(k == NULL){
		return 1;
	}
	else{
		return 0;
	}

}
kmk_t przod(kolejka_t* k)
{
	kmk_t q;
	q.x = 0;
	q.y = 0;
	if(k == NULL)
	{
		fprintf(stderr, "przod: nie mozna odczytac wartosci\n");
		return q;
	}
	kolejka_t* tmp = k;
	while(tmp->nast !=NULL)
	{
		tmp = tmp->nast;
	}
	return tmp->n;
}

int ilosc_elementow(kolejka_t* k)
{
	if(k == NULL)
	{
		fprintf(stderr, "ilosc_elementow: nieprawidlowa kolejka\n");
		return -1;
	}
	int i = 0;
	kolejka_t* tmp = k;
	while(tmp->nast!=NULL)
	{
		i++;
		tmp = tmp->nast;
	}
	return i+1;
}

void wypiszelementy(kolejka_t* kol){
	if(kol == NULL)
	{
		fprintf(stdout,"[ ]\n");
		return;
	}
	kolejka_t* ktmp = kol;
	fprintf(stdout, "[ ");
	while(ktmp != NULL)
	{
		kmk_t kmk = ktmp->n;
		fprintf(stdout, "(%d, %d) ", kmk.x, kmk.y);
		ktmp = ktmp->nast;
	}
	fprintf(stdout, "]\n");
	return;

}
 
