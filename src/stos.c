#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stos.h"
#include "komorka.h"

stos_t* utworz()
{
	stos_t* s = (stos_t*) malloc(sizeof(stos_t));
	if(s == NULL)
	{
		return NULL;
	}
	return s;

}
stos_t* dodaj(stos_t* s, kmk_t ob, kmk_t pop)
{
	stos_t* tmp = (stos_t*)malloc(sizeof(stos_t));
	if(tmp == NULL)
	{
		return NULL;
	}
	tmp->next = s;
	tmp->obec = ob;
	tmp->poprz = pop;
	return tmp;

}

stos_t* zdejmij(stos_t* s)
{
	if(s==NULL)
	{
		return NULL;
	}
	stos_t* tmp = malloc(sizeof(stos_t*));
	if(tmp == NULL)
	{
		return NULL;
	}
	tmp = s;
	tmp = tmp->next;
	free(s);
	return tmp;
}

void wierzcholek(stos_t* s)
{
	fprintf(stdout, "obecny: (%d,%d) poprzedni: (%d,%d)\n", s->obec.x, s->obec.y, s->poprz.x, s->poprz.y);
	return;
}

void wypisz(stos_t* s)
{
	stos_t* tmp = s;
	while(tmp != NULL)
	{
		printf("obecny: (%d,%d) poprzedni: (%d, %d)\n", tmp->obec.x, tmp->obec.y, tmp->poprz.x, tmp->poprz.y);
		tmp = tmp->next;
	}
	return;
}
