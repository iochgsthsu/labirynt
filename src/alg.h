#ifndef _DFS_H
#define _DFS_H
#include <stdio.h>
#include "lab.h"
#include "stos.h"
#include "postac.h"
#include "kolejka.h"
int dfs(labirynt_t*, char*, int, int, FILE*);
stos_t* bfs(labirynt_t*, char*, int, int);


#endif
