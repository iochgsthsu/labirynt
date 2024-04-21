#include "lab.h"
#include "postac.h"
#include "komorka.h"
#include "stos.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/*void wczytajbin(char* nazwa)
{
	FILE* plik = fopen(nazwa, "r");
	if(plik == NULL){
		fprintf(stderr, "bin2text: nie mozna otworzyc pliku\n");
		return;
	}
	char fileid[4];
	char escape[1];
	char columns[2];
	char lines[2];
	char entry_x[2];
	char entry_y[2];
	char exit_x[2];
	char exit_y[2];
	char reserved[12];
	char counter[4];
	char sollution_off[4];
	char separator[1];
	char wall[1];
	char path[1];
	size_t s0 = fread(fileid, 4, 1, plik);
	size_t s1 = fread(escape, 1, 1, plik);
	size_t s2 = fread(columns, 2, 1, plik);
	size_t s3 = fread(lines, 2, 1, plik);
	size_t s4 = fread(entry_x, 2, 1, plik);
	size_t s5 = fread(entry_y, 2, 1, plik);
	size_t s6 = fread(exit_x, 2, 1, plik);
	size_t s7 = fread(exit_y, 2, 1, plik);
	size_t s8 = fread(reserved, 12, 1, plik);
	size_t s9 = fread(counter, 4, 1, plik);
	size_t s10 = fread(sollution_off, 4, 1, plik);
	size_t s11 = fread(separator, 1, 1, plik);
	size_t s12 = fread(wall, 1, 1, plik);
	size_t s13 = fread(path, 1, 1, plik);
	printf("%c, %c///", lines[0], lines[1]);

	printf("%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s", fileid, escape, columns, lines, entry_x, entry_y, exit_x, exit_y, reserved, counter, sollution_off, separator, wall, path);
	fclose(plik);


}*/

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

