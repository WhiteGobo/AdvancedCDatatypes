#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	Duration dur1;

	dur1 = Duration_parse("P20Y15M");
	if (Duration_get_months(dur1) != 3){
		fprintf(stderr, "wrong month from 'P20Y15M'.");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
