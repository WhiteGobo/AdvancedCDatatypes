#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	DateTime dt1;
	Duration dur1, dur2;

	dt1 = DateTime_parse("1999-05-31T13:20:00-05:00");
	dur1 = DateTime_offset_as_duration(dt1);
	dur2 = Duration_parse("-PT5H");
	if (Duration_not_equal(dur1, dur2)){
		fprintf(stderr, "wrong timeoffset from "
				"'1999-05-31T13:20:00-05:00'\n");
		tmpstring = Duration_serialize(dur1);
		fprintf(stderr, "Got: %s\n", tmpstring);
		free(tmpstring);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
