#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

static bool qq(const char* input, const char* output, const char* dur);
static bool qq_neg(const char* input, const char* output, const char* dur);

int main(int argc, char *argv[]){
	int err = EXIT_SUCCESS;
	if(!DateTime_is_valid(DateTime_parse("2000-12-13T00:11:11.3"))){
		fprintf(stderr, "is_valid failed\n");
		err = EXIT_FAILURE;
	}
	if(DateTime_is_valid(DateTime_parse("not a datetime"))){
		fprintf(stderr, "is_valid failed\n");
		err = EXIT_FAILURE;
	}
	if(!Date_is_valid(Date_parse("2000-12-13"))){
		fprintf(stderr, "is_valid failed\n");
		err = EXIT_FAILURE;
	}
	if(Date_is_valid(Date_parse("not a date"))){
		fprintf(stderr, "is_valid failed\n");
		err = EXIT_FAILURE;
	}
	if(!Time_is_valid(Time_parse("00:11:11.3"))){
		fprintf(stderr, "is_valid failed\n");
		err = EXIT_FAILURE;
	}
	if(Time_is_valid(Time_parse("not a time"))){
		fprintf(stderr, "is_valid failed\n");
		err = EXIT_FAILURE;
	}
	if(!Duration_is_valid(Duration_parse("P3DT1H15M"))){
		fprintf(stderr, "is_valid failed\n");
		err = EXIT_FAILURE;
	}
	if(Duration_is_valid(Duration_parse("not a duration"))){
		fprintf(stderr, "is_valid failed\n");
		err = EXIT_FAILURE;
	}
	exit(err);
}
