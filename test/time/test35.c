#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

static bool qq(const char* input, const char* output, const char* dur);
static bool qq_neg(const char* input, const char* output, const char* dur);

int main(int argc, char *argv[]){
	int err = EXIT_SUCCESS;
	if(!qq("11:12:00", "12:27:00", "P3DT1H15M")){
		err = EXIT_FAILURE;
	}
	if(!qq("23:12:00+03:00", "02:27:00+03:00", "P1DT3H15M")){
		err = EXIT_FAILURE;
	}
	if(!qq_neg("11:12:00", "09:57:00", "P3DT1H15M")){
		err = EXIT_FAILURE;
	}
	exit(err);
}

static bool qq(const char* input, const char* output, const char* dur){
	char* tmp, *tmpstring;
	Time x, y, z;
	Duration dur1;

	x = Time_parse(input);
	y = Time_parse(output);
	dur1 = Duration_parse(dur);
	z = Time_add(x, dur1);
	fprintf(stderr, "Try add %s + %s = %s\n", input, dur, output);
	if(Time_equal(z, TIME_NOTVALID)){
		fprintf(stderr, "Add produced non valid Time\n");
		return false;
	}
	if (!Time_equal(y, z)){
		fprintf(stderr, "Add failed to produced correct time. Got ");
		fprintf_Time(stderr, z);
		fprintf(stderr, "\n");
		return false;
	}
	return true;
}

static bool qq_neg(const char* input, const char* output, const char* dur){
	char* tmp, *tmpstring;
	Time x, y, z;
	Duration dur1;

	x = Time_parse(input);
	y = Time_parse(output);
	dur1 = Duration_parse(dur);
	dur1 = Duration_neg(dur1);
	z = Time_add(x, dur1);
	fprintf(stderr, "Try %s - %s = %s\n", input, dur, output);
	if(Time_equal(z, TIME_NOTVALID)){
		fprintf(stderr, "Add produced non valid Time\n");
		return false;
	}
	if (!Time_equal(y, z)){
		fprintf(stderr, "Add failed to produced correct time. Got ");
		fprintf_Time(stderr, z);
		fprintf(stderr, "\n");
		return false;
	}
	return true;
}
