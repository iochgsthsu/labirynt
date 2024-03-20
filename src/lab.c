#include <stdio.h>
#include <stdlib.h>
#include "lab.h"
#include "postac.h"


labirynt_t* utworz_labirynt(char* nazwa_pliku) //uzyskuje informacje o labiryncie i alokuje pamiec
{
	labirynt_t* lbr = (labirynt_t*) malloc(sizeof(labirynt_t));
	if(lbr == NULL)
	{
		return NULL;
	}

	FILE* plik = fopen(nazwa_pliku, "r");
	if(plik==NULL)
	{
		return NULL;
	}
	
	int ilosc_kolumn = 0, ilosc_wierszy = 0;
	int p[2];
	int k[2];
	char c;
	while((c = fgetc(plik)) != EOF)
	{
		if(c != '\n')
		{
			ilosc_kolumn++;
		}
		else
		{
			ilosc_wierszy++;
			ilosc_kolumn = 0;
		}

		if(c == 'P')
		{
			p[0] = ilosc_wierszy+1;
			p[1] = ilosc_kolumn;
		}
		else if(c == 'K')
		{
			k[0] = ilosc_wierszy+1;
			k[1] = ilosc_kolumn;
		}
	}

	rewind(plik);
	while((c = fgetc(plik)) != '\n')
	{
		ilosc_kolumn++;

	}

	lbr->poczatek[0] = p[0];
	lbr->poczatek[1] = p[1];
	lbr->koniec[0] = k[0];
	lbr->koniec[1] = k[1];
	lbr->wiersze = ilosc_wierszy;
	lbr->kolumny = ilosc_kolumn;
	
	lbr->data = (char**) malloc(DATA_WIERSZE*sizeof(char*));
	if(lbr->data == NULL)
	{
		fprintf(stderr, "utworz_labirynt: nie udalo sie przydzielic pamieci\n");
		return NULL;
	}
	for(int i = 0; i<DATA_WIERSZE; i++)
	{
		lbr->data[i] = malloc(DATA_KOLUMNY*sizeof(char));
		if(lbr->data[i] == NULL)
		{
			fprintf(stderr, "utworz_labirynt: nie udalo sie przydzielci pamieci \n");
			return NULL;
		}
	}

	
	fclose(plik);

	return lbr;


}

void wczytaj_czesc(labirynt_t* l, char* nazwa_pliku, postac_t* p) // wczytuje czesc ktora jest potrzebna
{
	if(l == NULL)
	{
		fprintf(stderr, "wczytaj_czesc: labirynt nie mogl zostac wczytany\n");
		return;
	}
	FILE* plik = fopen(nazwa_pliku, "r");
	if(plik == NULL)
	{
		fprintf(stderr, "wczytaj_czesc: nie mozna otworzyc pliku\n");
		return;

	}

	int koniec = 0;
	char t;
	for(int i = 0; i<DATA_WIERSZE; i++)
	{	
		fseek(plik, (p->x/DATA_WIERSZE)*(l->kolumny+1)*DATA_WIERSZE + (p->y/DATA_KOLUMNY) * DATA_KOLUMNY + i*(l->kolumny+1), SEEK_SET);
		if(koniec == 0)
		{
			for(int j = 0; j<DATA_KOLUMNY; j++)
			{
				t = fgetc(plik);
				if(t == 'X' || t == ' ' || t == 'P' || t == 'K')
				{
					l->data[i][j] = t;
				}	
				else if(t == '\n')
				{
					for(int k = j; k<DATA_KOLUMNY; k++)
					{
						l->data[i][k] = 'X';
					}	
					break;
				}
				else if(t == EOF)
				{
					koniec = 1;
					for(int k = j; k<DATA_KOLUMNY; k++)
					{
						l->data[i][k] = 'X';
					}
					break;

				}
			}
		}
		else if( koniec == 1)
		{

			for(int j = 0; j<DATA_KOLUMNY; j++)
			{
				l->data[i][j] = 'X';
			}

		}

	}

	fclose(plik);
	return;


}

void zwolnij_czesc(labirynt_t* l)
{
	for(int i = 0; i< DATA_KOLUMNY; i++)
	{
		free(l->data[i]);
	}
	free(l->data);
}

void wypisz_czesc(labirynt_t* l) 
{
	if(l == NULL)
	{
		fprintf(stderr, "wypisz_czesc: nie mozna wypisac labiryntu\n");
		return;
	}

	for(int i = 0; i<DATA_WIERSZE; i++)
	{
		for(int j = 0; j<DATA_KOLUMNY; j++)
		{
			fprintf(stdout, "%c", l->data[i][j]);

		}

		fprintf(stdout, "\n");
	}
	return ;
}

void labirynt_informacje(labirynt_t* l)
{
	if(l == NULL)
	{
		printf("labirynt_informacje: nie mozna uzyskac informacji");
		return;
	}
	printf("Ilosc wierszy: %d\nIlosc kolumn: %d\nPoczatek: (%d,%d)\nKoniec: (%d,%d)\n", l->wiersze, l->kolumny, l->poczatek[0], l->poczatek[1], l->koniec[0], l->koniec[1]);

}

void zapisz_czesc(labirynt_t* l, char* nazwa)
{
	FILE* plik = fopen(nazwa, "w");
	if(plik == NULL)
	{
		fprintf(stderr, "zapisz_czesc: nie mozna zapisac pliku\n");
		return;
	}
	for(int i = 0; i<DATA_WIERSZE; i++)
	{
		for(int j = 0; j<DATA_KOLUMNY; j++)
		{
			fprintf(plik, "%c", l->data[i][j]);
	
		}
		fprintf(plik, "\n");
	}


	fclose(plik);
	return;


}

int numer_czesci(labirynt_t* l, postac_t* p)
{
	int x = p->x / DATA_WIERSZE;
	int y = p->y / DATA_KOLUMNY;
	int czescy = l->kolumny / DATA_KOLUMNY;
	return (x*czescy)+(y+1);
}

void usun_czesc(char* nazwa)
{
	if(remove(nazwa) != 0)
	{
		fprintf(stderr, "usun_czesc: nie mozna usunac pliku\n");
		return;
	}

	return;
}
