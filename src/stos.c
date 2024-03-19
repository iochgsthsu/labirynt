#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stos.h"

stos_t* utworz()
{
	stos_t* s = (stos_t*) malloc(sizeof(stos_t));
	if(s == NULL)
	{
		return NULL;
	}
	return s;

}
stos_t* dodaj(stos_t* s, char* x)
{
	stos_t* tmp = (stos_t*)malloc(sizeof(stos_t));
	if(tmp == NULL)
	{
		return NULL;
	}
	tmp->next = s;
	tmp->data = malloc(32*sizeof(char));
	if(tmp->data == NULL)
	{
		return NULL;
	}
	strcpy(tmp->data, x);
	return tmp;

}

stos_t* zdejmij(stos_t* s)
{
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
	fprintf(stdout, "%s\t", s->data);
	return;
}

void wypisz(stos_t* s)
{
	stos_t* tmp = s;
	while(tmp != NULL)
	{
		printf("%s\n", tmp->data);
		tmp = zdejmij(tmp);
	}
	return;
}
