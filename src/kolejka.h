#ifndef _KOLEJKA_H
#define _KOLEJKA_H
#include "komorka.h"
typedef struct kolejka{
	kmk_t n;
	struct kolejka* nast;  
} kolejka_t;
kolejka_t* k_usun(kolejka_t* k);
kolejka_t* k_dodaj(kolejka_t*, kmk_t);
int czypusta(kolejka_t*);
kmk_t przod(kolejka_t* k);
void wypiszelementy(kolejka_t*);
#endif

