#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	Date dt1;
	Duration dur1, dur2;

	dt1 = Date_parse("1999-05-31-05:00");
	dur1 = Date_offset_as_duration(dt1);
	dur2 = Duration_parse("-PT5H");
	if (Duration_not_equal(dur1, dur2)){
		fprintf(stderr, "wrong timeoffset from "
				"'1999-05-31-05:00'\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
