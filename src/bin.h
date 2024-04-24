#ifndef _BIN_H
#define _BIN_H
#include <stdint.h>
typedef struct bin{
	
	int fileid;
	char escape;
	short int columns;
	short int lines;
	short int entry_x;
	short int entry_y;
	short int exit_x;
	short int exit_y;
	uint64_t res1;
	uint32_t res2;
	int counter;
	int sollution_off;
	char separator;
	char wall;
	char path;
	int solveid;
	uint16_t steps;
} bin_t;


#endif
