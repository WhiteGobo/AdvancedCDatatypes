#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	DateTime dt1, dt2, dt3;
	Duration dur1;

	dt1 = DateTime_parse("1999-12-31T24:00:00");
	if (dt1.year != 2000){
		fprintf(stderr, "wrong year in '1999-12-31T24:00:00'\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
