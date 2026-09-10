#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

int main(int argc, char *argv[]){
	int err = EXIT_SUCCESS;
	char* tmp, *tmpstring;
	DateTime dt1, dt2, dt3;

	dt1 = DateTime_parse("2002-04-01T12:00:00-01:00");
	dt2 = DateTime_parse("2002-04-02T17:00:00+04:00");
	dt3 = DateTime_parse("2002-04-03T12:00:00-01:00");

	if (!DateTime_not_equal(dt1, dt2)){
		fprintf(stderr, "DateTime not equal didnt work\n");
		err = EXIT_FAILURE;
	}
	if (!DateTime_less(dt1, dt2)){
		fprintf(stderr, "'2002-04-01T12:00:00-01:00' < '2002-04-02T17:00:00+04:00'\n");
		fprintf(stderr, "DateTime_less didnt work\n");
		err = EXIT_FAILURE;
	}
	if (!DateTime_less_or_equal(dt1, dt2)){
		fprintf(stderr, "DateTime_less_or_equal didnt work\n");
		err = EXIT_FAILURE;
	}
	if (!DateTime_less_or_equal(dt1, dt1)){
		fprintf(stderr, "DateTime_less_or_equal didnt work\n");
		err = EXIT_FAILURE;
	}
	if (!DateTime_greater_or_equal(dt3, dt2)){
		fprintf(stderr, "DateTime_greater_or_equal didnt work\n");
		err = EXIT_FAILURE;
	}
	if (!DateTime_greater_or_equal(dt1, dt1)){
		fprintf(stderr, "'2002-04-01T12:00:00-01:00' >= '2002-04-01T12:00:00-01:00'\n");
		fprintf(stderr, "DateTime_greater_or_equal didnt work\n");
		err = EXIT_FAILURE;
	}
	exit(err);
}
