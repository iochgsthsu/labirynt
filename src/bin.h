#ifndef _BIN_H
#define _BIN_H
typedef struct bin{
	
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
} bin_t;


#endif
