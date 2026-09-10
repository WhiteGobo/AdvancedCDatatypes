#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	Duration dur1;
	Decimal seconds;

	dur1 = Duration_parse("P3DT10H12.5S");
	seconds = Duration_get_seconds(dur1);
	if (Decimal_not_equal(seconds, Decimal_parse("12.5", -1))){
		fprintf(stderr, "wrong seconds from 'P3DT10H12.5S'.");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
