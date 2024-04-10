#ifndef _LBR_H
#define _LBR_H
#include "postac.h"

//wielkosc wczytywanego labiryntu
#define DATA_WIERSZE 64
#define DATA_KOLUMNY 64

typedef struct labirynt{
	int wiersze; //ilosc wierszy
	int kolumny; // ilosc kolumn
	int poczatek[2]; //wiersz i kolumna poczatku
       	int koniec[2];	// wiersz i kolumna konca
	char** data; // czesc labiryntu
	int nrc; // numer aktualnej czesci
} labirynt_t;

labirynt_t* utworz_labirynt(char* nazwa_pliku);
void zwolnij_lab(labirynt_t* l);
void labirynt_informacje(labirynt_t* l);
int numer_czesci(labirynt_t* l, int, int);
void ustawpk(labirynt_t*, char*);

#endif
