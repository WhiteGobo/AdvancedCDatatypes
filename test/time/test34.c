#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"
static bool qq(const char* input, const char* output, const char* duration);
static bool qq_neg(const char* input, const char* output, const char* duration);

int main(int argc, char *argv[]){
	int err = EXIT_SUCCESS;
	if(!qq_neg("2000-10-30", "1999-08-30", "P1Y2M")){
		err = EXIT_FAILURE;
	}
	if(!qq_neg("2000-10-30", "2000-10-26", "P3DT1H15M")){
		err = EXIT_FAILURE;
	}
	exit(err);
}

static bool qq(const char* input, const char* output, const char* duration){
	Date x, y, z;
	Duration dur1, dur2;

	x = Date_parse(input);
	y = Date_parse(output);
	dur1 = Duration_parse(duration);
	z = Date_add(x, dur2);
	fprintf(stderr, "testing %s + %s = %s\n", input, duration, output);
	if(Date_equal(z, DATE_NOTVALID)){
		fprintf(stderr, "Add produced non valid Date\n");
		return false;
	}
	if (!Date_equal(y, z)){
		fprintf(stderr, "Add failed to produced correct date. Got: ");
		fprintf_Date(stderr, z);
		fprintf(stderr, "\n");
		return false;
	}
	return true;
}

static bool qq_neg(const char* input, const char* output, const char* duration){
	Date x, y, z;
	Duration dur1, dur2;

	x = Date_parse(input);
	y = Date_parse(output);
	dur1 = Duration_parse(duration);
	dur2 = Duration_neg(dur1);
	z = Date_add(x, dur2);
	fprintf(stderr, "testing %s - %s = %s\n", input, duration, output);
	if(Date_equal(z, DATE_NOTVALID)){
		fprintf(stderr, "Add produced non valid Date\n");
		return false;
	}
	if (!Date_equal(y, z)){
		fprintf(stderr, "Add failed to produced correct date. Got: ");
		fprintf_Date(stderr, z);
		fprintf(stderr, "\n");
		return false;
	}
	return true;
}
