#ifndef _STOS_H
#define _STOS_H
#include "komorka.h"
typedef struct stos{
	kmk_t obec;
	kmk_t poprz;
	struct stos* next;
	
} stos_t;
stos_t* utworz();
stos_t* dodaj(stos_t *s, kmk_t obec, kmk_t poprz);
stos_t* zdejmij(stos_t *s);
void wierzcholek(stos_t *s);
void wypisz(stos_t* s);
#endif
