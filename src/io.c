#include "lab.h"
#include "postac.h"
#include "komorka.h"
#include "stos.h"
#include "bin.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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

bin_t* wczytajbininfo(char* nazwa)
{
	FILE* plik = fopen(nazwa, "r");
	if(plik == NULL){
		fprintf(stderr, "wczytajbininfo: nie mozna otworzyc pliku\n");
		return NULL;
	}
	int fileid;
	char escape;
	short int columns;
	short int lines;
	short int entry_x;
	short int entry_y;
	short int exit_x;
	short int exit_y;
	int counter;
	int sollution_off;
	char separator;
	char wall;
	char path;
	fread(&fileid, 4, 1, plik);
	fread(&escape, 1, 1, plik);
	fread(&columns, 2, 1, plik);
	fread(&lines, 2, 1, plik);
	fread(&entry_x, 2, 1, plik);
	fread(&entry_y, 2, 1, plik);
	fread(&exit_x, 2, 1, plik);
	fread(&exit_y, 2, 1, plik);
	fseek(plik, 12, SEEK_CUR);
	fread(&counter, 4, 1, plik);
	fread(&sollution_off, 4, 1, plik);
	fread(&separator, 1, 1, plik);
	fread(&wall, 1, 1, plik);
	fread(&path, 1, 1, plik);

	//printf("FILEID: %d\nESCAPE: %d \nCOLUMNS: %d\nLINES: %d\nENTRY_X: %d\nENTRY_Y: %d\nEXIT_X: %d\nEXIT_Y:%d\nCOUNTER:%d \nSOLUTION_OFF: %d\nSEPARATOR: %c\nWALL: %c\nPATH: %c\n", fileid, escape, columns, lines, entry_x, entry_y, exit_x, exit_y, counter, sollution_off, separator, wall, path);
	fclose(plik);
	bin_t* b = malloc(sizeof(bin_t));
	b->fileid = fileid;
	b->escape = escape;
	b->columns = columns;
	b->lines = lines;
	b->entry_x = entry_x;
	b->entry_y = entry_y;
	b->exit_x = exit_x;
	b->exit_y = exit_y;
	b->counter = counter;
	b->sollution_off = sollution_off;
	b->separator = separator;
	b->wall = wall;
	b->path = path;
	return b;
		




}

void bin2text(bin_t* b, char* nazwa)
{
	FILE* bin = fopen(nazwa, "r");
	if(bin == NULL)
	{
		fprintf(stderr, "bin2text: nie mozna czytac pliku\n");
		return;
	}
	FILE* text = fopen(BIN2TEXT, "w");
	if(text == NULL)
	{
		fprintf(stderr, "bin2text: nie mozna pisac do pliku\n");
		return;
	}

	fseek(bin, 40, SEEK_SET);
	char separator;
	char value;
	uint8_t count;
	int nr_kolumny = 0;
	int nr_wiersza = 1;
	for(int i = 0; i<b->counter; i++)
	{
		fread(&separator, 1, 1, bin);
		fread(&value, 1, 1, bin);
		fread(&count, 1, 1, bin);
		for(int j = 0; j<count+1; j++)
		{
			if(nr_kolumny == b->columns)
			{
				nr_kolumny = 0;
				fprintf(text,"\n");
				nr_wiersza++;
			}

			if(nr_wiersza == b->entry_y && nr_kolumny == b->entry_x-1 )
			{
				fprintf(text, "P");
			}
			else if(nr_wiersza == b->exit_y && nr_kolumny == b->exit_x-1)
			{
				fprintf(text, "K");
			}
			else
			{

				if(value == b->wall)
				{
					fprintf(text, "%c", value);
				}
				else if(value == b->path)
				{
					fprintf(text, "%c", value);
				}
			}
			nr_kolumny++;

		}

		//printf("%c%c%d", separator, value, count);

	}
	fclose(text);
	fclose(bin);


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

void usun_kroki(int max_il_k)
{
	char* tmp = malloc(16*sizeof(char));
	for(int i = 1; i<max_il_k+1; i++)
	{
		sprintf(tmp, "tk%d", i);
		FILE * plik = fopen(tmp, "r");
		if(plik == NULL)
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

stos_t* stos_do_pliku(stos_t* s, int numer)
{
	if(s == NULL)
	{
		fprintf(stderr, "stos_do_pliku: nieprawidlowy stos\n");
		return NULL;
	}
	
	char* t  = malloc(16*sizeof(char));
	sprintf(t, "tk%d", numer);
	FILE* plik = fopen(t, "w");
	if(plik == NULL)
	{	
		fprintf(stderr, "stos_do_pliku: nie mozna pisac do pliku\n");
		return NULL;
	}
	kmk_t o, p;
	while(s!= NULL)
	{
		o = przod_obec(s);
		p = przod_poprz(s);
		fprintf(plik, "%hd %hd %hd %hd\n", o.x, o.y, p.x, p.y);
		s = zdejmij(s);

	}
	
		


	free(t);
	fclose(plik);
	return s;

}
int sprawdz_format(char* nazwa)
{
	if(nazwa == NULL)
	{
		fprintf(stderr, "sprawdz_format: nie prawidlowa nazwa\n");
		return 0;
	}
	FILE* plik = fopen(nazwa, "r");
	if(plik == NULL)
	{
		fprintf(stderr, "sprawdz_format: nie mozna otworzyc pliku\n");
		return 0;
	}
	char fileid[5];
	fread(&fileid, 4, 1, plik);
	fclose(plik);
	int cmp = strncmp(fileid, FILEID, 4);
	int il;
	if(cmp == 0)
	{
		return 2;
	}
	else
	{
		il = 0;
		for(int i = 0; i<4; i++)
		{
			if(fileid[i] == 'X' || fileid[i] == ' ' || fileid[i] == 'P' || fileid[i] == 'K')
			{
				il++;
			}
		}
	}
	if(il==4)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	return -1;


}

