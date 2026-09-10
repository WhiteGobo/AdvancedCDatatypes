#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	Date dt1, dt2;
	Duration dur1, dur2;

	dt1 = Date_parse("2000-10-30Z");
	dt2 = Date_parse("1999-11-28Z");
	dur1 = Date_sub(dt1, dt2);
	dur2 = Duration_parse("P337D");
	if (Duration_not_equal(dur1, dur2)){
		fprintf(stderr, "Date_sub failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
