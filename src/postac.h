#ifndef _POSTAC_H
#define _POSTAC_H
typedef struct postac{
	int x; // nr wiersza
	int y; // nr kolumny
}postac_t;

postac_t* utworz_postac(int x, int y);
void zwolnij_postac(postac_t* p);
#endif
