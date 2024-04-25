#include "lab.h"
#include "alg.h"
#include "stos.h"
#include "kolejka.h"
#include "io.h"
#include "postac.h"
#include "komorka.h"
#include "stos.h"
#include <stdio.h>
#include <stdlib.h>

int bfs(labirynt_t* l, char* nazwa, int w, int k)
{
	int r,c;
	int nr_lk = 0;
	kmk_t km;
	kmk_t dodajk;
	l->data[w%DATA_WIERSZE][k%DATA_KOLUMNY] = 'O';
	km.x = w;
	km.y = k;
	kolejka_t* kol = NULL;
	stos_t* stos = NULL;
	kol = k_dodaj(kol, km);
	while(kol!=NULL)
	{
	
	//	wypiszelementy(kol);
		km = przod(kol);
		kol = k_usun(kol);
	//	wypiszelementy(kol);
		
		for(int i = 0; i<4; i++)
		{
			if(i==0){
				r = km.x-1;
				c = km.y;

			}
			else if(i==1){
				r = km.x;
				c = km.y+1;

			}
			else if(i==2){
				r = km.x+1;
				c = km.y;

			}
			else if(i==3){
				r = km.x;
				c = km.y-1;
			}
	
			int tw = r%DATA_WIERSZE;
			int tk = c%DATA_KOLUMNY;
			zamien_czesc(l,r,c,nazwa);
			char t = l->data[tw][tk];
	
			if(t == ' ' || t == 'K')
			{
				dodajk.x = r;
				dodajk.y = c;
				stos = dodaj(stos, dodajk, km);
				if(t == 'K')
				{
					nr_lk++;
					stos = stos_do_pliku(stos, nr_lk);
					return nr_lk;
				}
				l->data[tw][tk] = 'O';
				kol = k_dodaj(kol, dodajk);

			}

			if(ilosc_stos(stos) == MAX_STOS)
			{
				nr_lk++;
				stos = stos_do_pliku(stos, nr_lk);

			}		
		}
	}
	// nie znaleziono sciezki
	return -nr_lk;


}





