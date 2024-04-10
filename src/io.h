#ifndef _IO_H
#define _IO_H
#define TMP_KROKI_R "zkrtmp"
#define TMP_KROKI "zktmp"

#include "lab.h"
#include "postac.h"

void wczytaj_czesc(labirynt_t* l, char* nazwa_pliku, int, int);
void wypisz_czesc(labirynt_t* l);
void zapisz_czesc(labirynt_t* l, char*);
void usun_czesc(char* nazwa);
void usun_czesci(labirynt_t* l);
int zamien_czesc(labirynt_t* l, int, int , char* nazwa_pliku);


#endif
