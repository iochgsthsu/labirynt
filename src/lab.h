#ifndef _LBR_H
#define _LBR_H
#include "postac.h"

typedef struct labirynt{
	int wiersze; //ilosc wierszy
	int kolumny; // ilosc kolumn
	int poczatek[2]; //wiersz i kolumna poczatku
       	int koniec[2];	// wiersz i kolumna konca
	char** data;
} labirynt_t;

labirynt_t* utworz_labirynt(char* nazwa_pliku);
void wczytaj_czesc(labirynt_t* l, char* nazwa_pliku, postac_t* p);
void wypisz_czesc(labirynt_t* l);
void zwolnij_czesc(labirynt_t* l);
void labirynt_informacje(labirynt_t* l);




#endif
