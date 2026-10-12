#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

int main(int argc, char *argv[]){
	int err = EXIT_SUCCESS;
	char* tmp, *tmpstring;
	Date dt1, dt2, dt3, dt4, dt4_s;

	dt1 = Date_parse("2004-12-24");
	dt2 = Date_parse("2004-12-26");
	dt3 = Date_parse("2004-12-25");
	dt4_s = Date_parse("2004-12-25-12:00");
	dt4 = Date_parse("2004-12-26+12:00");

	if (!Date_not_equal(dt1, dt2)){
		fprintf(stderr, "Date not equal didnt work\n");
		err = EXIT_FAILURE;
	}
	if (!Date_less(dt1, dt2)){
		fprintf(stderr, "Date_less didnt work\n");
		err = EXIT_FAILURE;
	}
	if (!Date_less_or_equal(dt1, dt2)){
		fprintf(stderr, "Date_less_or_equal didnt work\n");
		err = EXIT_FAILURE;
	}
	if (!Date_less_or_equal(dt1, dt1)){
		fprintf(stderr, "Date_less_or_equal didnt work\n");
		err = EXIT_FAILURE;
	}
	if(!Date_less(dt3, dt4)){
		fprintf(stderr, "Date_less didnt recognise timeoffset "
				"as expected\n");
		err = EXIT_FAILURE;
	}
	if(!Date_equal(dt4, dt4_s)){
		fprintf(stderr, "Date_equal didnt recognise timeoffset "
				"as expected\n");
		err = EXIT_FAILURE;
	}
	if (!Date_greater_or_equal(dt2, dt3)){
		fprintf(stderr, "'2004-12-25' >= '2004-12-26'\n");
		fprintf(stderr, "Date_greater_or_equal didnt work\n");
		err = EXIT_FAILURE;
	}
	if (!Date_greater_or_equal(dt1, dt1)){
		fprintf(stderr, "'2004-12-24' >= '2004-12-24'\n");
		fprintf(stderr, "Date_greater_or_equal didnt work\n");
		err = EXIT_FAILURE;
	}
	exit(err);
}
