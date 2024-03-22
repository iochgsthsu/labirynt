#ifndef _IO_H
#define _IO_H
#include "lab.h"
#include "postac.h"

void wczytaj_czesc(labirynt_t* l, char* nazwa_pliku, postac_t* p);
void wypisz_czesc(labirynt_t* l);
void zapisz_czesc(labirynt_t* l, char*);
void usun_czesc(char* nazwa);
void usun_czesci(labirynt_t* l);
int zamien_czesc(labirynt_t* l, postac_t* p, char* nazwa_pliku);


#endif
