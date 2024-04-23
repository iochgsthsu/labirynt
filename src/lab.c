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

	ilosc_kolumn = 0;

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





void labirynt_informacje(labirynt_t* l)
{
	if(l == NULL)
	{
		fprintf(stderr, "labirynt_informacje: nie mozna uzyskac informacji");
		return;
	}
	printf("Ilosc wierszy: %d\nIlosc kolumn: %d\nPoczatek: (%d,%d)\nKoniec: (%d,%d)\n", l->wiersze, l->kolumny, l->poczatek[0], l->poczatek[1], l->koniec[0], l->koniec[1]);

}


int numer_czesci(labirynt_t* l, int w, int k)
{
	if(l == NULL)
	{
		fprintf(stderr, "numer_czesci: nie mozna przetworzyc danych\n");
		return 1;
	}
	int y = l->kolumny/DATA_KOLUMNY;
	if(l->kolumny%DATA_KOLUMNY != 0)
	{
		y+=1;
	}
	return (w/DATA_WIERSZE)*y + k/DATA_KOLUMNY +1;


}

void zwolnij_lab(labirynt_t* l)
{
	if(l == NULL)
	{
		fprintf(stderr, "zwolnij_lab: dany labirynt to null\n");
		return;
	}
	free(l->data);
	free(l);
}





