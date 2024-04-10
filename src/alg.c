#include "lab.h"
#include "stos.h"
#include "kolejka.h"
#include "io.h"
#include "postac.h"
#include "komorka.h"
#include "stos.h"
#include <stdio.h>
#include <stdlib.h>


int dfs(labirynt_t* l, char* nazwa, int w, int k, FILE* zapisk)
{
	
	int tw = w%DATA_WIERSZE;
	int tk = k%DATA_KOLUMNY;

//	wypisz_czesc(l);
	zamien_czesc(l, w, k, nazwa);
	char t = l->data[tw][tk];

//	printf("\n(%d, %d)\nczesc: %d\nt: %c\n", w, k, l->nrc, t);

	if(t == 'P')
	{
		return 1;
	}
	else if( t == 'b' || t == 'K')
	{
		l->data[tw][tk] = 'd';
		if(dfs(l, nazwa, w+1, k, zapisk))
		{
			fprintf(zapisk, "GORA\n");
			return 1;
		}
		if(dfs(l, nazwa, w, k+1, zapisk))
		{
			fprintf(zapisk, "LEWO\n");
			return 1;
		}
		if(dfs(l, nazwa, w-1, k, zapisk))
		{
			fprintf(zapisk, "DOL\n");
			return 1;
		}
		if(dfs(l, nazwa,  w, k-1, zapisk))
		{
			fprintf(zapisk, "PRAWO\n");
			return 1;
		}
	}

	return 0;
}

stos_t* bfs(labirynt_t* l, char* nazwa, int w, int k)
{
	int r,c;
	kmk_t km;
	l->data[w%DATA_WIERSZE][k%DATA_KOLUMNY] = 'b';
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
		//	wypisz_czesc(l);
		//	wypiszelementy(kol);
		//	printf("\n(%d, %d)\nczesc: %d\ntw:%d, tk:%d\nt:%c\nkm.x:%d km.y:%d\n", r, c, l->nrc,tw,tk,t,km.x,km.y);
		//	printf("\n/////////////////////////////////\n");
			if(t == ' ' || t == 'K')
			{
				kmk_t dodajk;
				dodajk.x =r;
				dodajk.y = c;
				stos = dodaj(stos, dodajk, km);
				if(t == 'K')
				{
					printf("bfs: koniec odnaleziony\n");
					return stos;
				}
				l->data[tw][tk] = 'b';
				kol = k_dodaj(kol, dodajk);

			}	
		}
	}
	
		

	return NULL;


}






