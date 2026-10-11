#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

static bool qq(const char* input, const char* output, const char* dur);
static bool qq_neg(const char* input, const char* output, const char* dur);

int main(int argc, char *argv[]){
	int err = EXIT_SUCCESS;
	if(!qq("2000-12-13T00:11:11.3", "1999-11-11T23:10:10.2", "-P1Y1M1DT1H1M1.1S")){
		err = EXIT_FAILURE;
	}
	if(!qq_neg("2000-10-30T11:12:00", "2000-10-27T09:57:00", "P3DT1H15M")){
		err = EXIT_FAILURE;
	}
	exit(err);
}

static bool qq(const char* input, const char* output, const char* dur){
	char* tmp, *tmpstring;
	DateTime x, y, z;
	Duration dur1;

	x = DateTime_parse(input);
	y = DateTime_parse(output);
	dur1 = Duration_parse(dur);
	z = DateTime_add(x, dur1);
	fprintf(stderr, "Try add %s + %s = %s\n", input, dur, output);
	if(DateTime_equal(z, DATETIME_NOTVALID)){
		fprintf(stderr, "Add produced non valid DateTime\n");
		return false;
	}
	if (!DateTime_equal(y, z)){
		fprintf(stderr, "Add failed to produced correct datetime. Got ");
		fprintf_DateTime(stderr, z);
		fprintf(stderr, "\n");
		return false;
	}
	return true;
}

static bool qq_neg(const char* input, const char* output, const char* dur){
	char* tmp, *tmpstring;
	DateTime x, y, z;
	Duration dur1;

	x = DateTime_parse(input);
	y = DateTime_parse(output);
	dur1 = Duration_parse(dur);
	dur1 = Duration_neg(dur1);
	z = DateTime_add(x, dur1);
	fprintf(stderr, "Try %s - %s = %s\n", input, dur, output);
	if(DateTime_equal(z, DATETIME_NOTVALID)){
		fprintf(stderr, "Add produced non valid DateTime\n");
		return false;
	}
	if (!DateTime_equal(y, z)){
		fprintf(stderr, "Add failed to produced correct datetime. Got ");
		fprintf_DateTime(stderr, z);
		fprintf(stderr, "\n");
		return false;
	}
	return true;
}
