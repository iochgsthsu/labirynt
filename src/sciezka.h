#ifndef SCIEZKA_H
#define SCIEZKA_H

#include "lab.h"
#include "stos.h"

void zrobsciezke(labirynt_t*, int,  char*);
void zapiszkroki(char* nazwa_zapis, char* nazwa_wczyt);
void odwroc(char*, char*);
void zapiszkrokiout(char* nazwa_wczyt);
void zapiszkrokibin(bin_t*, char*, char*);
int liczbakrokow(char* nazwa);

#endif
