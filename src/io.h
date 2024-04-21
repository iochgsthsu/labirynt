#ifndef _IO_H
#define _IO_H
#include "stos.h"
#include "lab.h"
#define TMP_KROKI_R "zkrtmp"
#define TMP_KROKI "zktmp"
#define BIN2TEXT "tmpbintext"
#define MAX_STOS 2048
#define FILEID "CBRR"


#include "lab.h"
#include "postac.h"

void wczytaj_czesc(labirynt_t* l, char* nazwa_pliku, int, int);
void wypisz_czesc(labirynt_t* l);
void zapisz_czesc(labirynt_t* l, char*);
void usun_czesc(char* nazwa);
void usun_czesci(labirynt_t* l);
void usun_kroki(int);
int zamien_czesc(labirynt_t* l, int, int , char* nazwa_pliku);
labirynt_t* wczytajbininfo(char*);
stos_t* stos_do_pliku(stos_t*, int);
int sprawdz_format(char* nazwa); // 0 - niewlasciwy, 1 - tekstowy, 2 - binarny
void bin2text(char*);


#endif
