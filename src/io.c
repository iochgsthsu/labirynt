#include "lab.h"
#include "postac.h"
#include <stdio.h>
#include <stdlib.h>

void wczytaj_czesc(labirynt_t* l, char* nazwa_pliku, int w, int k) // wczytuje czesc ktora jest potrzebna
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
		fseek(plik, (w/DATA_WIERSZE)*(l->kolumny+1)*DATA_WIERSZE + (k/DATA_KOLUMNY) * DATA_KOLUMNY + i*(l->kolumny+1), SEEK_SET);
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

void wczytajbin(char* nazwa)
{
	FILE* plik = fopen(nazwa, "r");
	if(plik == NULL){
		fprintf(stderr, "bin2text: nie mozna otworzyc pliku\n");
		return;
	}
	char buf[4];
	size_t s = fread(buf, 4,1, plik);
	printf("%s\n", buf);
	fclose(plik);


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

void usun_czesc(char* nazwa)
{
	if(remove(nazwa) != 0)
	{
		fprintf(stderr, "usun_czesc: nie mozna usunac pliku\n");
		return;
	}

	return;
}


void usun_czesci(labirynt_t* l)
{

	int maxc = ((l->wiersze/DATA_WIERSZE)+1)*((l->kolumny/DATA_KOLUMNY)+1) ;
	char* tmp = malloc(16*sizeof(char));
	for(int i = 1; i< maxc+1; i++)
	{
		sprintf(tmp, "ltmp%d", i);
		FILE* plik = fopen(tmp, "r");
		if(plik==NULL)
		{
			continue;
		}	
		else
		{
			usun_czesc(tmp);
			fclose(plik);
		}
	}
	free(tmp);
	return;



}

int zamien_czesc(labirynt_t* l, int w, int k, char* nazwa_pliku)
{
	int n = numer_czesci(l, w, k);
	if(n != l->nrc)
	{

		char* tnazwa1 = malloc(16*sizeof(char));
		sprintf(tnazwa1, "ltmp%d", l->nrc);
		zapisz_czesc(l, tnazwa1);
		char* tnazwa2 = malloc(16*sizeof(char));
		l->nrc = n;
		sprintf(tnazwa2, "ltmp%d", l->nrc);
		FILE* tp = fopen(tnazwa2, "r");
		if(tp == NULL)
		{
			wczytaj_czesc(l,nazwa_pliku, w, k);
		}
		else
		{
			char t;
			for(int i =0; i<DATA_WIERSZE; i++)
			{
				for(int j = 0; j<DATA_KOLUMNY; j++)
				{
					t = fgetc(tp);
					if(t == '\n')
					{
						t = fgetc(tp);
					}
					l->data[i][j] = t;
				}
			}
			fclose(tp);



		}
		free(tnazwa1);
		free(tnazwa2);
		return 1;
	}
	else
	{
		return 0;
	}

}

