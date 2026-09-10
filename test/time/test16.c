#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	Duration dur1;

	dur1 = Duration_parse("P20Y15M");
	if (Duration_get_years(dur1) != 21){
		fprintf(stderr, "wrong year from 'P20Y15M'.");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
