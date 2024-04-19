#ifndef _ALG_H
#define _ALG_H
#include <stdio.h>
#include "lab.h"
#include "stos.h"
#include "postac.h"
#include "kolejka.h"
int dfs(labirynt_t*, char*, int, int, FILE*);
int bfs(labirynt_t*, char*, int, int);
#endif
