#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stos.h"
#include "komorka.h"
#include "lab.h"


void zrobsciezke(labirynt_t* l, int tkmax, char* nazwa_zapis)
{
	kmk_t o, p;
	int dx, dy;
	int tpx, tpy;

	if(nazwa_zapis== NULL)
	{
		fprintf(stderr, "zrobsciezke: zla nazwa\n");
		return;
	}

	FILE* plik = fopen(nazwa_zapis, "w");
	if(plik == NULL)
	{
		fprintf(stderr,"zrobsciezke: nie mozna pisac do pliku\n");
		return;
	}
	int pcz = 0;
	int x;
	char* t = malloc(16*sizeof(char));
	for(int i = 0; i<tkmax; i++)
	{
		sprintf(t, "tk%d", tkmax-i);
		FILE* lista = fopen(t, "r");
		if(lista == NULL)
		{
			fprintf(stderr, "zrobsciezka: zla lista\n");
			return;
		}
		if(pcz == 0){
			x = fscanf(lista, "%hd %hd %hd %hd\n", &o.x, &o.y, &p.x, &p.y);
			pcz = 1;
		}
		while(1)
		{
			
		
		
		
			if(x!=EOF)
			{
				dx = o.x - p.x;
				dy = o.y - p.y;

				if(dx==1)
				{
					fprintf(plik, "D");
				}
				else if(dx==-1)
				{
					fprintf(plik, "G");
	
				}
				else if(dy==1)
				{
					fprintf(plik, "P");
	
				}
				else if(dy==-1)
				{
					fprintf(plik, "L");
				}
			
				if(tpx == l->poczatek[0]-1 && tpy == l->poczatek[1]-1)
				{
					break;
				}
				tpx = p.x;
				tpy = p.y;
			}
			
			while(o.x != tpx || o.y != tpy)
			{
				x = fscanf(lista, "%hd %hd %hd %hd\n", &o.x, &o.y, &p.x, &p.y);
				if(x==EOF)
				{
					break;
				}
			
			
			}
			if(x==EOF)
			{
				break;
			}
			
				
		}
		fclose(lista);	
		
	}
	
	fclose(plik);
	free(t);


	
}

void zapiszkroki(char* nazwa_zapis, char* nazwa_wczyt)
{
	FILE* wplik = fopen(nazwa_wczyt, "r");
	if(wplik == NULL)
	{	
		fprintf(stderr, "zapiszkroki: nie mozna otworzyc pliku\n");
		return;
	}
	int b;
	int bprev = 'T';

	FILE* zplik = fopen(nazwa_zapis, "w");
	if(zplik == NULL)
	{
		fprintf(stderr, "zapiszkroki: nie mozna pisac do pliku\n");
		return;
	}
	int kroki = 0;
	fprintf(zplik, "START\n");
	while((b = fgetc(wplik)) != EOF)
	{
		
			if(kroki!=0 && b!=bprev && bprev!= 'T')
			{
				fprintf(zplik,"FORWARD %d\n", kroki);
				if((bprev == 'G' && b == 'P') ||
				(bprev == 'P' && b == 'D') ||
				(bprev == 'D' && b == 'L') ||
				(bprev == 'L' && b == 'G')
				){
					fprintf(zplik,"TURNRIGHT\n");
				}
				else
				{
					fprintf(zplik,"TURNLEFT\n");
				}
				kroki = 0;
			}
		kroki++;

		bprev = b;
	}
	if(kroki!=0)
	{
		fprintf(zplik, "FORWARD %d\n",kroki);
	}

	fprintf(zplik, "END\n");

	fclose(zplik);
	fclose(wplik);

	return;


}

void zapiszkrokiout(char* nazwa_wczyt)
{
	FILE* wplik = fopen(nazwa_wczyt, "r");
	if(wplik == NULL)
	{	
		fprintf(stderr, "zapiszkroki: nie mozna otworzyc pliku\n");
		return;
	}
	int b;
	int bprev = 'T';

	
	int kroki = 0;
	fprintf(stdout, "START\n");
	while((b = fgetc(wplik)) != EOF)
	{
		
			if(kroki!=0 && b!=bprev && bprev!= 'T')
			{
				fprintf(stdout,"FORWARD %d\n", kroki);
				if((bprev == 'G' && b == 'P') ||
				(bprev == 'P' && b == 'D') ||
				(bprev == 'D' && b == 'L') ||
				(bprev == 'L' && b == 'G')
				){
					fprintf(stdout,"TURNRIGHT\n");
				}
				else
				{
					fprintf(stdout,"TURNLEFT\n");
				}
				kroki = 0;
			}
		kroki++;

		bprev = b;
	}
	if(kroki!=0)
	{
		fprintf(stdout, "FORWARD %d\n",kroki);
	}

	fprintf(stdout, "END\n");

	fclose(wplik);

	return;


}




void odwroc(char* nazwa_wczyt, char* nazwa_zapis)
{
	FILE* plikczytaj = fopen(nazwa_wczyt, "r");
	if(plikczytaj == NULL)
	{
		fprintf(stderr, "odwroc: nie mozna otworzyc pliku\n");
		return;
	}
	FILE *plikzapis = fopen(nazwa_zapis, "w");
	if(plikzapis == NULL)
	{
		fprintf(stderr, "plikzapis: nie mozna pisac do pliku\n");
		return;
	}
	char t;
	int n = 0;
	while((t = fgetc(plikczytaj)) !=EOF)
	{
		n++;
	}

	for(int i= 0; i<n; i++)
	{
	
		fseek(plikczytaj,-i-1,SEEK_END);
		t = fgetc(plikczytaj);
		fprintf(plikzapis, "%c", t);
	}



	fclose(plikczytaj);
	fclose(plikzapis);
}
