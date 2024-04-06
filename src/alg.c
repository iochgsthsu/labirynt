#include "lab.h"
#include "stos.h"
#include "kolejka.h"
#include "io.h"
#include "postac.h"
#include "komorka.h"
#include <stdio.h>
#include <stdlib.h>
int dfs(labirynt_t* l, char* nazwa, int w, int k)
{
	
	int tw = w%DATA_WIERSZE;
	int tk = k%DATA_KOLUMNY;

//	wypisz_czesc(l);
	zamien_czesc(l, w, k, nazwa);
	char t = l->data[tw][tk];

//	printf("\n(%d, %d)\nczesc: %d\nt: %c\n", w, k, l->nrc, t);

	if(t == 'K')
	{
		return 1;
	}
	else if( t == ' ' || t == 'P')
	{
		l->data[tw][tk] = 'O';
		if(dfs(l, nazwa, w+1, k))
		{
			printf("DOL\n");
			return 1;
		}
		if(dfs(l, nazwa, w, k+1))
		{
			printf("PRAWO\n");
			return 1;
		}
		if(dfs(l, nazwa, w-1, k))
		{
			printf("GORA\n");
			return 1;
		}
		if(dfs(l, nazwa,  w, k-1))
		{
			printf("LEWO\n");
			return 1;
		}
	}

	return 0;
}

int bfs(labirynt_t* l, char* nazwa, int w, int k)
{
	int r,c;
	kmk_t km;
	l->data[w%DATA_WIERSZE][k%DATA_KOLUMNY] = 'O';
	km.x = w;
	km.y = k;
	kolejka_t* kol = NULL;
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
				if(t == 'K')
				{
					printf("bfs: koniec odnaleziony\n");
					return 1;
				}
				l->data[tw][tk] = 'O';
				kmk_t dodaj;
				dodaj.x = r;
			       	dodaj.y = c;
				kol = k_dodaj(kol, dodaj);	

			}	
		}
	}
	
		

	return 0;


}






