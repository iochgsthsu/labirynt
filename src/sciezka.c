#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stos.h"
#include "komorka.h"
#include "lab.h"


void zrobsciezke(labirynt_t* l, stos_t* s, char* nazwa_zapis)
{
	kmk_t o, p;
	int dx, dy;
	
	if(s == NULL)
	{
		fprintf(stderr, "zrobsciezke: zly stos\n");
		return;
	}
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
	while(s != NULL)
	{

		o = s->obec;
		p = s->poprz;
		dx = o.x - p.x;
		dy = o.y - p.y;
	//	printf("o: (%d,%d) p: (%d,%d) dx: %d dy: %d\n", o.x, o.y, p.x, p.y, dx, dy);

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
		
		if(s->poprz.x == l->poczatek[0]-1 && s->poprz.y == l->poczatek[1]-1)
		{
			break;
		}


		while(p.x != s->obec.x || p.y != s->obec.y)
		{
			s = zdejmij(s);	
		}
		

		
		
	}

	fclose(plik);


	
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
	//	printf("b:%c bprev:%c kr:%d\n", b, bprev, kroki);
		
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
	//	printf("b:%c bprev:%c kr:%d\n", b, bprev, kroki);
		
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
