#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	Time dt1, dt2;
	Duration dur1, dur2;

	dt1 = Time_parse("11:12:00Z");
	dt2 = Time_parse("04:00:00Z");
	dur1 = Time_sub(dt1, dt2);
	dur2 = Duration_parse("PT7H12M");
	if (Duration_not_equal(dur1, dur2)){
		fprintf(stderr, "Time_sub failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
