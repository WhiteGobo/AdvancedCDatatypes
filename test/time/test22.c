#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	DateTime dt1, dt2;
	Duration dur1, dur2;

	dt1 = DateTime_parse("2000-10-30T06:12:00-05:00");
	dt2 = DateTime_parse("1999-11-28T09:00:00Z");
	dur1 = DateTime_sub(dt1, dt2);
	dur2 = Duration_parse("P337DT2H12M");
	if (Duration_not_equal(dur1, dur2)){
		tmpstring = Duration_serialize(dur1);
		fprintf(stderr, "DateTime_sub failed. Got: '%s'\n", tmpstring);
		free(tmpstring);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
