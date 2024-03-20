#ifndef _LBR_H
#define _LBR_H
#include "postac.h"

//wielkosc wczytywanego labiryntu
#define DATA_WIERSZE 128
#define DATA_KOLUMNY 128

typedef struct labirynt{
	int wiersze; //ilosc wierszy
	int kolumny; // ilosc kolumn
	int poczatek[2]; //wiersz i kolumna poczatku
       	int koniec[2];	// wiersz i kolumna konca
	char** data; // czesc labiryntu
} labirynt_t;

labirynt_t* utworz_labirynt(char* nazwa_pliku);
void wczytaj_czesc(labirynt_t* l, char* nazwa_pliku, postac_t* p);
void wypisz_czesc(labirynt_t* l);
void zwolnij_czesc(labirynt_t* l);
void labirynt_informacje(labirynt_t* l);
void zapisz_czesc(labirynt_t* l, char*);
void usun_czesc(char* nazwa);
int numer_czesci(labirynt_t* l, postac_t* p);




#endif
