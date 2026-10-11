#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	Date x, y, z;
	Duration dur1, dur2;

	x = Date_parse("2000-10-30");
	y = Date_parse("1999-08-30");
	dur1 = Duration_parse("P1Y2M");
	dur2 = Duration_neg(dur1);
	z = Date_add(x, dur2);
	if(Date_equal(z, DATE_NOTVALID)){
		fprintf(stderr, "Add produced non valid Date\n");
		exit(EXIT_FAILURE);
	}
	if (!Date_equal(y, z)){
		fprintf(stderr, "Add failed to produced correct date\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
