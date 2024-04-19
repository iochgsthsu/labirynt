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
	/*
	stos_t* tmp = malloc(sizeof(stos_t*));
	if(tmp == NULL)
	{
		return NULL;
	}*/
	stos_t* tmp = s;
	/*
	tmp = s;
	tmp = tmp->next;
	*/
	s = s->next;
	free(tmp);
	return s;
}

kmk_t przod_obec(stos_t* s)
{
	kmk_t km;
	km.x = -1;
	km.y = -1;
	if(s== NULL)
	{
		return km;
	}
	return s->obec;
}
kmk_t przod_poprz(stos_t* s)
{
	kmk_t km;
	km.x = -1;
	km.y = -1;
	if(s == NULL)
	{
		return km;
	}
	return s->poprz;
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

int ilosc_stos(stos_t* s)
{
	int il = 0;
	if(s == NULL)
	{
		return - 1;
	}

	stos_t* tmp = s;
	while(tmp!= NULL)
	{
		il++;
		tmp = tmp->next;
	}
	return il;
}
