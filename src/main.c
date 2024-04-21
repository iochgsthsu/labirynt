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
	int pomoc = 0;
	while((opcja = getopt(argc, argv, "i:o:h")) != -1)
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
			case 'h':
			{
				pomoc = 1;
				printf("%s: Opis parametrow\n Program obsluguje dane parametry:\n-o NAZWAPLIKU -> Wczytanie labiryntu z pliku o nazwie NAZWAPLIKU\n-i NAZWAPLIKU -> Zapis kroków rozwiązania labiryntu do pliku o nazwie NAZWAPLIKU\nPrzyklad: ./labirynt -i maze -o maze_kroki\n",argv[0]);

			}

			default:
			{
				break;
			}
		}
	}
	int spr = sprawdz_format(nazwa_wczytanie);
	labirynt_t* l = NULL;
	if(spr == 0)
	{
		fprintf(stderr,"%s: Nieprawidlowy format pliku\n", argv[0]);
		return 1;
	}
	else if(spr == 1)
	{
		l = utworz_labirynt(nazwa_wczytanie);
	}
	else if(spr == 2)
	{
		l = wczytajbininfo(nazwa_wczytanie);
		return 0;
	}
		
	int czystdout = 0;
	if(pomoc == 1)
	{
		return 0;
	}
	if(nazwa_zapis == NULL)
	{
		czystdout = 1;
	}
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
//	wczytajbin(nazwa_wczytanie);
//	labirynt_informacje(l);
	int il_tk;
	if(spr==1)
	{
		wczytaj_czesc(l, nazwa_wczytanie, p->x, p->y);
		l->nrc = numer_czesci(l, p->x, p->y);
		il_tk = bfs(l, nazwa_wczytanie, (p->x-1), (p->y-1));
	}
	else if(spr==2)
	{

	}
	

//	wypisz(st);
	


//	dfs(l, nazwa_wczytanie, l->koniec[0]-1, l->koniec[1]-1, zktmp);

	zrobsciezke(l, il_tk, TMP_KROKI_R);
	odwroc(TMP_KROKI_R, TMP_KROKI);
	if(czystdout == 0)
	{
		zapiszkroki(nazwa_zapis, TMP_KROKI);
	}
	else
	{
		zapiszkrokiout(TMP_KROKI);
	}
	usun_czesci(l);
	usun_czesc(TMP_KROKI);
	usun_czesc(TMP_KROKI_R);
	usun_kroki(il_tk);
	//usun_czesc(LISTA);
	zwolnij_postac(p);
	zwolnij_lab(l);
	
	return 0;
}
