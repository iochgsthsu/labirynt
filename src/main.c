#include "lab.h"
#include "alg.h"
#include "postac.h"
#include "stos.h"
#include "io.h"
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
//	labirynt_informacje(l);
	wczytaj_czesc(l, nazwa_wczytanie, p->x, p->y);
	l->nrc = numer_czesci(l, p->x, p->y);
	dfs(l, nazwa_wczytanie, (p->x-1), (p->y-1));
//	wypisz_czesc(l);
	usun_czesci(l);
	zwolnij_postac(p);
	zwolnij_lab(l);
	return 0;
}
