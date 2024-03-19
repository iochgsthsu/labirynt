#ifndef _STOS_H
#define _STOS_H
typedef struct stos{
	char* data;
	struct stos* next;
	
} stos_t;
stos_t* utworz();
stos_t* dodaj(stos_t *s, char*);
stos_t* zdejmij(stos_t *s);
void wierzcholek(stos_t *s);
void wypisz(stos_t* s);
#endif
