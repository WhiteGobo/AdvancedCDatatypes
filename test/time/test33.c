#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

int main(int argc, char *argv[]){
	int err = EXIT_SUCCESS;
	char* tmp, *tmpstring;
	Time dt1, dt2, dt3;

	dt1 = Time_parse("20:30:00+10:30");
	dt2 = Time_parse("06:00:00-05:00");
	dt3 = Time_parse("22:30:00+10:30");

	if (!Time_not_equal(dt1, dt2)){
		fprintf(stderr, "Time not equal didnt work\n");
		err = EXIT_FAILURE;
	}
	if (!Time_less(dt1, dt2)){
		fprintf(stderr, "Time_less didnt work\n");
		err = EXIT_FAILURE;
	}
	if (!Time_less_or_equal(dt1, dt2)){
		fprintf(stderr, "Time_less_or_equal didnt work\n");
		err = EXIT_FAILURE;
	}
	if (!Time_less_or_equal(dt1, dt1)){
		fprintf(stderr, "Time_less_or_equal didnt work\n");
		err = EXIT_FAILURE;
	}
	if (!Time_greater_or_equal(dt3, dt1)){
		fprintf(stderr, "Time_greater_or_equal didnt work\n");
		err = EXIT_FAILURE;
	}
	if (!Time_greater_or_equal(dt1, dt1)){
		fprintf(stderr, "Time_greater_or_equal didnt work\n");
		err = EXIT_FAILURE;
	}
	exit(err);
}
