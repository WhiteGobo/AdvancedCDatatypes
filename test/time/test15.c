#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	Time dt1;
	Duration dur1, dur2;

	dt1 = Time_parse("13:20:00-05:00");
	dur1 = Time_offset_as_duration(dt1);
	dur2 = Duration_parse("-PT5H");
	if (Duration_not_equal(dur1, dur2)){
		fprintf(stderr, "wrong timeoffset from "
				"'113:20:00-05:00'\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
