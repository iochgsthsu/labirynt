#include "lab.h"
#include "alg.h"
#include "postac.h"
#include "stos.h"
#include "io.h"
#include "sciezka.h"
#include "kolejka.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main(int argc, char** argv)
{
	int opcja;
	char* nazwa_zapis;
	char* nazwa_wczytanie;
	while((opcja = getopt(argc, argv, "i:o:")) != -1)
	{
		switch(opcja)
		{
			case 'i':
			{
				nazwa_wczytanie = optarg;
				break;
			}
			case 'o':
			{
				nazwa_zapis = optarg;
				break;
			}
			default:
			{
				break;
			}
		}
	}
	labirynt_t* l = utworz_labirynt(nazwa_wczytanie);
	if(l == NULL)
	{
		fprintf(stderr, "%s: Nie mozna otworzyc pliku\n", argv[0]);
		return 1;
	}
	postac_t* p = utworz_postac(l->poczatek[0], l->poczatek[1]);
	if(p == NULL)
	{
		fprintf(stderr, "%s: Nie mozna utworzyc postaci\n", argv[0]);
		return 1;
	}
	labirynt_informacje(l);
	wczytaj_czesc(l, nazwa_wczytanie, p->x, p->y);
	l->nrc = numer_czesci(l, p->x, p->y);
	stos_t* st = bfs(l, nazwa_wczytanie, (p->x-1), (p->y-1));

//	wypisz(st);
	

	ustawpk(l, nazwa_wczytanie);

//	dfs(l, nazwa_wczytanie, l->koniec[0]-1, l->koniec[1]-1, zktmp);

	zrobsciezke(l, st, TMP_KROKI_R);
	odwroc(TMP_KROKI_R, TMP_KROKI);
	zapiszkroki(nazwa_zapis, TMP_KROKI);
	usun_czesci(l);
	usun_czesc(TMP_KROKI);
	usun_czesc(TMP_KROKI_R);
	zwolnij_postac(p);
	zwolnij_lab(l);
	return 0;
}
